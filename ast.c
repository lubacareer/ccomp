#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "parser.h"

Type *create_type(BaseType base) {
    Type *type = (Type *)malloc(sizeof(Type));
    type->base = base;
    type->ptr_to = NULL;
    type->array_size = 0;
    type->name = NULL;
    type->members = NULL;
    type->is_signed = 0;
    type->is_unsigned = 0;
    type->is_const = 0;
    type->is_static = 0;
    type->is_extern = 0;
    type->is_volatile = 0;
    type->is_inline = 0;
    return type;
}

Type *create_pointer_type(Type *ptr_to) {
    Type *type = create_type(TYPE_POINTER);
    type->ptr_to = ptr_to;
    return type;
}

Type *create_array_type(Type *base_type, int size) {
    Type *type = create_type(TYPE_ARRAY);
    type->ptr_to = base_type; // Use ptr_to to point to the base type of the array
    type->array_size = size;
    return type;
}

Type *create_function_type(Type *return_type, ASTNode *params) {
    Type *type = create_type(TYPE_FUNCTION);
    type->ptr_to = return_type;
    type->members = params;
    return type;
}

ASTNode *create_integer_node(int value) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_INTEGER;
    node->integer_value = value;
    return node;
}

ASTNode *create_float_node(char *value) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_FLOAT;
    node->float_value = atof(value);
    return node;
}

ASTNode *create_char_node(char *value) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_CHAR;
    node->char_value = value[1];
    return node;
}

ASTNode *create_string_literal_node(char *value) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_STRING_LITERAL;
    node->string_value = value;
    return node;
}

ASTNode *create_variable_node(char *name) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_VARIABLE;
    node->variable.name = name;
    return node;
}

ASTNode *create_binary_op_node(int op, ASTNode *left, ASTNode *right) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_BINARY_OP;
    node->binary_op.op = op;
    node->binary_op.left = left;
    node->binary_op.right = right;
    return node;
}

ASTNode *create_unary_op_node(int op, ASTNode *operand) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_UNARY_OP;
    node->unary_op.op = op;
    node->unary_op.operand = operand;
    return node;
}

ASTNode *create_var_decl_node(char *name, Type *type, int is_const, int is_static, ASTNode *init_expr) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_VAR_DECL;
    node->var_decl.name = name;
    node->var_decl.var_type = type;
    node->var_decl.is_const = is_const;
    node->var_decl.is_static = is_static;
    node->var_decl.init_expr = init_expr;
    return node;
}

ASTNode *create_sizeof_node(Type *type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_SIZEOF;
    node->sizeof_op.type = type;
    return node;
}

ASTNode *create_assign_node(ASTNode *var, ASTNode *expr) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_ASSIGN;
    node->assign.var = var;
    node->assign.expr = expr;
    return node;
}

ASTNode *create_if_node(ASTNode *condition, ASTNode *then_branch, ASTNode *else_branch) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_IF;
    node->if_statement.condition = condition;
    node->if_statement.then_branch = then_branch;
    node->if_statement.else_branch = else_branch;
    return node;
}

ASTNode *create_while_node(ASTNode *condition, ASTNode *body) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_WHILE;
    node->while_loop.condition = condition;
    node->while_loop.body = body;
    return node;
}

ASTNode *create_do_while_node(ASTNode *body, ASTNode *condition) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_DO_WHILE;
    node->do_while_loop.body = body;
    node->do_while_loop.condition = condition;
    return node;
}

ASTNode *create_for_node(ASTNode *init, ASTNode *condition, ASTNode *increment, ASTNode *body) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_FOR;
    node->for_loop.init = init;
    node->for_loop.condition = condition;
    node->for_loop.increment = increment;
    node->for_loop.body = body;
    return node;
}

ASTNode *create_switch_node(ASTNode *expr, ASTNode *cases) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_SWITCH;
    node->switch_statement.expr = expr;
    node->switch_statement.cases = cases;
    return node;
}

ASTNode *create_case_node(ASTNode *value) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_CASE;
    node->case_statement.value = value;
    return node;
}

ASTNode *create_break_node() {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_BREAK;
    return node;
}

ASTNode *create_continue_node() {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_CONTINUE;
    return node;
}

ASTNode *create_goto_node(char *name) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_GOTO;
    node->goto_statement.name = name;
    return node;
}

ASTNode *create_label_node(char *name, ASTNode *statement) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_LABEL;
    node->label_statement.name = name;
    node->label_statement.statement = statement;
    return node;
}

