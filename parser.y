%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtab.h"

extern int yylex(void);
void yyerror(const char *s);
extern char *yytext;
extern int yylineno;
ASTNode *root;
%}

%union {
    int integer_value;
    char *string_value;
    struct ASTNode *node;
    struct Type *type;
}

%token <string_value> T_IDENTIFIER T_TYPENAME
%token <integer_value> T_INTEGER
%token <string_value> T_FLOAT_LITERAL T_CHAR_LITERAL T_STRING_LITERAL
%token T_INT T_RETURN T_IF T_ELSE T_WHILE T_FOR T_SWITCH T_CASE T_DEFAULT T_BREAK T_DO T_CONTINUE T_GOTO T_STRUCT T_UNION T_ENUM T_CHAR T_FLOAT T_DOUBLE T_VOID T_SHORT T_LONG T_SIGNED T_UNSIGNED T_TYPEDEF T_SIZEOF T_CONST T_STATIC T_EXTERN T_VOLATILE T_INLINE
%token T_SEMICOLON T_LPAREN T_RPAREN T_LBRACE T_RBRACE T_COMMA
%token T_LBRACKET T_RBRACKET T_DOT T_ARROW
%token T_INC T_DEC
%token T_LOGICAL_NOT T_BITWISE_NOT
%token T_LOGICAL_AND T_LOGICAL_OR
%token T_BITWISE_AND T_BITWISE_OR T_BITWISE_XOR
%token T_LSHIFT T_RSHIFT
%token T_ASSIGN T_ADD_ASSIGN T_SUB_ASSIGN T_MUL_ASSIGN T_DIV_ASSIGN T_MOD_ASSIGN
%token T_EQ T_NE T_GT T_GE T_LT T_LE
%token T_ADD T_SUB T_MUL T_DIV T_MOD
%token T_QUESTION T_COLON

%nonassoc T_IFX
%nonassoc T_ELSE

%right T_ASSIGN T_ADD_ASSIGN T_SUB_ASSIGN T_MUL_ASSIGN T_DIV_ASSIGN T_MOD_ASSIGN
%right T_QUESTION T_COLON
%left T_LOGICAL_OR
%left T_LOGICAL_AND
%left T_BITWISE_OR
%left T_BITWISE_XOR
%left T_BITWISE_AND
%left T_EQ T_NE
%left T_GT T_GE T_LT T_LE
%left T_LSHIFT T_RSHIFT
%left T_ADD T_SUB
%left T_MUL T_DIV T_MOD
%right T_INC T_DEC T_LOGICAL_NOT T_BITWISE_NOT

%type <node> program translation_unit external_declaration
%type <node> function_definition
%type <node> statement compound_statement block_item_list block_item
%type <node> declaration assignment_expression selection_statement iteration_statement jump_statement labeled_statement
%type <node> expression conditional_expression logical_or_expression logical_and_expression inclusive_or_expression exclusive_or_expression and_expression equality_expression relational_expression shift_expression additive_expression multiplicative_expression cast_expression unary_expression postfix_expression primary_expression
%type <node> param_list parameter_declaration argument_expression_list
%type <node> struct_specifier union_specifier struct_declaration_list struct_declaration enum_specifier enumerator_list enumerator
%type <node> initializer_list initializer init_declarator_list init_declarator declarator direct_declarator declarator_list
%type <type> type_specifier declaration_specifiers pointer type_name abstract_declarator direct_abstract_declarator

%%

program:
    translation_unit { root = $1; }
    ;

translation_unit:
    external_declaration { $$ = create_program_node(); add_toplevel_statement_to_program($$, $1); }
    | translation_unit external_declaration { add_toplevel_statement_to_program($1, $2); $$ = $1; }
    ;

external_declaration:
    function_definition
    | declaration
    ;

function_definition:
    declaration_specifiers declarator compound_statement { $$ = create_function_definition_node($1, $2, NULL, $3); }
    ;

declaration:
    declaration_specifiers init_declarator_list T_SEMICOLON { $$ = create_decl_list_node($1, $2); }
    | declaration_specifiers T_SEMICOLON { $$ = create_type_decl_node($1); }
    | T_TYPEDEF declaration_specifiers init_declarator_list T_SEMICOLON {
        for (int i = 0; i < $3->statement_list.count; i++) {
            add_typedef_name($3->statement_list.statements[i]->var_decl.name);
        }
        $$ = create_typedef_node(NULL, $2);
    }
    ;

