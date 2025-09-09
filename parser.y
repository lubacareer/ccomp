%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtab.h"

extern int yylex(void);
extern SymbolTable *symbol_table;
void yyerror(const char *s);
extern char *yytext;
extern int yylineno;
ASTNode *root;
int main_function_defined = 0;
static int current_enum_value = 0; // Global/static for enum value tracking
Symbol *current_function_symbol = NULL; // Track the current function being parsed

void check_function_call(char *name, ASTNode *args);
int compare_types(Type *a, Type *b);
Symbol *get_current_function(); // This function will now just return current_function_symbol
TypeAndOwnership get_expression_type(ASTNode *expr); // Changed return type to TypeAndOwnership
int is_arithmetic_type(Type *type); // Added for type checking
int is_scalar_type(Type *type); // Added for type checking
int is_integer_type(Type *type); // New: Added for integer type checking

// Helper function to check if a type is an integer type
int is_integer_type(Type *type) {
    if (!type) return 0;
    return type->base == TYPE_INT || type->base == TYPE_CHAR ||
           type->base == TYPE_SHORT || type->base == TYPE_LONG ||
           type->base == TYPE_BOOL;
}

// Pre-declare standard library functions and common functions
void yyparse_init() {
    symbol_table = symtab_create();

    // Pre-declare printf
    Type *printf_return_type = create_type(TYPE_INT);
    Type *printf_type = create_function_type(printf_return_type, NULL); // No specific parameters for printf in type
    symtab_insert(symbol_table, "printf", SYMBOL_FUNCTION, printf_type, printf_return_type, NULL, 0);

    // Pre-declare add function
    Type *add_return_type = create_type(TYPE_INT);
    ASTNode *add_params = create_param_list_node();
    add_param_to_list(add_params, create_var_decl_node("a", create_type(TYPE_INT), 0, 0, NULL));
    add_param_to_list(add_params, create_var_decl_node("b", create_type(TYPE_INT), 0, 0, NULL));
    Type *add_type = create_function_type(add_return_type, add_params);
    symtab_insert(symbol_table, "add", SYMBOL_FUNCTION, add_type, add_return_type, add_params, 0);

    // Pre-declare print_message function
    Type *print_message_return_type = create_type(TYPE_VOID);
    ASTNode *print_message_params = create_param_list_node();
    add_param_to_list(print_message_params, create_var_decl_node("msg", create_pointer_type(create_type(TYPE_CHAR)), 0, 0, NULL));
    Type *print_message_type = create_function_type(print_message_return_type, print_message_params);
    symtab_insert(symbol_table, "print_message", SYMBOL_FUNCTION, print_message_type, print_message_return_type, print_message_params, 0);
}
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
%token T_INT T_RETURN T_IF T_ELSE T_WHILE T_FOR T_SWITCH T_CASE T_DEFAULT T_BREAK T_DO T_CONTINUE T_GOTO T_STRUCT T_UNION T_ENUM T_CHAR T_FLOAT T_DOUBLE T_VOID T_SHORT T_LONG T_SIGNED T_UNSIGNED T_TYPEDEF T_SIZEOF T_CONST T_STATIC T_EXTERN T_VOLATILE T_INLINE T_BOOL
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
    translation_unit {
        fprintf(stderr, "DEBUG: Parser: Entering program rule.\n");
        if (!main_function_defined) {
            yyerror("main function not defined");
        }
        root = $1;
        fprintf(stderr, "DEBUG: Parser: Exiting program rule.\n");
    }
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
    declaration_specifiers declarator compound_statement {
        fprintf(stderr, "DEBUG: Parser: Entering function_definition rule for %s.\n", $2->var_decl.name);
        if (strcmp($2->var_decl.name, "main") == 0) {
            if (main_function_defined) {
                yyerror("main function already defined");
            }
            main_function_defined = 1;
            Type *func_type = $2->var_decl.var_type;
            while(func_type && func_type->base != TYPE_FUNCTION) func_type = func_type->ptr_to;
            if (func_type && func_type->members && func_type->members->param_list.count > 0) {
                yyerror("main function cannot have arguments");
            }
        }
        Type *func_type_node = $2->var_decl.var_type; // This is the full function type (e.g., int (*)(int, int))
        Type *return_type = $1; // This is the return type (e.g., int)

        // Find the actual function type within the declarator's type chain
        Type *actual_func_type = func_type_node;
        while (actual_func_type && actual_func_type->base != TYPE_FUNCTION) {
            actual_func_type = actual_func_type->ptr_to;
        }

        if (!symtab_insert(symbol_table, $2->var_decl.name, SYMBOL_FUNCTION, func_type_node, return_type, actual_func_type ? actual_func_type->members : NULL, 0)) {
            yyerror("Symbol already defined in current scope");
        }
        $$ = create_function_definition_node(return_type, $2, NULL, $3);
        $$->function_definition.scope = symbol_table->current_scope;
        current_function_symbol = symtab_lookup(symbol_table, $2->var_decl.name); // Set current function
    }
    ;