ASTNode *create_struct_def_node(char *name, ASTNode *members) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_STRUCT_DEF;
    node->struct_def.name = name;
    node->struct_def.members = members;
    return node;
}

ASTNode *create_struct_ref_node(char *name) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_STRUCT_REF;
    node->struct_ref.name = name;
    return node;
}

Type *create_type_from_specifier(ASTNode *specifier) {
    Type *type = create_type(TYPE_STRUCT);
    if (specifier->type == NODE_TYPE_STRUCT_DEF) {
        type->name = specifier->struct_def.name;
        type->members = specifier->struct_def.members;
    } else if (specifier->type == NODE_TYPE_STRUCT_REF) {
        type->name = specifier->struct_ref.name;
        type->members = NULL; // It's a reference, no members here
    }
    return type;
}

ASTNode *create_union_def_node(char *name, ASTNode *members) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_UNION_DEF;
    node->union_def.name = name;
    node->union_def.members = members;
    return node;
}

ASTNode *create_union_ref_node(char *name) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_UNION_REF;
    node->union_ref.name = name;
    return node;
}

Type *create_type_from_union_specifier(ASTNode *specifier) {
    Type *type = create_type(TYPE_UNION);
    if (specifier->type == NODE_TYPE_UNION_DEF) {
        type->name = specifier->union_def.name;
        type->members = specifier->union_def.members;
    } else if (specifier->type == NODE_TYPE_UNION_REF) {
        type->name = specifier->union_ref.name;
        type->members = NULL; // It's a reference, no members here
    }
    return type;
}

Type *create_type_from_enum_specifier(ASTNode *specifier) {
    Type *type = create_type(TYPE_ENUM);
    type->name = specifier->enum_specifier.name;
    return type;
}

ASTNode *create_type_decl_node(Type *type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_TYPE_DECL;
    // This is a bit of a hack, but we store the type in the var_decl union
    // to avoid creating a new union member for just one node type.
    node->var_decl.var_type = type;
    return node;
}

ASTNode *create_decl_list_node(Type *base_type, ASTNode *declarators) {
    for (int i = 0; i < declarators->statement_list.count; i++) {
        ASTNode *decl = declarators->statement_list.statements[i];
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
    return declarators;
}

ASTNode *create_enum_specifier_node(char *name, ASTNode *enumerators) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_ENUM;
    node->enum_specifier.name = name;
    node->enum_specifier.enumerators = enumerators;
    return node;
}

ASTNode *create_enumerator_node(char *name, ASTNode *value) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_ENUMERATOR;
    node->enumerator.name = name;
    node->enumerator.value = value;
    return node;
}

ASTNode *create_typedef_node(char *name, Type *type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_TYPEDEF;
    node->typedef_node.name = name;
    node->typedef_node.type = type;
    return node;
}

ASTNode *create_ternary_op_node(ASTNode *condition, ASTNode *true_expr, ASTNode *false_expr) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_TERNARY_OP;
    node->ternary_op.condition = condition;
    node->ternary_op.true_expr = true_expr;
    node->ternary_op.false_expr = false_expr;
    return node;
}

ASTNode *create_return_node(ASTNode *statement) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_RETURN;
    node->return_statement.statement = statement;
    return node;
}

ASTNode *create_statement_list_node() {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_STATEMENT_LIST;
    node->statement_list.statements = NULL;
    node->statement_list.count = 0;
    return node;
}

void add_statement_to_list(ASTNode *list, ASTNode *statement) {
    list->statement_list.count++;
    list->statement_list.statements = (ASTNode **)realloc(list->statement_list.statements, list->statement_list.count * sizeof(ASTNode *));
    list->statement_list.statements[list->statement_list.count - 1] = statement;
}

ASTNode *create_function_definition_node(Type *return_type, ASTNode *declarator, ASTNode *params, ASTNode *body) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_FUNCTION_DEFINITION;
    node->function_definition.return_type = return_type;
    node->function_definition.name = declarator->var_decl.name;
    node->function_definition.params = params;
    node->function_definition.body = body;
    return node;
}

ASTNode *create_func_call_node(char *name, ASTNode *args) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_FUNC_CALL;
    node->func_call.name = name;
    node->func_call.args = args;
    return node;
}

ASTNode *create_param_list_node() {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_PARAM_LIST;
    node->param_list.params = NULL;
    node->param_list.count = 0;
    return node;
}