declaration_specifiers:
    type_specifier { $$ = $1; }
    | T_CONST declaration_specifiers { $$ = $2; $$->is_const = 1; }
    | T_STATIC declaration_specifiers { $$ = $2; $$->is_static = 1; }
    | T_EXTERN declaration_specifiers { $$ = $2; $$->is_extern = 1; }
    | T_VOLATILE declaration_specifiers { $$ = $2; $$->is_volatile = 1; }
    | T_INLINE declaration_specifiers { $$ = $2; $$->is_inline = 1; }
    ;

init_declarator_list:
    init_declarator { $$ = create_statement_list_node(); add_statement_to_list($$, $1); }
    | init_declarator_list T_COMMA init_declarator { add_statement_to_list($1, $3); $$ = $1; }
    ;

init_declarator:
    declarator { $$ = $1; }
    | declarator T_ASSIGN initializer { $1->var_decl.init_expr = $3; $$ = $1; }
    ;

declarator:
    pointer direct_declarator { $$ = $2; Type *t = $1; while(t->ptr_to) t = t->ptr_to; t->ptr_to = $2->var_decl.var_type; $2->var_decl.var_type = $1; }
    | direct_declarator { $$ = $1; }
    ;

direct_declarator:
    T_IDENTIFIER { $$ = create_var_decl_node($1, NULL, 0, 0, NULL); }
    | T_LPAREN declarator T_RPAREN { $$ = $2; }
    | direct_declarator T_LBRACKET conditional_expression T_RBRACKET { $$ = $1; $1->var_decl.var_type = create_array_type($1->var_decl.var_type, 0); }
    | direct_declarator T_LBRACKET T_RBRACKET { $$ = $1; $1->var_decl.var_type = create_array_type($1->var_decl.var_type, 0); }
    | direct_declarator T_LPAREN param_list T_RPAREN {
        $$ = $1;
        Type *t = $$->var_decl.var_type;
        if (t) {
            while(t->ptr_to) t = t->ptr_to;
            t->ptr_to = create_function_type(NULL, $3);
        } else {
            $$->var_decl.var_type = create_function_type(NULL, $3);
        }
    }
    | direct_declarator T_LPAREN T_RPAREN {
        $$ = $1;
        Type *t = $$->var_decl.var_type;
        if (t) {
            while(t->ptr_to) t = t->ptr_to;
            t->ptr_to = create_function_type(NULL, NULL);
        } else {
            $$->var_decl.var_type = create_function_type(NULL, NULL);
        }
    }
    ;

pointer:
    T_MUL { $$ = create_pointer_type(NULL); }
    | T_MUL pointer { $$ = create_pointer_type($2); }
    ;

param_list:
    parameter_declaration { $$ = create_param_list_node(); add_param_to_list($$, $1); }
    | param_list T_COMMA parameter_declaration { add_param_to_list($1, $3); $$ = $1; }
    ;

parameter_declaration:
    declaration_specifiers declarator {
        $$ = $2;
        if ($$->var_decl.var_type) {
            Type *t = $$->var_decl.var_type;
            while(t->ptr_to) t = t->ptr_to;
            t->ptr_to = $1;
        } else {
            $$->var_decl.var_type = $1;
        }
    }
    | declaration_specifiers abstract_declarator { $$ = create_var_decl_node(NULL, $1, 0, 0, NULL); }
    | declaration_specifiers { $$ = create_var_decl_node(NULL, $1, 0, 0, NULL); }
    ;

type_name:
    declaration_specifiers { $$ = $1; }
    | declaration_specifiers abstract_declarator { $$ = $1; }
    ;

abstract_declarator:
    pointer { $$ = $1; }
    | direct_abstract_declarator { $$ = $1; }
    | pointer direct_abstract_declarator { $$ = $1; }
    ;

direct_abstract_declarator:
    T_LPAREN abstract_declarator T_RPAREN { $$ = $2; }
    | T_LBRACKET T_RBRACKET { $$ = create_array_type(NULL, 0); }
    | T_LBRACKET conditional_expression T_RBRACKET { $$ = create_array_type(NULL, 0); }
    | direct_abstract_declarator T_LBRACKET T_RBRACKET { $$ = $1; }
    | direct_abstract_declarator T_LBRACKET conditional_expression T_RBRACKET { $$ = $1; }
    | T_LPAREN T_RPAREN { $$ = create_function_type(NULL, NULL); }
    | T_LPAREN param_list T_RPAREN { $$ = create_function_type(NULL, $2); }
    | direct_abstract_declarator T_LPAREN T_RPAREN { $$ = $1; }
    | direct_abstract_declarator T_LPAREN param_list T_RPAREN { $$ = $1; }
    ;