declaration:
    declaration_specifiers init_declarator_list T_SEMICOLON {
        // First, apply the base type to all declarators in the list
        ASTNode *full_declarations = create_decl_list_node($1, $2);

        for (int i = 0; i < full_declarations->statement_list.count; i++) {
            ASTNode *decl = full_declarations->statement_list.statements[i];
            SymbolType symbol_kind = SYMBOL_VARIABLE;
            Type *decl_type = decl->var_decl.var_type; // Now decl_type should be fully formed
            Type *return_type = NULL;
            ASTNode *params = NULL;

            // Determine if it's a function declaration
            Type *temp_type = decl_type;
            while (temp_type && temp_type->base != TYPE_FUNCTION) {
                temp_type = temp_type->ptr_to;
            }
            if (temp_type && temp_type->base == TYPE_FUNCTION) {
                symbol_kind = SYMBOL_FUNCTION;
                return_type = temp_type->ptr_to; // The type pointed to by the function type is its return type
                params = temp_type->members; // Parameters are stored in members
            }

            if (!symtab_insert(symbol_table, decl->var_decl.name, symbol_kind, decl_type, return_type, params, 0)) {
                yyerror("Symbol already defined in current scope");
            }
        }
        $$ = full_declarations;
    }
    | declaration_specifiers T_SEMICOLON { $$ = create_type_decl_node($1); }
    | T_TYPEDEF declaration_specifiers init_declarator_list T_SEMICOLON {
        // Similar logic for typedefs: first build types, then add to symtab
        ASTNode *typedef_declarations = create_decl_list_node($2, $3); // $2 is base type for typedef
        for (int i = 0; i < typedef_declarations->statement_list.count; i++) {
            ASTNode *decl = typedef_declarations->statement_list.statements[i];
            add_typedef_name(symbol_table, decl->var_decl.name, decl->var_decl.var_type);
        }
        $$ = create_typedef_node(NULL, $2); // The node itself might not need all declarators
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
            // Combine base type from declaration_specifiers with declarator's type
            ASTNode *param_decl_node = $2;
            Type *base_type = $1;

            if (param_decl_node->var_decl.var_type == NULL) {
                param_decl_node->var_decl.var_type = base_type;
            } else {
                Type *t = param_decl_node->var_decl.var_type;
                while (t->ptr_to) {
                    t = t->ptr_to;
                }
                t->ptr_to = base_type;
            }

            // Now insert the fully formed type into the symbol table
            if (!symtab_insert(symbol_table, param_decl_node->var_decl.name, SYMBOL_VARIABLE, param_decl_node->var_decl.var_type, NULL, NULL, 0)) {
                yyerror("Symbol already defined in current scope");
            }
            $$ = param_decl_node;
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
    T_LBRACE { symtab_enter_scope(symbol_table); } T_RBRACE {
        $$ = create_statement_list_node();
        $$->statement_list.scope = symbol_table->current_scope;
        // symtab_exit_scope(symbol_table); // Defer scope exit until after codegen
        current_function_symbol = NULL; // Clear current function
    }
    | T_LBRACE { symtab_enter_scope(symbol_table); } block_item_list T_RBRACE {
        $$ = $3;
        $$->statement_list.scope = symbol_table->current_scope;
        // symtab_exit_scope(symbol_table); // Defer scope exit until after codegen
        current_function_symbol = NULL; // Clear current function
    }
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
    T_IDENTIFIER ':' statement {
        if (!symtab_insert(symbol_table, $1, SYMBOL_LABEL, NULL, NULL, NULL, 0)) {
            yyerror("Label already defined in current scope");
        }
        $$ = create_label_node($1, $3);
    }
    | T_CASE conditional_expression ':' statement { $$ = create_case_node($2); add_statement_to_list($$, $4); }
    | T_DEFAULT ':' statement { $$ = create_case_node(NULL); add_statement_to_list($$, $3); }
    | T_IDENTIFIER ':' T_SEMICOLON {
        if (!symtab_insert(symbol_table, $1, SYMBOL_LABEL, NULL, NULL, NULL, 0)) {
            yyerror("Label already defined in current scope");
        }
        $$ = create_label_node($1, NULL);
    }
    ;

selection_statement:
    T_IF T_LPAREN expression T_RPAREN statement %prec T_IFX {
        TypeAndOwnership cond_tao = get_expression_type($3);
        Type *cond_type = cond_tao.type;
        if (!is_scalar_type(cond_type)) {
            yyerror("if condition must be a scalar type");
        }
        if (cond_tao.is_newly_allocated) free_type(cond_type);
        $$ = create_if_node($3, $5, NULL);
    }
    | T_IF T_LPAREN expression T_RPAREN statement T_ELSE statement {
        TypeAndOwnership cond_tao = get_expression_type($3);
        Type *cond_type = cond_tao.type;
        if (!is_scalar_type(cond_type)) {
            yyerror("if condition must be a scalar type");
        }
        if (cond_tao.is_newly_allocated) free_type(cond_type);
        $$ = create_if_node($3, $5, $7);
    }
    | T_SWITCH T_LPAREN expression T_RPAREN statement { $$ = create_switch_node($3, $5); }
    ;

iteration_statement:
    T_WHILE T_LPAREN expression T_RPAREN statement {
        TypeAndOwnership cond_tao = get_expression_type($3);
        Type *cond_type = cond_tao.type;
        if (!is_scalar_type(cond_type)) {
            yyerror("while condition must be a scalar type");
        }
        if (cond_tao.is_newly_allocated) free_type(cond_type);
        $$ = create_while_node($3, $5);
    }
    | T_DO statement T_WHILE T_LPAREN expression T_RPAREN T_SEMICOLON {
        TypeAndOwnership cond_tao = get_expression_type($5);
        Type *cond_type = cond_tao.type;
        if (!is_scalar_type(cond_type)) {
            yyerror("do-while condition must be a scalar type");
        }
        if (cond_tao.is_newly_allocated) free_type(cond_type);
        $$ = create_do_while_node($2, $5);
    }
    | T_FOR T_LPAREN expression T_SEMICOLON expression T_SEMICOLON T_RPAREN statement {
        TypeAndOwnership cond_tao = get_expression_type($5);
        Type *cond_type = cond_tao.type;
        if (!is_scalar_type(cond_type)) {
            yyerror("for loop condition must be a scalar type");
        }
        if (cond_tao.is_newly_allocated) free_type(cond_type);
        $$ = create_for_node($3, $5, NULL, $8);
    }
    | T_FOR T_LPAREN expression T_SEMICOLON expression T_SEMICOLON expression T_RPAREN statement {
        TypeAndOwnership cond_tao = get_expression_type($5);
        Type *cond_type = cond_tao.type;
        if (!is_scalar_type(cond_type)) {
            yyerror("for loop condition must be a scalar type");
        }
        if (cond_tao.is_newly_allocated) free_type(cond_type);
        $$ = create_for_node($3, $5, $7, $9);
    }
    | T_FOR T_LPAREN declaration expression T_SEMICOLON T_RPAREN statement {
        TypeAndOwnership cond_tao = get_expression_type($4);
        Type *cond_type = cond_tao.type;
        if (!is_scalar_type(cond_type)) {
            yyerror("for loop condition must be a scalar type");
        }
        if (cond_tao.is_newly_allocated) free_type(cond_type);
        $$ = create_for_node($3, $4, NULL, $7);
    }
    | T_FOR T_LPAREN declaration expression T_SEMICOLON expression T_RPAREN statement {
        TypeAndOwnership cond_tao = get_expression_type($4);
        Type *cond_type = cond_tao.type;
        if (!is_scalar_type(cond_type)) {
            yyerror("for loop condition must be a scalar type");
        }
        if (cond_tao.is_newly_allocated) free_type(cond_type);
        $$ = create_for_node($3, $4, $6, $8);
    }
    ;

jump_statement:
    T_GOTO T_IDENTIFIER T_SEMICOLON { $$ = create_goto_node($2); }
    | T_CONTINUE T_SEMICOLON { $$ = create_continue_node(); }
    | T_BREAK T_SEMICOLON { $$ = create_break_node(); }
    | T_RETURN T_SEMICOLON {
        Symbol *func = get_current_function();
        if (func && func->return_type->base != TYPE_VOID) {
            yyerror("Non-void function must return a value");
        }
        $$ = create_return_node(NULL);
    }
    | T_RETURN expression T_SEMICOLON {
        Symbol *func = get_current_function();
        if (func) {
            TypeAndOwnership expr_tao = get_expression_type($2);
            Type *expr_type = expr_tao.type;
            if (!compare_types(expr_type, func->return_type)) {
                yyerror("Incompatible return type");
            }
            if (expr_tao.is_newly_allocated) free_type(expr_type);
        }
        $$ = create_return_node($2);
    }
    ;

expression:
    assignment_expression { $$ = $1; }
    | expression T_COMMA assignment_expression { $$ = create_binary_op_node(T_COMMA, $1, $3); }
    ;

assignment_expression:
    conditional_expression { $$ = $1; }
    | unary_expression T_ASSIGN assignment_expression {
        TypeAndOwnership left_tao = get_expression_type($1);
        Type *left_type = left_tao.type;
        TypeAndOwnership right_tao = get_expression_type($3);
        Type *right_type = right_tao.type;

        // C standard allows assignment of integer literal 0 to any pointer type (NULL)
        if (left_type && left_type->base == TYPE_POINTER &&
            $3 && $3->type == NODE_TYPE_INTEGER && $3->integer_value == 0) {
            // Valid NULL assignment, no error
        } else if (!compare_types(left_type, right_type)) {
            yyerror("Incompatible types in assignment");
        }
        if (left_tao.is_newly_allocated) free_type(left_type);
        if (right_tao.is_newly_allocated) free_type(right_type);
        $$ = create_assign_node($1, $3);
    }
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
    | logical_or_expression T_LOGICAL_OR logical_and_expression {
        TypeAndOwnership left_tao = get_expression_type($1);
        Type *left_type = left_tao.type;
        TypeAndOwnership right_tao = get_expression_type($3);
        Type *right_type = right_tao.type;
        // In C, any scalar type can be used in a logical context.
        // Non-zero values are true, zero is false.
        // We'll assume if we get a type, it's a scalar.
        if (left_type == NULL || right_type == NULL || left_type->base == TYPE_VOID || right_type->base == TYPE_VOID) {
            yyerror("Logical operators require scalar operands");
        }
        if (left_tao.is_newly_allocated) free_type(left_type);
        if (right_tao.is_newly_allocated) free_type(right_type);
        $$ = create_binary_op_node(T_LOGICAL_OR, $1, $3);
    }
    ;

logical_and_expression:
    inclusive_or_expression { $$ = $1; }
    | logical_and_expression T_LOGICAL_AND inclusive_or_expression {
        TypeAndOwnership left_tao = get_expression_type($1);
        Type *left_type = left_tao.type;
        TypeAndOwnership right_tao = get_expression_type($3);
        Type *right_type = right_tao.type;
        // In C, any scalar type can be used in a logical context.
        // Non-zero values are true, zero is false.
        // We'll assume if we get a type, it's a scalar.
        if (left_type == NULL || right_type == NULL || left_type->base == TYPE_VOID || right_type->base == TYPE_VOID) {
            yyerror("Logical operators require scalar operands");
        }
        if (left_tao.is_newly_allocated) free_type(left_type);
        if (right_tao.is_newly_allocated) free_type(right_type);
        $$ = create_binary_op_node(T_LOGICAL_AND, $1, $3);
    }
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
    | equality_expression T_EQ relational_expression {
        TypeAndOwnership left_tao = get_expression_type($1);
        Type *left_type = left_tao.type;
        TypeAndOwnership right_tao = get_expression_type($3);
        Type *right_type = right_tao.type;
        if (!compare_types(left_type, right_type)) {
            yyerror("Equality operators require operands of compatible types");
        }
        if (left_tao.is_newly_allocated) free_type(left_type);
        if (right_tao.is_newly_allocated) free_type(right_type);
        $$ = create_binary_op_node(T_EQ, $1, $3);
    }
    | equality_expression T_NE relational_expression {
        TypeAndOwnership left_tao = get_expression_type($1);
        Type *left_type = left_tao.type;
        TypeAndOwnership right_tao = get_expression_type($3);
        Type *right_type = right_tao.type;
        if (!compare_types(left_type, right_type)) {
            yyerror("Equality operators require operands of compatible types");
        }
        if (left_tao.is_newly_allocated) free_type(left_type);
        if (right_tao.is_newly_allocated) free_type(right_type);
        $$ = create_binary_op_node(T_NE, $1, $3);
    }
    ;

relational_expression:
    shift_expression { $$ = $1; }
    | relational_expression T_LT shift_expression {
        TypeAndOwnership left_tao = get_expression_type($1);
        Type *left_type = left_tao.type;
        TypeAndOwnership right_tao = get_expression_type($3);
        Type *right_type = right_tao.type;
        // Relational operators require arithmetic types (integer or float)
        if (left_type == NULL || right_type == NULL || left_type->base == TYPE_VOID || right_type->base == TYPE_VOID ||
            (!is_arithmetic_type(left_type) || !is_arithmetic_type(right_type))) {
            yyerror("Relational operators require arithmetic operands");
        }
        if (left_tao.is_newly_allocated) free_type(left_type);
        if (right_tao.is_newly_allocated) free_type(right_type);
        $$ = create_binary_op_node(T_LT, $1, $3);
    }
    | relational_expression T_GT shift_expression {
        TypeAndOwnership left_tao = get_expression_type($1);
        Type *left_type = left_tao.type;
        TypeAndOwnership right_tao = get_expression_type($3);
        Type *right_type = right_tao.type;
        if (left_type == NULL || right_type == NULL || left_type->base == TYPE_VOID || right_type->base == TYPE_VOID ||
            (!is_arithmetic_type(left_type) || !is_arithmetic_type(right_type))) {
            yyerror("Relational operators require arithmetic operands");
        }
        if (left_tao.is_newly_allocated) free_type(left_type);
        if (right_tao.is_newly_allocated) free_type(right_type);
        $$ = create_binary_op_node(T_GT, $1, $3);
    }
    | relational_expression T_LE shift_expression {
        TypeAndOwnership left_tao = get_expression_type($1);
        Type *left_type = left_tao.type;
        TypeAndOwnership right_tao = get_expression_type($3);
        Type *right_type = right_tao.type;
        if (left_type == NULL || right_type == NULL || left_type->base == TYPE_VOID || right_type->base == TYPE_VOID ||
            (!is_arithmetic_type(left_type) || !is_arithmetic_type(right_type))) {
            yyerror("Relational operators require arithmetic operands");
        }
        if (left_tao.is_newly_allocated) free_type(left_type);
        if (right_tao.is_newly_allocated) free_type(right_type);
        $$ = create_binary_op_node(T_LE, $1, $3);
    }
    | relational_expression T_GE shift_expression {
        TypeAndOwnership left_tao = get_expression_type($1);
        Type *left_type = left_tao.type;
        TypeAndOwnership right_tao = get_expression_type($3);
        Type *right_type = right_tao.type;
        if (left_type == NULL || right_type == NULL || left_type->base == TYPE_VOID || right_type->base == TYPE_VOID ||
            (!is_arithmetic_type(left_type) || !is_arithmetic_type(right_type))) {
            yyerror("Relational operators require arithmetic operands");
        }
        if (left_tao.is_newly_allocated) free_type(left_type);
        if (right_tao.is_newly_allocated) free_type(right_type);
        $$ = create_binary_op_node(T_GE, $1, $3);
    }
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
    | T_MUL cast_expression {
        TypeAndOwnership operand_tao = get_expression_type($2);
        Type *operand_type = operand_tao.type;
        if (operand_type == NULL || operand_type->base != TYPE_POINTER) {
            yyerror("Dereference operator can only be applied to pointers");
        }
        if (operand_tao.is_newly_allocated) free_type(operand_type);
        $$ = create_unary_op_node(T_MUL, $2);
    }
    | T_ADD cast_expression { $$ = $2; }
    | T_SUB cast_expression { $$ = create_unary_op_node(T_SUB, $2); }
    | T_BITWISE_NOT cast_expression { $$ = create_unary_op_node(T_BITWISE_NOT, $2); }
    | T_LOGICAL_NOT cast_expression {
        TypeAndOwnership operand_tao = get_expression_type($2);
        Type *operand_type = operand_tao.type;
        // In C, logical NOT can be applied to any scalar type.
        // Non-zero values are true, zero is false.
        if (operand_type == NULL || operand_type->base == TYPE_VOID) {
            yyerror("Logical NOT operator requires a scalar operand");
        }
        if (operand_tao.is_newly_allocated) free_type(operand_type);
        $$ = create_unary_op_node(T_LOGICAL_NOT, $2);
    }
    | T_SIZEOF unary_expression { $$ = create_sizeof_node(NULL); }
    | T_SIZEOF T_LPAREN type_name T_RPAREN { $$ = create_sizeof_node($3); }
    ;

postfix_expression:
    primary_expression { $$ = $1; }
    | postfix_expression T_LBRACKET expression T_RBRACKET {
        TypeAndOwnership array_tao = get_expression_type($1);
        Type *array_type = array_tao.type;
        if (array_type == NULL || array_type->base != TYPE_ARRAY) {
            yyerror("[] operator can only be used with arrays");
        }
        TypeAndOwnership index_tao = get_expression_type($3);
        Type *index_type = index_tao.type;
        if (index_type == NULL || index_type->base != TYPE_INT) {
            yyerror("Array index must be an integer");
        }
        if (array_tao.is_newly_allocated) free_type(array_type);
        if (index_tao.is_newly_allocated) free_type(index_type);
        $$ = create_array_access_node($1, $3);
    }
    | postfix_expression T_LPAREN T_RPAREN {
        check_function_call($1->variable.name, NULL);
        $$ = create_func_call_node($1->variable.name, NULL);
    }
    | postfix_expression T_LPAREN argument_expression_list T_RPAREN {
        check_function_call($1->variable.name, $3);
        $$ = create_func_call_node($1->variable.name, $3);
    }
    | postfix_expression T_DOT T_IDENTIFIER { $$ = create_member_access_node(T_DOT, $1, $3); }
    | postfix_expression T_ARROW T_IDENTIFIER { $$ = create_member_access_node(T_ARROW, $1, $3); }
    | postfix_expression T_INC { $$ = create_unary_op_node(T_INC, $1); }
    | postfix_expression T_DEC { $$ = create_unary_op_node(T_DEC, $1); }
    ;

primary_expression:
    T_IDENTIFIER {
        Symbol *s = symtab_lookup(symbol_table, $1);
        if (s == NULL) {
            yyerror("Symbol not defined");
        } else if (s->type == SYMBOL_ENUMERATOR) {
            $$ = create_integer_node(s->enum_value); // Treat enumerator as integer constant
        } else {
            $$ = create_variable_node($1);
        }
    }
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
    T_BOOL { $$ = create_type(TYPE_BOOL); }
    | T_VOID { $$ = create_type(TYPE_VOID); }
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
    T_STRUCT T_IDENTIFIER T_LBRACE struct_declaration_list T_RBRACE {
        ASTNode *node = create_struct_def_node($2, $4);
        Type *type = create_type_from_specifier(node);
        type->members = $4; // Store the member list in the Type structure
        $$ = node;
    }
    | T_STRUCT T_LBRACE struct_declaration_list T_RBRACE {
        ASTNode *node = create_struct_def_node(NULL, $3);
        Type *type = create_type_from_specifier(node);
        type->members = $3; // Store the member list in the Type structure
        $$ = node;
    }
    | T_STRUCT T_IDENTIFIER { $$ = create_struct_ref_node($2); }
    ;

union_specifier:
    T_UNION T_IDENTIFIER T_LBRACE struct_declaration_list T_RBRACE {
        ASTNode *node = create_union_def_node($2, $4);
        Type *type = create_type_from_union_specifier(node);
        type->members = $4; // Store the member list in the Type structure
        $$ = node;
    }
    | T_UNION T_LBRACE struct_declaration_list T_RBRACE {
        ASTNode *node = create_union_def_node(NULL, $3);
        Type *type = create_type_from_union_specifier(node);
        type->members = $3; // Store the member list in the Type structure
        $$ = node;
    }
    | T_UNION T_IDENTIFIER { $$ = create_union_ref_node($2); }
    ;

enum_specifier:
    T_ENUM T_IDENTIFIER T_LBRACE { symtab_enter_scope(symbol_table); current_enum_value = 0; } enumerator_list T_RBRACE {
        $$ = create_enum_specifier_node($2, $5);
        $$->enum_specifier.scope = symbol_table->current_scope;
        symtab_exit_scope(symbol_table);
    }
    | T_ENUM T_LBRACE { symtab_enter_scope(symbol_table); current_enum_value = 0; } enumerator_list T_RBRACE {
        $$ = create_enum_specifier_node(NULL, $4);
        $$->enum_specifier.scope = symbol_table->current_scope;
        symtab_exit_scope(symbol_table);
    }
    | T_ENUM T_IDENTIFIER { $$ = create_enum_specifier_node($2, NULL); }
    ;

enumerator_list:
    enumerator { $$ = create_statement_list_node(); add_statement_to_list($$, $1); }
    | enumerator_list T_COMMA enumerator { add_statement_to_list($1, $3); $$ = $1; }
    ;

enumerator:
    T_IDENTIFIER {
        if (!symtab_insert(symbol_table, $1, SYMBOL_ENUMERATOR, create_type(TYPE_INT), NULL, NULL, current_enum_value)) {
            yyerror("Enumerator already defined in current scope");
        }
        $$ = create_enumerator_node($1, create_integer_node(current_enum_value++));
    }
    | T_IDENTIFIER T_ASSIGN conditional_expression {
        TypeAndOwnership expr_tao = get_expression_type($3);
        Type *expr_type = expr_tao.type;
        if (expr_type == NULL || expr_type->base != TYPE_INT) {
            yyerror("Enumerator value must be an integer constant");
        }
        // Extract the integer value from the expression if it's a constant
        int assigned_value = 0;
        if ($3->type == NODE_TYPE_INTEGER) {
            assigned_value = $3->integer_value;
        } else {
            yyerror("Enumerator value must be an integer constant");
        }

        if (!symtab_insert(symbol_table, $1, SYMBOL_ENUMERATOR, create_type(TYPE_INT), NULL, NULL, assigned_value)) {
            yyerror("Enumerator already defined in current scope");
        }
        $$ = create_enumerator_node($1, $3);
        // Reset current_enum_value for the next enumerator if it's explicitly assigned
        current_enum_value = assigned_value + 1;
        if (expr_tao.is_newly_allocated) free_type(expr_type);
    }
    ;

struct_declaration_list:
    struct_declaration { $$ = create_statement_list_node(); add_statement_to_list($$, $1); }
    | struct_declaration_list struct_declaration { add_statement_to_list($1, $2); $$ = $1; }
    ;

struct_declaration:
    declaration_specifiers declarator_list T_SEMICOLON {
        // Apply the base type ($1) to each declarator in the list ($2)
        ASTNode *declarator_list_node = $2; // This is a STATEMENT_LIST of VAR_DECLs
        Type *base_type = $1;

        for (int i = 0; i < declarator_list_node->statement_list.count; i++) {
            ASTNode *decl = declarator_list_node->statement_list.statements[i];
            if (decl->var_decl.var_type == NULL) {
                decl->var_decl.var_type = base_type;
            } else {
                Type *t = decl->var_decl.var_type;
                while (t->ptr_to) {
                    t = t->ptr_to;
                }
                t->ptr_to = base_type;
            }
        }
        $$ = declarator_list_node; // Return the list of typed declarations
    }
    ;

declarator_list:
    declarator { $$ = create_statement_list_node(); add_statement_to_list($$, $1); }
    | declarator_list T_COMMA declarator { add_statement_to_list($1, $3); $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "DEBUG: yyerror: Parse error on line %d: %s near '%s'\n", yylineno, s, yytext);
}