void add_param_to_list(ASTNode *list, ASTNode *param) {
    list->param_list.count++;
    list->param_list.params = (ASTNode **)realloc(list->param_list.params, list->param_list.count * sizeof(ASTNode *));
    list->param_list.params[list->param_list.count - 1] = param;
}

ASTNode *create_arg_list_node() {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_ARG_LIST;
    node->arg_list.args = NULL;
    node->arg_list.count = 0;
    return node;
}

void add_arg_to_list(ASTNode *list, ASTNode *arg) {
    list->arg_list.count++;
    list->arg_list.args = (ASTNode **)realloc(list->arg_list.args, list->arg_list.count * sizeof(ASTNode *));
    list->arg_list.args[list->arg_list.count - 1] = arg;
}

ASTNode *create_array_access_node(ASTNode *array, ASTNode *index) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_ARRAY_ACCESS;
    node->array_access.array = array;
    node->array_access.index = index;
    return node;
}

ASTNode *create_member_access_node(ASTNode *struct_or_union, char *member_name) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_MEMBER_ACCESS;
    node->member_access.struct_or_union = struct_or_union;
    node->member_access.member_name = member_name;
    return node;
}

ASTNode *create_program_node() {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_PROGRAM;
    node->program.statements = create_statement_list_node();
    return node;
}

void add_toplevel_statement_to_program(ASTNode *program, ASTNode *statement) {
    add_statement_to_list(program->program.statements, statement);
}

ASTNode *create_cast_node(Type *to_type, ASTNode *expr) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_CAST;
    node->cast.to_type = to_type;
    node->cast.expr = expr;
    return node;
}

ASTNode *create_initializer_list_node() {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_INITIALIZER_LIST;
    node->initializer_list.initializers = NULL;
    node->initializer_list.count = 0;
    return node;
}

void add_initializer_to_list(ASTNode *list, ASTNode *initializer) {
    list->initializer_list.count++;
    list->initializer_list.initializers = (ASTNode **)realloc(list->initializer_list.initializers, list->initializer_list.count * sizeof(ASTNode *));
    list->initializer_list.initializers[list->initializer_list.count - 1] = initializer;
}

void print_type(Type *type) {
    if (type == NULL) return;
    if (type->is_signed) printf("SIGNED ");
    if (type->is_unsigned) printf("UNSIGNED ");
    switch (type->base) {
        case TYPE_INT: printf("INT"); break;
        case TYPE_VOID: printf("VOID"); break;
        case TYPE_SHORT: printf("SHORT"); break;
        case TYPE_LONG: printf("LONG"); break;
        case TYPE_POINTER: printf("POINTER to "); print_type(type->ptr_to); break;
        case TYPE_ARRAY: printf("ARRAY of %d ", type->array_size); print_type(type->ptr_to); break;
        case TYPE_STRUCT: printf("STRUCT %s", type->name); break;
        case TYPE_UNION: printf("UNION %s", type->name); break;
        case TYPE_ENUM: printf("ENUM %s", type->name); break;
        case TYPE_CHAR: printf("CHAR"); break;
        case TYPE_FLOAT: printf("FLOAT"); break;
        case TYPE_DOUBLE: printf("DOUBLE"); break;
        case TYPE_TYPEDEF: printf("TYPEDEF %s", type->name); break;
        case TYPE_FUNCTION: printf("FUNCTION returning "); print_type(type->ptr_to); break;
        case TYPE_BOOL: printf("BOOL"); break;
    }
}