statement:
    labeled_statement
    | compound_statement
    | expression T_SEMICOLON
    | selection_statement
    | iteration_statement
    | jump_statement
    ;

compound_statement:
    T_LBRACE T_RBRACE { $$ = create_statement_list_node(); }
    | T_LBRACE block_item_list T_RBRACE { $$ = $2; }
    ;

block_item_list:
    block_item { $$ = create_statement_list_node(); add_statement_to_list($$, $1); }
    | block_item_list block_item { add_statement_to_list($1, $2); $$ = $1; }
    ;

block_item:
    declaration
    | statement
    ;

labeled_statement:
    T_IDENTIFIER ':' statement { $$ = create_label_node($1, $3); }
    | T_CASE conditional_expression ':' statement { $$ = create_case_node($2); add_statement_to_list($$, $4); }
    | T_DEFAULT ':' statement { $$ = create_case_node(NULL); add_statement_to_list($$, $3); }
    | T_IDENTIFIER ':' T_SEMICOLON { $$ = create_label_node($1, NULL); }
    ;

selection_statement:
    T_IF T_LPAREN expression T_RPAREN statement %prec T_IFX { $$ = create_if_node($3, $5, NULL); }
    | T_IF T_LPAREN expression T_RPAREN statement T_ELSE statement { $$ = create_if_node($3, $5, $7); }
    | T_SWITCH T_LPAREN expression T_RPAREN statement { $$ = create_switch_node($3, $5); }
    ;

iteration_statement:
    T_WHILE T_LPAREN expression T_RPAREN statement { $$ = create_while_node($3, $5); }
    | T_DO statement T_WHILE T_LPAREN expression T_RPAREN T_SEMICOLON { $$ = create_do_while_node($2, $5); }
    | T_FOR T_LPAREN expression T_SEMICOLON expression T_SEMICOLON T_RPAREN statement { $$ = create_for_node($3, $5, NULL, $8); }
    | T_FOR T_LPAREN expression T_SEMICOLON expression T_SEMICOLON expression T_RPAREN statement { $$ = create_for_node($3, $5, $7, $9); }
    | T_FOR T_LPAREN declaration expression T_SEMICOLON T_RPAREN statement { $$ = create_for_node($3, $4, NULL, $7); }
    | T_FOR T_LPAREN declaration expression T_SEMICOLON expression T_RPAREN statement { $$ = create_for_node($3, $4, $6, $8); }
    ;

jump_statement:
    T_GOTO T_IDENTIFIER T_SEMICOLON { $$ = create_goto_node($2); }
    | T_CONTINUE T_SEMICOLON { $$ = create_continue_node(); }
    | T_BREAK T_SEMICOLON { $$ = create_break_node(); }
    | T_RETURN T_SEMICOLON { $$ = create_return_node(NULL); }
    | T_RETURN expression T_SEMICOLON { $$ = create_return_node($2); }
    ;

expression:
    assignment_expression { $$ = $1; }
    | expression T_COMMA assignment_expression { $$ = create_binary_op_node(T_COMMA, $1, $3); }
    ;

assignment_expression:
    conditional_expression { $$ = $1; }
    | unary_expression T_ASSIGN assignment_expression { $$ = create_assign_node($1, $3); }
    | unary_expression T_ADD_ASSIGN assignment_expression { $$ = create_assign_node($1, create_binary_op_node(T_ADD, $1, $3)); }
    | unary_expression T_SUB_ASSIGN assignment_expression { $$ = create_assign_node($1, create_binary_op_node(T_SUB, $1, $3)); }
    | unary_expression T_MUL_ASSIGN assignment_expression { $$ = create_assign_node($1, create_binary_op_node(T_MUL, $1, $3)); }
    | unary_expression T_DIV_ASSIGN assignment_expression { $$ = create_assign_node($1, create_binary_op_node(T_DIV, $1, $3)); }
    | unary_expression T_MOD_ASSIGN assignment_expression { $$ = create_assign_node($1, create_binary_op_node(T_MOD, $1, $3)); }
    ;

conditional_expression:
    logical_or_expression { $$ = $1; }
    | logical_or_expression T_QUESTION expression T_COLON conditional_expression { $$ = create_ternary_op_node($1, $3, $5); }
    ;

logical_or_expression:
    logical_and_expression { $$ = $1; }
    | logical_or_expression T_LOGICAL_OR logical_and_expression { $$ = create_binary_op_node(T_LOGICAL_OR, $1, $3); }
    ;

logical_and_expression:
    inclusive_or_expression { $$ = $1; }
    | logical_and_expression T_LOGICAL_AND inclusive_or_expression { $$ = create_binary_op_node(T_LOGICAL_AND, $1, $3); }
    ;