void check_function_call(char *name, ASTNode *args) {
    Symbol *s = symtab_lookup(symbol_table, name);
    if (s == NULL) {
        yyerror("Function not defined");
        return;
    }
    if (s->type != SYMBOL_FUNCTION) {
        yyerror("Identifier is not a function");
        return;
    }
    fprintf(stderr, "DEBUG: check_function_call: Checking call to function '%s'\n", name);

    // Special handling for printf (variadic function)
    if (strcmp(name, "printf") == 0) {
        // For printf, we only check the first argument (format string) if it exists
        // A more robust solution would would involve proper varargs handling
        if (args && args->arg_list.count > 0) {
            ASTNode *first_arg = args->arg_list.args[0];
            TypeAndOwnership first_arg_tao = get_expression_type(first_arg);
            Type *first_arg_type = first_arg_tao.type;
            // Expecting a char* for the format string
            Type *expected_type = create_pointer_type(create_type(TYPE_CHAR));
            if (!compare_types(first_arg_type, expected_type)) {
                yyerror("Incompatible type for printf format string");
            }
        }
        return;
    }

    int num_args = args ? args->arg_list.count : 0;
    int num_params = s->params ? s->params->param_list.count : 0;

    if (num_args != num_params) {
        yyerror("Incorrect number of arguments in function call");
        return;
    }

        for (int i = 0; i < num_args; i++) {
            ASTNode *arg = args->arg_list.args[i];
            TypeAndOwnership arg_tao = get_expression_type(arg);
            Type *arg_type = arg_tao.type;
            Type *param_type = s->params->param_list.params[i]->var_decl.var_type;
            fprintf(stderr, "DEBUG: check_function_call: Comparing arg type ");
            print_type(arg_type, stderr);
            fprintf(stderr, " with param type ");
            print_type(param_type, stderr);
            fprintf(stderr, "\n");
            if (!compare_types(arg_type, param_type)) {
                yyerror("Incompatible argument type in function call");
            }
        }
    }