void print_ast(ASTNode *node, int indent) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < indent; i++) {
        printf("  ");
    }

    switch (node->type) {
        case NODE_TYPE_INTEGER:
            printf("INTEGER: %d\n", node->integer_value);
            break;
        case NODE_TYPE_FLOAT:
            printf("FLOAT: %f\n", node->float_value);
            break;
        case NODE_TYPE_CHAR:
            printf("CHAR: %c\n", node->char_value);
            break;
        case NODE_TYPE_STRING_LITERAL:
            printf("STRING_LITERAL: %s\n", node->string_value);
            break;
        case NODE_TYPE_VARIABLE:
            printf("VARIABLE: %s\n", node->variable.name);
            break;
        case NODE_TYPE_BINARY_OP:
            printf("BINARY_OP: ");
            switch (node->binary_op.op) {
                case T_EQ: printf("==\n"); break;
                case T_NE: printf("!=\n"); break;
                case T_GT: printf(">\n"); break;
                case T_GE: printf(">=\n"); break;
                case T_LT: printf("<\n"); break;
                case T_LE: printf("<=\n"); break;
                case T_LOGICAL_AND: printf("&&\n"); break;
                case T_LOGICAL_OR: printf("||\n"); break;
                case T_BITWISE_AND: printf("&\n"); break;
                case T_BITWISE_OR: printf("|\n"); break;
                case T_BITWISE_XOR: printf("^\n"); break;
                case T_LSHIFT: printf("<<\n"); break;
                case T_RSHIFT: printf(">>\n"); break;
                case T_ADD: printf("+\n"); break;
                case T_SUB: printf("-\n"); break;
                case T_MUL: printf("*\n"); break;
                case T_DIV: printf(" /\n"); break;
                case T_MOD: printf("%%\n"); break;
            }
            print_ast(node->binary_op.left, indent + 1);
            print_ast(node->binary_op.right, indent + 1);
            break;
        case NODE_TYPE_UNARY_OP:
            printf("UNARY_OP: ");
            switch (node->unary_op.op) {
                case T_MUL: printf("*\n"); break;
                case T_BITWISE_AND: printf("&\n"); break;
                case T_SUB: printf("-\n"); break;
                case T_LOGICAL_NOT: printf("!\n"); break;
                case T_BITWISE_NOT: printf("~\n"); break;
                case T_INC: printf("++\n"); break;
                case T_DEC: printf("--\n"); break;
            }
            print_ast(node->unary_op.operand, indent + 1);
            break;
        case NODE_TYPE_VAR_DECL:
            printf("VAR_DECL: %s", node->var_decl.name);
            if (node->var_decl.is_const) {
                printf(" (const)");
            }
            if (node->var_decl.is_static) {
                printf(" (static)");
            }
            if (node->var_decl.var_type->is_extern) {
                printf(" (extern)");
            }
            if (node->var_decl.var_type->is_volatile) {
                printf(" (volatile)");
            }
            if (node->var_decl.var_type->is_inline) {
                printf(" (inline)");
            }
            printf(" of type ");
            print_type(node->var_decl.var_type);
            if (node->var_decl.init_expr) {
                printf(" =\n");
                print_ast(node->var_decl.init_expr, indent + 1);
            } else {
                printf("\n");
            }
            break;
        case NODE_TYPE_ASSIGN:
            printf("ASSIGN\n");
            print_ast(node->assign.var, indent + 1);
            print_ast(node->assign.expr, indent + 1);
            break;
        case NODE_TYPE_IF:
            printf("IF\n");
            print_ast(node->if_statement.condition, indent + 1);
            print_ast(node->if_statement.then_branch, indent + 1);
            if (node->if_statement.else_branch) {
                for (int i = 0; i < indent; i++) printf("  ");
                printf("ELSE\n");
                print_ast(node->if_statement.else_branch, indent + 1);
            }
            break;
        case NODE_TYPE_WHILE:
            printf("WHILE\n");
            print_ast(node->while_loop.condition, indent + 1);
            print_ast(node->while_loop.body, indent + 1);
            break;
        case NODE_TYPE_DO_WHILE:
            printf("DO_WHILE\n");
            print_ast(node->do_while_loop.body, indent + 1);
            print_ast(node->do_while_loop.condition, indent + 1);
            break;
        case NODE_TYPE_FOR:
            printf("FOR\n");
            print_ast(node->for_loop.init, indent + 1);
            print_ast(node->for_loop.condition, indent + 1);
            print_ast(node->for_loop.increment, indent + 1);
            print_ast(node->for_loop.body, indent + 1);
            break;
        case NODE_TYPE_SWITCH:
            printf("SWITCH\n");
            print_ast(node->switch_statement.expr, indent + 1);
            print_ast(node->switch_statement.cases, indent + 1);
            break;
        case NODE_TYPE_CASE:
            if (node->case_statement.value) {
                printf("CASE:\n");
                print_ast(node->case_statement.value, indent + 1);
            } else {
                printf("DEFAULT:\n");
            }
            break;
        case NODE_TYPE_BREAK:
            printf("BREAK\n");
            break;
        case NODE_TYPE_CONTINUE:
            printf("CONTINUE\n");
            break;
        case NODE_TYPE_GOTO:
            printf("GOTO: %s\n", node->goto_statement.name);
            break;
        case NODE_TYPE_LABEL:
            printf("LABEL: %s\n", node->label_statement.name);
            print_ast(node->label_statement.statement, indent + 1);
            break;
        case NODE_TYPE_STRUCT_DEF:
            printf("STRUCT_DEF: %s\n", node->struct_def.name ? node->struct_def.name : "(anonymous)");
            print_ast(node->struct_def.members, indent + 1);
            break;
        case NODE_TYPE_STRUCT_REF:
            printf("STRUCT_REF: %s\n", node->struct_ref.name);
            break;
        case NODE_TYPE_UNION_DEF:
            printf("UNION_DEF: %s\n", node->union_def.name ? node->union_def.name : "(anonymous)");
            print_ast(node->union_def.members, indent + 1);
            break;
        case NODE_TYPE_UNION_REF:
            printf("UNION_REF: %s\n", node->union_ref.name);
            break;
        case NODE_TYPE_ENUM:
            printf("ENUM: %s\n", node->enum_specifier.name);
            print_ast(node->enum_specifier.enumerators, indent + 1);
            break;
        case NODE_TYPE_ENUMERATOR:
            printf("ENUMERATOR: %s\n", node->enumerator.name);
            if (node->enumerator.value) {
                print_ast(node->enumerator.value, indent + 1);
            }
            break;
        case NODE_TYPE_TYPEDEF:
            printf("TYPEDEF: %s\n", node->typedef_node.name);
            print_type(node->typedef_node.type);
            printf("\n");
            break;
        case NODE_TYPE_TERNARY_OP:
            printf("TERNARY_OP\n");
            print_ast(node->ternary_op.condition, indent + 1);
            print_ast(node->ternary_op.true_expr, indent + 1);
            print_ast(node->ternary_op.false_expr, indent + 1);
            break;
        case NODE_TYPE_RETURN:
            printf("RETURN\n");
            print_ast(node->return_statement.statement, indent + 1);
            break;
        case NODE_TYPE_STATEMENT_LIST:
            printf("STATEMENT_LIST\n");
            for (int i = 0; i < node->statement_list.count; i++) {
                print_ast(node->statement_list.statements[i], indent + 1);
            }
            break;
        case NODE_TYPE_FUNCTION_DEFINITION:
            printf("FUNCTION_DEFINITION: %s", node->function_definition.name);
            if (node->function_definition.return_type->is_inline) {
                printf(" (inline)");
            }
            printf(", returns ");
            print_type(node->function_definition.return_type);
            printf("\n");
            print_ast(node->function_definition.params, indent + 1);
            print_ast(node->function_definition.body, indent + 1);
            break;
        case NODE_TYPE_FUNC_CALL:
            printf("FUNC_CALL: %s\n", node->func_call.name);
            print_ast(node->func_call.args, indent + 1);
            break;
        case NODE_TYPE_PARAM_LIST:
            printf("PARAM_LIST\n");
            for (int i = 0; i < node->param_list.count; i++) {
                print_ast(node->param_list.params[i], indent + 1);
            }
            break;
        case NODE_TYPE_ARG_LIST:
            printf("ARG_LIST\n");
            for (int i = 0; i < node->arg_list.count; i++) {
                print_ast(node->arg_list.args[i], indent + 1);
            }
            break;
        case NODE_TYPE_ARRAY_ACCESS:
            printf("ARRAY_ACCESS\n");
            print_ast(node->array_access.array, indent + 1);
            print_ast(node->array_access.index, indent + 1);
            break;
        case NODE_TYPE_MEMBER_ACCESS:
            printf("MEMBER_ACCESS: %s\n", node->member_access.member_name);
            print_ast(node->member_access.struct_or_union, indent + 1);
            break;
        case NODE_TYPE_SIZEOF:
            printf("SIZEOF: ");
            print_type(node->sizeof_op.type);
            printf("\n");
            break;
        case NODE_TYPE_PROGRAM:
            printf("PROGRAM\n");
            print_ast(node->program.statements, indent + 1);
            break;
        case NODE_TYPE_CAST:
            printf("CAST to ");
            print_type(node->cast.to_type);
            printf("\n");
            print_ast(node->cast.expr, indent + 1);
            break;
        case NODE_TYPE_INITIALIZER_LIST:
            printf("INITIALIZER_LIST\n");
            for (int i = 0; i < node->initializer_list.count; i++) {
                print_ast(node->initializer_list.initializers[i], indent + 1);
            }
            break;
        case NODE_TYPE_TYPE_DECL:
            printf("TYPE_DECL: ");
            print_type(node->var_decl.var_type);
            printf("\n");
            break;
    }
}