inclusive_or_expression:
    exclusive_or_expression { $$ = $1; }
    | inclusive_or_expression T_BITWISE_OR exclusive_or_expression { $$ = create_binary_op_node(T_BITWISE_OR, $1, $3); }
    ;

exclusive_or_expression:
    and_expression { $$ = $1; }
    | exclusive_or_expression T_BITWISE_XOR and_expression { $$ = create_binary_op_node(T_BITWISE_XOR, $1, $3); }
    ;

and_expression:
    equality_expression { $$ = $1; }
    | and_expression T_BITWISE_AND equality_expression { $$ = create_binary_op_node(T_BITWISE_AND, $1, $3); }
    ;

equality_expression:
    relational_expression { $$ = $1; }
    | equality_expression T_EQ relational_expression { $$ = create_binary_op_node(T_EQ, $1, $3); }
    | equality_expression T_NE relational_expression { $$ = create_binary_op_node(T_NE, $1, $3); }
    ;

relational_expression:
    shift_expression { $$ = $1; }
    | relational_expression T_LT shift_expression { $$ = create_binary_op_node(T_LT, $1, $3); }
    | relational_expression T_GT shift_expression { $$ = create_binary_op_node(T_GT, $1, $3); }
    | relational_expression T_LE shift_expression { $$ = create_binary_op_node(T_LE, $1, $3); }
    | relational_expression T_GE shift_expression { $$ = create_binary_op_node(T_GE, $1, $3); }
    ;

shift_expression:
    additive_expression { $$ = $1; }
    | shift_expression T_LSHIFT additive_expression { $$ = create_binary_op_node(T_LSHIFT, $1, $3); }
    | shift_expression T_RSHIFT additive_expression { $$ = create_binary_op_node(T_RSHIFT, $1, $3); }
    ;

additive_expression:
    multiplicative_expression { $$ = $1; }
    | additive_expression T_ADD multiplicative_expression { $$ = create_binary_op_node(T_ADD, $1, $3); }
    | additive_expression T_SUB multiplicative_expression { $$ = create_binary_op_node(T_SUB, $1, $3); }
    ;

multiplicative_expression:
    cast_expression { $$ = $1; }
    | multiplicative_expression T_MUL cast_expression { $$ = create_binary_op_node(T_MUL, $1, $3); }
    | multiplicative_expression T_DIV cast_expression { $$ = create_binary_op_node(T_DIV, $1, $3); }
    | multiplicative_expression T_MOD cast_expression { $$ = create_binary_op_node(T_MOD, $1, $3); }
    ;

cast_expression:
    unary_expression { $$ = $1; }
    | T_LPAREN type_name T_RPAREN cast_expression { $$ = create_cast_node($2, $4); }
    ;

unary_expression:
    postfix_expression { $$ = $1; }
    | T_INC unary_expression { $$ = create_unary_op_node(T_INC, $2); }
    | T_DEC unary_expression { $$ = create_unary_op_node(T_DEC, $2); }
    | T_BITWISE_AND cast_expression { $$ = create_unary_op_node(T_BITWISE_AND, $2); }
    | T_MUL cast_expression { $$ = create_unary_op_node(T_MUL, $2); }
    | T_ADD cast_expression { $$ = $2; }
    | T_SUB cast_expression { $$ = create_unary_op_node(T_SUB, $2); }
    | T_BITWISE_NOT cast_expression { $$ = create_unary_op_node(T_BITWISE_NOT, $2); }
    | T_LOGICAL_NOT cast_expression { $$ = create_unary_op_node(T_LOGICAL_NOT, $2); }
    | T_SIZEOF unary_expression { $$ = create_sizeof_node(NULL); }
    | T_SIZEOF T_LPAREN type_name T_RPAREN { $$ = create_sizeof_node($3); }
    ;

postfix_expression:
    primary_expression { $$ = $1; }
    | postfix_expression T_LBRACKET expression T_RBRACKET { $$ = create_array_access_node($1, $3); }
    | postfix_expression T_LPAREN T_RPAREN { $$ = create_func_call_node(NULL, NULL); }
    | postfix_expression T_LPAREN argument_expression_list T_RPAREN { $$ = create_func_call_node(NULL, $3); }
    | postfix_expression T_DOT T_IDENTIFIER { $$ = create_member_access_node($1, $3); }
    | postfix_expression T_ARROW T_IDENTIFIER { $$ = create_member_access_node($1, $3); }
    | postfix_expression T_INC { $$ = create_unary_op_node(T_INC, $1); }
    | postfix_expression T_DEC { $$ = create_unary_op_node(T_DEC, $1); }
    ;