int compare_types(Type *a, Type *b) {
    if (a == NULL || b == NULL) {
        return 0; // Cannot compare with unknown types
    }

    // Resolve typedefs to their actual types before comparison
    if (a->base == TYPE_TYPEDEF) {
        Type *resolved_a = get_typedef_type(symbol_table, a->name);
        if (resolved_a) {
            a = resolved_a;
        }
    }
    if (b->base == TYPE_TYPEDEF) {
        Type *resolved_b = get_typedef_type(symbol_table, b->name);
        if (resolved_b) {
            b = resolved_b;
        }
    }

    // If types are identical, they are compatible
    if (a->base == b->base && a->is_signed == b->is_signed && a->is_const == b->is_const) {
        if (a->base == TYPE_POINTER) {
            return compare_types(a->ptr_to, b->ptr_to);
        }
        if (a->base == TYPE_ARRAY) {
            // Arrays are compatible if their base types are compatible and sizes match (if specified)
            if (a->array_size != 0 && b->array_size != 0 && a->array_size != b->array_size) {
                return 0;
            }
            return compare_types(a->ptr_to, b->ptr_to);
        }
        if ((a->base == TYPE_STRUCT || a->base == TYPE_UNION || a->base == TYPE_ENUM) && a->name && b->name) {
            return strcmp(a->name, b->name) == 0;
        }
        return 1;
    }

    // Implicit conversions for arithmetic types
    int a_is_integer = (a->base == TYPE_CHAR || a->base == TYPE_SHORT || a->base == TYPE_INT || a->base == TYPE_LONG || a->base == TYPE_BOOL);
    int b_is_integer = (b->base == TYPE_CHAR || b->base == TYPE_SHORT || b->base == TYPE_INT || b->base == TYPE_LONG || b->base == TYPE_BOOL);

    // All integer types are compatible for implicit conversion
    if (a_is_integer && b_is_integer) {
        return 1;
    }

    // Promotion from integer to float/double
    if ((a_is_integer && (b->base == TYPE_FLOAT || b->base == TYPE_DOUBLE)) ||
        (b_is_integer && (a->base == TYPE_FLOAT || a->base == TYPE_DOUBLE))) {
        return 1;
    }

    // Pointer to void* and vice-versa
    if (a->base == TYPE_POINTER && b->base == TYPE_POINTER) {
        if ((a->ptr_to && a->ptr_to->base == TYPE_VOID) || (b->ptr_to && b->ptr_to->base == TYPE_VOID)) {
            return 1; // void* is compatible with any other pointer type
        }
        // Allow comparison of any two pointers to object types
        // C standard allows comparison of pointers to compatible types, or one to void*
        // For simplicity, allow comparison if base types of pointed-to types are compatible
        if (a->ptr_to && b->ptr_to && compare_types(a->ptr_to, b->ptr_to)) {
            return 1;
        }
    }

    // Array to pointer decay (e.g., int[] to int*)
    if (a->base == TYPE_ARRAY && b->base == TYPE_POINTER) {
        return compare_types(a->ptr_to, b->ptr_to);
    }
    if (b->base == TYPE_ARRAY && a->base == TYPE_POINTER) {
        return compare_types(b->ptr_to, a->ptr_to);
    }

    // Allow comparison/assignment of integer literal 0 to any pointer type (NULL)
    // This is a common implicit conversion.
    if ((a->base == TYPE_POINTER && b->base == TYPE_INT) || (b->base == TYPE_POINTER && a->base == TYPE_INT)) {
        return 1;
    }

    // Allow assignment of integer literal 0 to any pointer type (NULL)
    // This check requires the actual expression node, which is not available in compare_types.
    // This should be handled at the call site of compare_types (e.g., in assignment_expression).
    // if ((a->base == TYPE_POINTER && b->base == TYPE_INT && expr && expr->type == NODE_TYPE_INTEGER && expr->integer_value == 0) ||
    //     (b->base == TYPE_POINTER && a->base == TYPE_INT && expr && expr->type == NODE_TYPE_INTEGER && expr->integer_value == 0)) {
    //     return 1;
    // }

    return 0; // Types are not compatible
}