primary_expression:
    T_IDENTIFIER { $$ = create_variable_node($1); }
    | T_INTEGER { $$ = create_integer_node($1); }
    | T_FLOAT_LITERAL { $$ = create_float_node($1); }
    | T_CHAR_LITERAL { $$ = create_char_node($1); }
    | T_STRING_LITERAL { $$ = create_string_literal_node($1); }
    | T_LPAREN expression T_RPAREN { $$ = $2; }
    ;

argument_expression_list:
    assignment_expression { $$ = create_arg_list_node(); add_arg_to_list($$, $1); }
    | argument_expression_list T_COMMA assignment_expression { add_arg_to_list($1, $3); $$ = $1; }
    ;

initializer:
    assignment_expression { $$ = $1; }
    | T_LBRACE initializer_list T_RBRACE { $$ = $2; }
    | T_LBRACE initializer_list T_COMMA T_RBRACE { $$ = $2; }
    ;

initializer_list:
    initializer { $$ = create_initializer_list_node(); add_initializer_to_list($$, $1); }
    | initializer_list T_COMMA initializer { add_initializer_to_list($1, $3); $$ = $1; }
    ;

type_specifier:
    T_VOID { $$ = create_type(TYPE_VOID); }
    | T_CHAR { $$ = create_type(TYPE_CHAR); }
    | T_SHORT { $$ = create_type(TYPE_SHORT); }
    | T_INT { $$ = create_type(TYPE_INT); }
    | T_LONG { $$ = create_type(TYPE_LONG); }
    | T_FLOAT { $$ = create_type(TYPE_FLOAT); }
    | T_DOUBLE { $$ = create_type(TYPE_DOUBLE); }
    | T_SIGNED { $$ = create_type(TYPE_INT); $$->is_signed = 1; }
    | T_UNSIGNED { $$ = create_type(TYPE_INT); $$->is_unsigned = 1; }
    | struct_specifier { $$ = create_type_from_specifier($1); }
    | union_specifier { $$ = create_type_from_union_specifier($1); }
    | enum_specifier { $$ = create_type_from_enum_specifier($1); }
    | T_TYPENAME { $$ = create_type(TYPE_TYPEDEF); $$->name = $1; }
    ;

struct_specifier:
    T_STRUCT T_IDENTIFIER T_LBRACE struct_declaration_list T_RBRACE { $$ = create_struct_def_node($2, $4); }
    | T_STRUCT T_LBRACE struct_declaration_list T_RBRACE { $$ = create_struct_def_node(NULL, $3); }
    | T_STRUCT T_IDENTIFIER { $$ = create_struct_ref_node($2); }
    ;

union_specifier:
    T_UNION T_IDENTIFIER T_LBRACE struct_declaration_list T_RBRACE { $$ = create_union_def_node($2, $4); }
    | T_UNION T_LBRACE struct_declaration_list T_RBRACE { $$ = create_union_def_node(NULL, $3); }
    | T_UNION T_IDENTIFIER { $$ = create_union_ref_node($2); }
    ;

enum_specifier:
    T_ENUM T_IDENTIFIER T_LBRACE enumerator_list T_RBRACE { $$ = create_enum_specifier_node($2, $4); }
    | T_ENUM T_LBRACE enumerator_list T_RBRACE { $$ = create_enum_specifier_node(NULL, $3); }
    | T_ENUM T_IDENTIFIER { $$ = create_enum_specifier_node($2, NULL); }
    ;

enumerator_list:
    enumerator { $$ = create_statement_list_node(); add_statement_to_list($$, $1); }
    | enumerator_list T_COMMA enumerator { add_statement_to_list($1, $3); $$ = $1; }
    ;

enumerator:
    T_IDENTIFIER { $$ = create_enumerator_node($1, NULL); }
    | T_IDENTIFIER T_ASSIGN conditional_expression { $$ = create_enumerator_node($1, $3); }
    ;

struct_declaration_list:
    struct_declaration { $$ = create_statement_list_node(); add_statement_to_list($$, $1); }
    | struct_declaration_list struct_declaration { add_statement_to_list($1, $2); $$ = $1; }
    ;

struct_declaration:
    declaration_specifiers declarator_list T_SEMICOLON { $$ = create_decl_list_node($1, $2); }
    ;

declarator_list:
    declarator { $$ = create_statement_list_node(); add_statement_to_list($$, $1); }
    | declarator_list T_COMMA declarator { add_statement_to_list($1, $3); $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error on line %d: %s near '%s'\n", yylineno, s, yytext);
}