Symbol *get_current_function() {
    return current_function_symbol;
}

TypeAndOwnership get_expression_type(ASTNode *expr) {
    TypeAndOwnership result = { .type = create_type(TYPE_VOID), .is_newly_allocated = false };

    if (!expr) {
        return result;
    }

    switch (expr->type) {
        case NODE_TYPE_VARIABLE: {
            Symbol *s = symtab_lookup(symbol_table, expr->variable.name);
            if (s) {
                if (s->type == SYMBOL_ENUMERATOR) {
                    result.type = create_type(TYPE_INT); // Global singleton
                    result.is_newly_allocated = false;
                    return result;
                }
                // Resolve typedefs to their actual types
                if (s->data_type && s->data_type->base == TYPE_TYPEDEF) {
                    Type *resolved_type = get_typedef_type(symbol_table, s->data_type->name);
                    if (resolved_type) {
                        result.type = resolved_type;
                        result.is_newly_allocated = false; // Type is from symtab or global
                        return result;
                    }
                }
                result.type = s->data_type;
                result.is_newly_allocated = false; // Type is from symtab or global
                return result;
            }
            yyerror("Unknown variable type");
            return result; // Returns TYPE_VOID, not newly allocated
        }
        case NODE_TYPE_INTEGER:
            result.type = create_type(TYPE_INT);
            result.is_newly_allocated = false;
            return result;
        case NODE_TYPE_FLOAT:
            result.type = create_type(TYPE_FLOAT);
            result.is_newly_allocated = false;
            return result;
        case NODE_TYPE_CHAR:
            result.type = create_type(TYPE_CHAR);
            result.is_newly_allocated = false;
            return result;
        case NODE_TYPE_STRING_LITERAL:
            result.type = create_pointer_type(create_type(TYPE_CHAR)); // create_pointer_type allocates a new Type
            result.is_newly_allocated = true;
            return result;
        case NODE_TYPE_BINARY_OP: {
            TypeAndOwnership left_tao = get_expression_type(expr->binary_op.left);
            TypeAndOwnership right_tao = get_expression_type(expr->binary_op.right);
            Type *left_type = left_tao.type;
            Type *right_type = right_tao.type;

            // Handle cases where types might be unknown or void
            if (!left_type || left_type->base == TYPE_VOID || !right_type || right_type->base == TYPE_VOID) {
                yyerror("Invalid operand type for binary operation");
                // Free any newly allocated types from children
                if (right_tao.is_newly_allocated) free_type(right_type);
                return result; // Returns TYPE_VOID, not newly allocated
            }

            // Type promotion rules (simplified C rules)
            // If either operand is float/double, result is float/double
            if (left_type->base == TYPE_FLOAT || right_type->base == TYPE_FLOAT) {
                result.type = create_type(TYPE_FLOAT);
                result.is_newly_allocated = false;
            } else if (left_type->base == TYPE_DOUBLE || right_type->base == TYPE_DOUBLE) {
                result.type = create_type(TYPE_DOUBLE);
                result.is_newly_allocated = false;
            }
            // If either operand is a pointer, result is a pointer (for pointer arithmetic)
            else if (left_type->base == TYPE_POINTER && is_arithmetic_type(right_type)) {
                result.type = left_type;
                result.is_newly_allocated = false; // This type is from left_tao, not newly allocated here
            } else if (right_type->base == TYPE_POINTER && is_arithmetic_type(left_type)) {
                result.type = right_type;
                result.is_newly_allocated = false; // This type is from right_tao, not newly allocated here
            }
            // Pointer subtraction results in ptrdiff_t (int for simplicity)
            else if (left_type->base == TYPE_POINTER && right_type->base == TYPE_POINTER) {
                // Ensure pointers are compatible for subtraction
                if (!compare_types(left_type, right_type)) {
                    yyerror("Incompatible pointer types for subtraction");
                    // Free any newly allocated types from children
                    if (left_tao.is_newly_allocated) free_type(left_type);
                    if (right_tao.is_newly_allocated) free_type(right_type);
                    return result; // Returns TYPE_VOID, not newly allocated
                }
                result.type = create_type(TYPE_INT);
                result.is_newly_allocated = false;
            }
            // Logical and relational operators return BOOL
            else if (expr->binary_op.op == T_LOGICAL_AND || expr->binary_op.op == T_LOGICAL_OR ||
                       expr->binary_op.op == T_EQ || expr->binary_op.op == T_NE ||
                       expr->binary_op.op == T_LT || expr->binary_op.op == T_LE ||
                       expr->binary_op.op == T_GT || expr->binary_op.op == T_GE) {
                result.type = create_type(TYPE_BOOL);
                result.is_newly_allocated = false;
            }
            // Default for other binary ops (arithmetic, bitwise) is INT
            else {
                result.type = create_type(TYPE_INT);
                result.is_newly_allocated = false;
            }

            // Free any newly allocated types from children that are not the result type
            if (left_tao.is_newly_allocated && left_type != result.type) free_type(left_type);
            if (right_tao.is_newly_allocated && right_type != result.type) free_type(right_type);
            return result;
        }
        case NODE_TYPE_UNARY_OP: {
            TypeAndOwnership operand_tao = get_expression_type(expr->unary_op.operand);
            Type *operand_type = operand_tao.type;

            if (!operand_type || operand_type->base == TYPE_VOID) {
                yyerror("Invalid operand type for unary operation");
                if (operand_tao.is_newly_allocated) free_type(operand_type);
                return result; // Returns TYPE_VOID, not newly allocated
            }

            if (expr->unary_op.op == T_BITWISE_AND) { // Address-of operator
                result.type = create_pointer_type(operand_type); // create_pointer_type allocates a new Type
                result.is_newly_allocated = true;
            } else if (expr->unary_op.op == T_MUL) { // Dereference operator
                if (operand_type->base == TYPE_POINTER) {
                    result.type = operand_type->ptr_to;
                    result.is_newly_allocated = false; // Type pointed to is not newly allocated here
                } else {
                    yyerror("Dereference operator can only be applied to pointers");
                    if (operand_tao.is_newly_allocated) free_type(operand_type);
                    return result; // Returns TYPE_VOID, not newly allocated
                }
            } else if (expr->unary_op.op == T_LOGICAL_NOT) { // Logical NOT returns BOOL
                if (!is_scalar_type(operand_type)) {
                    yyerror("Logical NOT operator requires a scalar operand");
                    if (operand_tao.is_newly_allocated) free_type(operand_type);
                    return result; // Returns TYPE_VOID, not newly allocated
                }
                result.type = create_type(TYPE_BOOL);
                result.is_newly_allocated = false;
            } else if (expr->unary_op.op == T_SUB) { // Unary negation
                if (!is_arithmetic_type(operand_type)) {
                    yyerror("Unary negation operator requires an arithmetic operand");
                    if (operand_tao.is_newly_allocated) free_type(operand_type);
                    return result; // Returns TYPE_VOID, not newly allocated
                }
                result.type = operand_type; // Type remains the same
                result.is_newly_allocated = false;
            } else if (expr->unary_op.op == T_BITWISE_NOT) { // Bitwise NOT
                if (!is_integer_type(operand_type)) {
                    yyerror("Bitwise NOT operator requires an integer operand");
                    if (operand_tao.is_newly_allocated) free_type(operand_type);
                    return result; // Returns TYPE_VOID, not newly allocated
                }
                result.type = operand_type; // Type remains the same
                result.is_newly_allocated = false;
            } else {
                // For increment/decrement, the type remains the same
                result.type = operand_type;
                result.is_newly_allocated = false;
            }

            // Free operand_type if it was newly allocated and not part of the result
            if (operand_tao.is_newly_allocated && operand_type != result.type) free_type(operand_type);
            return result;
        }
        case NODE_TYPE_FUNC_CALL: {
            Symbol *s = symtab_lookup(symbol_table, expr->func_call.name);
            result.type = s ? s->return_type : create_type(TYPE_VOID);
            result.is_newly_allocated = false; // Return type is from symtab or global
            return result;
        }
        case NODE_TYPE_ARRAY_ACCESS: {
            TypeAndOwnership array_tao = get_expression_type(expr->array_access.array);
            TypeAndOwnership index_tao = get_expression_type(expr->array_access.index);
            Type *array_type = array_tao.type;
            Type *index_type = index_tao.type;

            if (!array_type) {
                yyerror("Array access on unknown type");
                if (array_tao.is_newly_allocated) free_type(array_type);
                if (index_tao.is_newly_allocated) free_type(index_type);
                return result; // Returns TYPE_VOID, not newly allocated
            }

            // Array access can be on an array type or a pointer type
            if (array_type->base == TYPE_ARRAY) {
                array_type = array_type->ptr_to; // Decay array to pointer to its element type
            } else if (array_type->base != TYPE_POINTER) {
                yyerror("[] operator can only be used with arrays or pointers");
                if (array_tao.is_newly_allocated) free_type(array_type);
                if (index_tao.is_newly_allocated) free_type(index_type);
                return result; // Returns TYPE_VOID, not newly allocated
            }

            if (!is_integer_type(index_type)) { // Index must be an integer type
                yyerror("Array index must be an integer type");
                if (array_tao.is_newly_allocated) free_type(array_type);
                if (index_tao.is_newly_allocated) free_type(index_type);
                return result; // Returns TYPE_VOID, not newly allocated
            }
            result.type = array_type->ptr_to; // Return the type pointed to by the (possibly decayed) array/pointer
            result.is_newly_allocated = false; // This type is from array_type, not newly allocated here

            // Free any newly allocated types from children that are not the result type
            if (array_tao.is_newly_allocated && array_type != result.type) free_type(array_type);
            if (index_tao.is_newly_allocated && index_type != result.type) free_type(index_type);
            return result;
        }
        case NODE_TYPE_MEMBER_ACCESS: {
            TypeAndOwnership base_tao = get_expression_type(expr->member_access.struct_or_union);
            Type *base_type = base_tao.type;

            if (!base_type) {
                yyerror("Member access on unknown type");
                if (base_tao.is_newly_allocated) free_type(base_type);
                return result; // Returns TYPE_VOID, not newly allocated
            }
            fprintf(stderr, "DEBUG: get_expression_type (MEMBER_ACCESS): Base type: ");
            print_type(base_type, stderr);
            fprintf(stderr, ", Member name: %s\n", expr->member_access.member_name);

            // If accessing through a pointer (e.g., ptr->member), dereference the pointer type
            if (expr->member_access.op == T_ARROW) { // Check if it's the arrow operator
                if (base_type->base == TYPE_POINTER) {
                    base_type = base_type->ptr_to;
                } else {
                    yyerror("Arrow operator can only be applied to pointer to struct/union types");
                    if (base_tao.is_newly_allocated) free_type(base_type);
                    return result; // Returns TYPE_VOID, not newly allocated
                }
            }

            if (base_type->base != TYPE_STRUCT && base_type->base != TYPE_UNION) {
                yyerror("Member access operator can only be used with struct/union types");
                if (base_tao.is_newly_allocated) free_type(base_type);
                return result; // Returns TYPE_VOID, not newly allocated
            }

            // Look up the member in the struct/union's members list
            /* base_type was resolved (STRUCT/UNION), handle . / -> , and now we search members */
            if (base_type->members && base_type->members->type == NODE_TYPE_STATEMENT_LIST) {
                int top_count = base_type->members->statement_list.count;
                for (int i = 0; i < top_count; i++) {
                    ASTNode *item = base_type->members->statement_list.statements[i];

                    if (item->type == NODE_TYPE_VAR_DECL) {
                        if (item->var_decl.name &&
                            strcmp(item->var_decl.name, expr->member_access.member_name) == 0) {
                            /* return TypeAndOwnership (not raw Type*) */
                            return (TypeAndOwnership){ .type = item->var_decl.var_type, .is_newly_allocated = false };
                        }
                    } else if (item->type == NODE_TYPE_STATEMENT_LIST) {
                        /* nested list of VAR_DECLs */
                        int m = item->statement_list.count;
                        for (int j = 0; j < m; j++) {
                            ASTNode *mem = item->statement_list.statements[j];
                            if (mem->type == NODE_TYPE_VAR_DECL &&
                                mem->var_decl.name &&
                                strcmp(mem->var_decl.name, expr->member_access.member_name) == 0) {
                                return (TypeAndOwnership){ .type = mem->var_decl.var_type, .is_newly_allocated = false };
                            }
                        }
                    } else if (item->type == NODE_TYPE_DECL_LIST) {
                        /* legacy shape: list of VAR_DECLs under a DECL_LIST */
                        int k = item->statement_list.count;
                        for (int j = 0; j < k; j++) {
                            ASTNode *mem = item->statement_list.statements[j];
                            if (mem->type == NODE_TYPE_VAR_DECL &&
                                mem->var_decl.name &&
                                strcmp(mem->var_decl.name, expr->member_access.member_name) == 0) {
                                return (TypeAndOwnership){ .type = mem->var_decl.var_type, .is_newly_allocated = false };
                            }
                        }
                    }
                }
            }

            /* If not found, report and return a safe value */
            yyerror("Member not found in struct/union");
            return (TypeAndOwnership){ .type = create_type(TYPE_VOID), .is_newly_allocated = true };

                    }
        case NODE_TYPE_CAST: {
            TypeAndOwnership expr_tao = get_expression_type(expr->cast.expr);
            Type *expr_type = expr_tao.type;
            result.type = expr->cast.to_type;
            result.is_newly_allocated = false; // Cast type is from AST, not newly allocated here

            if (expr_tao.is_newly_allocated) free_type(expr_type);
            return result;
        }
        case NODE_TYPE_TERNARY_OP: {
            TypeAndOwnership cond_tao = get_expression_type(expr->ternary_op.condition);
            TypeAndOwnership true_tao = get_expression_type(expr->ternary_op.true_expr);
            TypeAndOwnership false_tao = get_expression_type(expr->ternary_op.false_expr);
            Type *condition_type = cond_tao.type;
            Type *true_type = true_tao.type;
            Type *false_type = false_tao.type;

            if (!is_scalar_type(condition_type)) {
                yyerror("Ternary operator condition must be a scalar type");
                if (cond_tao.is_newly_allocated) free_type(condition_type);
                if (true_tao.is_newly_allocated) free_type(true_type);
                if (false_tao.is_newly_allocated) free_type(false_type);
                return result; // Returns TYPE_VOID, not newly allocated
            }

            if (!true_type || !false_type) {
                yyerror("Invalid operand type for ternary operator");
                if (cond_tao.is_newly_allocated) free_type(condition_type);
                if (true_tao.is_newly_allocated) free_type(true_type);
                if (false_tao.is_newly_allocated) free_type(false_type);
                return result; // Returns TYPE_VOID, not newly allocated
            }

            // C standard rules for ternary operator result type:
            // If both are arithmetic, usual arithmetic conversions apply.
            // If both are compatible pointer types, or one is NULL, result is that pointer type.
            // If one is void* and other is object pointer, result is void*.
            // Otherwise, types are incompatible.

            if (is_arithmetic_type(true_type) && is_arithmetic_type(false_type)) {
                // Simplified: if one is float/double, result is float/double, else int
                if (true_type->base == TYPE_DOUBLE || false_type->base == TYPE_DOUBLE) result.type = create_type(TYPE_DOUBLE);
                else if (true_type->base == TYPE_FLOAT || false_type->base == TYPE_FLOAT) result.type = create_type(TYPE_FLOAT);
                else result.type = create_type(TYPE_INT);
                result.is_newly_allocated = false;
            } else if (true_type->base == TYPE_POINTER && false_type->base == TYPE_POINTER) {
                if (compare_types(true_type, false_type)) {
                    result.type = true_type; // Compatible pointer types
                    result.is_newly_allocated = false;
                } else {
                    yyerror("Incompatible pointer types in ternary operator expressions");
                    if (cond_tao.is_newly_allocated) free_type(condition_type);
                    if (true_tao.is_newly_allocated) free_type(true_type);
                    if (false_tao.is_newly_allocated) free_type(false_type);
                    return result; // Returns TYPE_VOID, not newly allocated
                }
            } else if ((true_type->base == TYPE_POINTER && false_type->base == TYPE_INT && expr->ternary_op.false_expr->type == NODE_TYPE_INTEGER && expr->ternary_op.false_expr->integer_value == 0) ||
                       (false_type->base == TYPE_POINTER && true_type->base == TYPE_INT && expr->ternary_op.true_expr->type == NODE_TYPE_INTEGER && expr->ternary_op.true_expr->integer_value == 0)) {
                // One is a pointer, other is integer literal 0 (NULL)
                result.type = (true_type->base == TYPE_POINTER) ? true_type : false_type;
                result.is_newly_allocated = false;
            } else {
                yyerror("Incompatible types in ternary operator expressions");
                if (cond_tao.is_newly_allocated) free_type(condition_type);
                if (true_tao.is_newly_allocated) free_type(true_type);
                if (false_tao.is_newly_allocated) free_type(false_type);
                return result; // Returns TYPE_VOID, not newly allocated
            }

            // Free any newly allocated types from children that are not the result type
            if (cond_tao.is_newly_allocated && condition_type != result.type) free_type(condition_type);
            if (true_tao.is_newly_allocated && true_type != result.type) free_type(true_type);
            if (false_tao.is_newly_allocated && false_type != result.type) free_type(false_type);
            return result;
        }
        case NODE_TYPE_ENUMERATOR:
            result.type = create_type(TYPE_INT); // Global singleton
            result.is_newly_allocated = false;
            return result;
        case NODE_TYPE_SIZEOF:
            result.type = create_type(TYPE_INT); // Global singleton
            result.is_newly_allocated = false;
            return result;
        default:
            return result; // Returns TYPE_VOID, not newly allocated
    }
}
