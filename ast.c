#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "parser.h"
#include "symtab.h"            // Symbol, SymbolTable, symtab_* APIs
extern SymbolTable *symbol_table;
extern int compare_types(Type *a, Type *b);
extern void yyerror(const char *s);

// Global singleton Type objects for fundamental types
static Type *global_int_type = NULL;
static Type *global_float_type = NULL;
static Type *global_char_type = NULL;
static Type *global_void_type = NULL;
static Type *global_bool_type = NULL;
// Add others as needed (short, long, double)

Type *create_type(BaseType base) {
    Type *type = NULL;
    switch (base) {
        case TYPE_INT:
            if (!global_int_type) {
                global_int_type = (Type *)malloc(sizeof(Type));
                if (!global_int_type) { perror("Failed to allocate global_int_type"); exit(EXIT_FAILURE); }
                global_int_type->base = TYPE_INT;
                global_int_type->ptr_to = NULL;
                global_int_type->array_size = 0;
                global_int_type->name = NULL;
                global_int_type->members = NULL;
                global_int_type->is_signed = 0;
                global_int_type->is_unsigned = 0;
                global_int_type->is_const = 0;
                global_int_type->is_static = 0;
                global_int_type->is_extern = 0;
                global_int_type->is_volatile = 0;
                global_int_type->is_inline = 0;
            }
            return global_int_type;
        case TYPE_FLOAT:
            if (!global_float_type) {
                global_float_type = (Type *)malloc(sizeof(Type));
                if (!global_float_type) { perror("Failed to allocate global_float_type"); exit(EXIT_FAILURE); }
                global_float_type->base = TYPE_FLOAT;
                global_float_type->ptr_to = NULL;
                global_float_type->array_size = 0;
                global_float_type->name = NULL;
                global_float_type->members = NULL;
                global_float_type->is_signed = 0;
                global_float_type->is_unsigned = 0;
                global_float_type->is_const = 0;
                global_float_type->is_static = 0;
                global_float_type->is_extern = 0;
                global_float_type->is_volatile = 0;
                global_float_type->is_inline = 0;
            }
            return global_float_type;
        case TYPE_CHAR:
            if (!global_char_type) {
                global_char_type = (Type *)malloc(sizeof(Type));
                if (!global_char_type) { perror("Failed to allocate global_char_type"); exit(EXIT_FAILURE); }
                global_char_type->base = TYPE_CHAR;
                global_char_type->ptr_to = NULL;
                global_char_type->array_size = 0;
                global_char_type->name = NULL;
                global_char_type->members = NULL;
                global_char_type->is_signed = 0;
                global_char_type->is_unsigned = 0;
                global_char_type->is_const = 0;
                global_char_type->is_static = 0;
                global_char_type->is_extern = 0;
                global_char_type->is_volatile = 0;
                global_char_type->is_inline = 0;
            }
            return global_char_type;
        case TYPE_VOID:
            if (!global_void_type) {
                global_void_type = (Type *)malloc(sizeof(Type));
                if (!global_void_type) { perror("Failed to allocate global_void_type"); exit(EXIT_FAILURE); }
                global_void_type->base = TYPE_VOID;
                global_void_type->ptr_to = NULL;
                global_void_type->array_size = 0;
                global_void_type->name = NULL;
                global_void_type->members = NULL;
                global_void_type->is_signed = 0;
                global_void_type->is_unsigned = 0;
                global_void_type->is_const = 0;
                global_void_type->is_static = 0;
                global_void_type->is_extern = 0;
                global_void_type->is_volatile = 0;
                global_void_type->is_inline = 0;
            }
            return global_void_type;
        case TYPE_BOOL:
            if (!global_bool_type) {
                global_bool_type = (Type *)malloc(sizeof(Type));
                if (!global_bool_type) { perror("Failed to allocate global_bool_type"); exit(EXIT_FAILURE); }
                global_bool_type->base = TYPE_BOOL;
                global_bool_type->ptr_to = NULL;
                global_bool_type->array_size = 0;
                global_bool_type->name = NULL;
                global_bool_type->members = NULL;
                global_bool_type->is_signed = 0;
                global_bool_type->is_unsigned = 0;
                global_bool_type->is_const = 0;
                global_bool_type->is_static = 0;
                global_bool_type->is_extern = 0;
                global_bool_type->is_volatile = 0;
                global_bool_type->is_inline = 0;
            }
            return global_bool_type;
        // For other types, allocate a new one
        default:
            type = (Type *)malloc(sizeof(Type));
            if (!type) {
                perror("Failed to allocate Type");
                exit(EXIT_FAILURE);
            }
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
    fprintf(stderr, "DEBUG: create_float_node: input value = '%s'\n", value);
    node->string_value = strdup(value); // Store the string value
    if (!node->string_value) {
        perror("strdup failed in create_float_node");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "DEBUG: create_float_node: stored string_value = '%s'\n", node->string_value);
    node->float_value = atof(value); // Also store the converted float value for convenience
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
    node->string_value = strdup(value); // Duplicate the string to ensure ownership
    if (!node->string_value) {
        perror("strdup failed in create_string_literal_node");
        exit(EXIT_FAILURE);
    }
    return node;
}

ASTNode *create_variable_node(char *name) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_VARIABLE;
    node->variable.name = strdup(name); // Duplicate the string to ensure ownership
    if (!node->variable.name) {
        perror("strdup failed in create_variable_node");
        exit(EXIT_FAILURE);
    }
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
    node->var_decl.name = strdup(name); // Duplicate the string to ensure ownership
    if (!node->var_decl.name) {
        perror("strdup failed in create_var_decl_node");
        exit(EXIT_FAILURE);
    }
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
    if (!specifier) return NULL;

    if (specifier->type == NODE_TYPE_STRUCT_DEF) {
        // Definition: build the canonical Type and insert into the tag namespace
        Type *type = create_type(TYPE_STRUCT);
        type->name    = specifier->struct_def.name;     // may be NULL for anonymous
        type->members = specifier->struct_def.members;  // STATEMENT_LIST of DECL_LISTs

        // Only insert named (tagged) structs into the symtab
        if (type->name && *type->name) {
            // Insert or update the tag; the current symtab_insert allows redeclare of structs. 
            symtab_insert(symbol_table, type->name, SYMBOL_STRUCT, type, NULL, NULL, 0);
        }
        return type;
    }

    if (specifier->type == NODE_TYPE_STRUCT_REF) {
        // Reference: resolve through the symtab to reuse the canonical Type with members
        const char *tag = specifier->struct_ref.name;
        Symbol *sym = symtab_lookup(symbol_table, tag);
        if (sym && sym->type == SYMBOL_STRUCT && sym->data_type) {
            return sym->data_type; // REUSE canonical type (has members wired)
        }
        yyerror("Unknown struct type");
        // Fallback to avoid crashes; member access will still be invalid
        Type *type = create_type(TYPE_STRUCT);
        type->name = specifier->struct_ref.name;
        type->members = NULL;
        return type;
    }

    // Not a struct specifier
    return NULL;
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
    if (!specifier) return NULL;

    if (specifier->type == NODE_TYPE_UNION_DEF) {
        Type *type = create_type(TYPE_UNION);
        type->name    = specifier->union_def.name;     // may be NULL for anonymous
        type->members = specifier->union_def.members;

        if (type->name && *type->name) {
            symtab_insert(symbol_table, type->name, SYMBOL_UNION, type, NULL, NULL, 0);
        }
        return type;
    }

    if (specifier->type == NODE_TYPE_UNION_REF) {
        const char *tag = specifier->union_ref.name;
        Symbol *sym = symtab_lookup(symbol_table, tag);
        if (sym && sym->type == SYMBOL_UNION && sym->data_type) {
            return sym->data_type;
        }
        yyerror("Unknown union type");
        Type *type = create_type(TYPE_UNION);
        type->name = specifier->union_ref.name;
        type->members = NULL;
        return type;
    }

    return NULL;
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
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_STATEMENT_LIST;
    node->statement_list.statements = NULL;
    node->statement_list.count = 0;
    node->statement_list.scope = NULL;
    return node;
}

void add_statement_to_list(ASTNode *list, ASTNode *statement) {
    list->statement_list.count++;
    list->statement_list.statements = (ASTNode **)realloc(list->statement_list.statements, list->statement_list.count * sizeof(ASTNode *));
    list->statement_list.statements[list->statement_list.count - 1] = statement;
}

ASTNode *create_function_definition_node(Type *return_type, ASTNode *declarator, ASTNode *params, ASTNode *body) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_FUNCTION_DEFINITION;
    node->function_definition.return_type = return_type; 
    node->function_definition.declarator = declarator;
    node->function_definition.declarations = params;
    node->function_definition.body = body;
    node->function_definition.scope = NULL;
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

ASTNode *create_member_access_node(int op, ASTNode *struct_or_union, char *member_name) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_MEMBER_ACCESS;
    node->member_access.op = op;
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

ASTNode *fold_constants(ASTNode *node) {
    if (!node) {
        return NULL;
    }

    // Recursively fold children first
    if (node->type == NODE_TYPE_BINARY_OP) {
        node->binary_op.left = fold_constants(node->binary_op.left);
        node->binary_op.right = fold_constants(node->binary_op.right);
    } else if (node->type == NODE_TYPE_PROGRAM) {
        node->program.statements = fold_constants(node->program.statements);
    } else if (node->type == NODE_TYPE_STATEMENT_LIST) {
        for (int i = 0; i < node->statement_list.count; i++) {
            node->statement_list.statements[i] = fold_constants(node->statement_list.statements[i]);
        }
    } else if (node->type == NODE_TYPE_FUNCTION_DEFINITION) {
        node->function_definition.body = fold_constants(node->function_definition.body);
    } else if (node->type == NODE_TYPE_RETURN) {
        node->return_statement.statement = fold_constants(node->return_statement.statement);
    }

    // Now, try to fold the current node
    if (node->type == NODE_TYPE_BINARY_OP &&
        node->binary_op.left->type == NODE_TYPE_INTEGER &&
        node->binary_op.right->type == NODE_TYPE_INTEGER) {
        
        int result;
        switch (node->binary_op.op) {
            case T_ADD: result = node->binary_op.left->integer_value + node->binary_op.right->integer_value; break;
            case T_SUB: result = node->binary_op.left->integer_value - node->binary_op.right->integer_value; break;
            case T_MUL: result = node->binary_op.left->integer_value * node->binary_op.right->integer_value; break;
            case T_DIV: result = node->binary_op.left->integer_value / node->binary_op.right->integer_value; break;
            default: return node; // Not a foldable operator
        }
        
        free(node->binary_op.left);
        free(node->binary_op.right);
        node->type = NODE_TYPE_INTEGER;
        node->integer_value = result;
    }

    return node;
}

ASTNode *eliminate_dead_code(ASTNode *node) {
    if (!node) {
        return NULL;
    }

    if (node->type == NODE_TYPE_IF) {
        node->if_statement.condition = eliminate_dead_code(node->if_statement.condition);
        node->if_statement.then_branch = eliminate_dead_code(node->if_statement.then_branch);
        node->if_statement.else_branch = eliminate_dead_code(node->if_statement.else_branch);

        if (node->if_statement.condition->type == NODE_TYPE_INTEGER) {
            ASTNode *result;
            if (node->if_statement.condition->integer_value == 0) {
                // Condition is false, so the 'then' branch is dead code.
                result = node->if_statement.else_branch;
            } else {
                // Condition is true, so the 'else' branch is dead code.
                result = node->if_statement.then_branch;
            }
            free(node->if_statement.condition);
            free(node);
            return result;
        }
    } else if (node->type == NODE_TYPE_PROGRAM) {
        node->program.statements = eliminate_dead_code(node->program.statements);
    } else if (node->type == NODE_TYPE_STATEMENT_LIST) {
        for (int i = 0; i < node->statement_list.count; i++) {
            node->statement_list.statements[i] = eliminate_dead_code(node->statement_list.statements[i]);
        }
    } else if (node->type == NODE_TYPE_FUNCTION_DEFINITION) {
        node->function_definition.body = eliminate_dead_code(node->function_definition.body);
    }

    return node;
}

void print_type(Type *type, FILE *output_file) {
    if (type == NULL) return;
    if (type->is_signed) fprintf(output_file, "SIGNED ");
    if (type->is_unsigned) fprintf(output_file, "UNSIGNED ");
    switch (type->base) {
        case TYPE_INT: fprintf(output_file, "INT"); break;
        case TYPE_VOID: fprintf(output_file, "VOID"); break;
        case TYPE_SHORT: fprintf(output_file, "SHORT"); break;
        case TYPE_LONG: fprintf(output_file, "LONG"); break;
        case TYPE_POINTER: fprintf(output_file, "POINTER to "); print_type(type->ptr_to, output_file); break;
        case TYPE_ARRAY: fprintf(output_file, "ARRAY of %d ", type->array_size); print_type(type->ptr_to, output_file); break;
        case TYPE_STRUCT: fprintf(output_file, "STRUCT %s", type->name); break;
        case TYPE_UNION: fprintf(output_file, "UNION %s", type->name); break;
        case TYPE_ENUM: fprintf(output_file, "ENUM %s", type->name); break;
        case TYPE_CHAR: fprintf(output_file, "CHAR"); break;
        case TYPE_FLOAT: fprintf(output_file, "FLOAT"); break;
        case TYPE_DOUBLE: fprintf(output_file, "DOUBLE"); break;
        case TYPE_TYPEDEF: fprintf(output_file, "TYPEDEF %s", type->name); break;
        case TYPE_FUNCTION: fprintf(output_file, "FUNCTION returning "); print_type(type->ptr_to, output_file); break;
        case TYPE_BOOL: fprintf(output_file, "BOOL"); break;
    }
}

void generate_dot(ASTNode *node) {
    // Implementation for DOT graph generation (if needed)
}

void print_ast(ASTNode *node, int indent, FILE *output_file) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < indent; i++) {
        fprintf(output_file, "  ");
    }

    switch (node->type) {
        case NODE_TYPE_INTEGER:
            fprintf(output_file, "INTEGER: %d\n", node->integer_value);
            break;
        case NODE_TYPE_FLOAT:
            fprintf(output_file, "FLOAT: %f\n", node->float_value);
            break;
        case NODE_TYPE_CHAR:
            fprintf(output_file, "CHAR: %c\n", node->char_value);
            break;
        case NODE_TYPE_STRING_LITERAL:
            fprintf(output_file, "STRING_LITERAL: %s\n", node->string_value);
            break;
        case NODE_TYPE_VARIABLE:
            fprintf(output_file, "VARIABLE: %s\n", node->variable.name);
            break;
        case NODE_TYPE_BINARY_OP:
            fprintf(output_file, "BINARY_OP: ");
            switch (node->binary_op.op) {
                case T_EQ: fprintf(output_file, "==\n"); break;
                case T_NE: fprintf(output_file, "!=\n"); break;
                case T_GT: fprintf(output_file, ">\n"); break;
                case T_GE: fprintf(output_file, ">=\n"); break;
                case T_LT: fprintf(output_file, "<\n"); break;
                case T_LE: fprintf(output_file, "<=\n"); break;
                case T_LOGICAL_AND: fprintf(output_file, "&&\n"); break;
                case T_LOGICAL_OR: fprintf(output_file, "||\n"); break;
                case T_BITWISE_AND: fprintf(output_file, "&\n"); break;
                case T_BITWISE_OR: fprintf(output_file, "|\n"); break;
                case T_BITWISE_XOR: fprintf(output_file, "^\n"); break;
                case T_LSHIFT: fprintf(output_file, "<<\n"); break;
                case T_RSHIFT: fprintf(output_file, ">>\n"); break;
                case T_ADD: fprintf(output_file, "+\n"); break;
                case T_SUB: fprintf(output_file, "-\n"); break;
                case T_MUL: fprintf(output_file, "*\n"); break;
                case T_DIV: fprintf(output_file, " /\n"); break;
                case T_MOD: fprintf(output_file, "%%\n"); break;
            }
            print_ast(node->binary_op.left, indent + 1, output_file);
            print_ast(node->binary_op.right, indent + 1, output_file);
            break;
        case NODE_TYPE_UNARY_OP:
            fprintf(output_file, "UNARY_OP: ");
            switch (node->unary_op.op) {
                case T_MUL: fprintf(output_file, "*\n"); break;
                case T_BITWISE_AND: fprintf(output_file, "&\n"); break;
                case T_SUB: fprintf(output_file, "-\n"); break;
                case T_LOGICAL_NOT: fprintf(output_file, "!\n"); break;
                case T_BITWISE_NOT: fprintf(output_file, "~\n"); break;
                case T_INC: fprintf(output_file, "++\n"); break;
                case T_DEC: fprintf(output_file, "-\n"); break;
            }
            print_ast(node->unary_op.operand, indent + 1, output_file);
            break;
        case NODE_TYPE_VAR_DECL:
            fprintf(output_file, "VAR_DECL: %s", node->var_decl.name);
            if (node->var_decl.is_const) {
                fprintf(output_file, " (const)");
            }
            if (node->var_decl.is_static) {
                fprintf(output_file, " (static)");
            }
            if (node->var_decl.var_type && node->var_decl.var_type->is_extern) {
                fprintf(output_file, " (extern)");
            }
            if (node->var_decl.var_type && node->var_decl.var_type->is_volatile) {
                fprintf(output_file, " (volatile)");
            }
            if (node->var_decl.var_type && node->var_decl.var_type->is_inline) {
                fprintf(output_file, " (inline)");
            }
            fprintf(output_file, " of type ");
            print_type(node->var_decl.var_type, output_file);
            if (node->var_decl.init_expr) {
                fprintf(output_file, " =\n");
                print_ast(node->var_decl.init_expr, indent + 1, output_file);
            } else {
                fprintf(output_file, "\n");
            }
            break;
        case NODE_TYPE_ASSIGN:
            fprintf(output_file, "ASSIGN\n");
            print_ast(node->assign.var, indent + 1, output_file);
            print_ast(node->assign.expr, indent + 1, output_file);
            break;
        case NODE_TYPE_IF:
            fprintf(output_file, "IF\n");
            print_ast(node->if_statement.condition, indent + 1, output_file);
            print_ast(node->if_statement.then_branch, indent + 1, output_file);
            if (node->if_statement.else_branch) {
                for (int i = 0; i < indent; i++) fprintf(output_file, "  ");
                fprintf(output_file, "ELSE\n");
                print_ast(node->if_statement.else_branch, indent + 1, output_file);
            }
            break;
        case NODE_TYPE_WHILE:
            fprintf(output_file, "WHILE\n");
            print_ast(node->while_loop.condition, indent + 1, output_file);
            print_ast(node->while_loop.body, indent + 1, output_file);
            break;
        case NODE_TYPE_DO_WHILE:
            fprintf(output_file, "DO_WHILE\n");
            print_ast(node->do_while_loop.body, indent + 1, output_file);
            print_ast(node->do_while_loop.condition, indent + 1, output_file);
            break;
        case NODE_TYPE_FOR:
            fprintf(output_file, "FOR\n");
            print_ast(node->for_loop.init, indent + 1, output_file);
            print_ast(node->for_loop.condition, indent + 1, output_file);
            print_ast(node->for_loop.increment, indent + 1, output_file);
            print_ast(node->for_loop.body, indent + 1, output_file);
            break;
        case NODE_TYPE_SWITCH:
            fprintf(output_file, "SWITCH\n");
            print_ast(node->switch_statement.expr, indent + 1, output_file);
            print_ast(node->switch_statement.cases, indent + 1, output_file);
            break;
        case NODE_TYPE_CASE:
            if (node->case_statement.value) {
                fprintf(output_file, "CASE:\n");
                print_ast(node->case_statement.value, indent + 1, output_file);
            } else {
                fprintf(output_file, "DEFAULT:\n");
            }
            break;
        case NODE_TYPE_BREAK:
            fprintf(output_file, "BREAK\n");
            break;
        case NODE_TYPE_CONTINUE:
            fprintf(output_file, "CONTINUE\n");
            break;
        case NODE_TYPE_GOTO:
            fprintf(output_file, "GOTO: %s\n", node->goto_statement.name);
            break;
        case NODE_TYPE_LABEL:
            fprintf(output_file, "LABEL: %s\n", node->label_statement.name);
            print_ast(node->label_statement.statement, indent + 1, output_file);
            break;
        case NODE_TYPE_STRUCT_DEF:
            fprintf(output_file, "STRUCT_DEF: %s\n", node->struct_def.name ? node->struct_def.name : "(anonymous)");
            print_ast(node->struct_def.members, indent + 1, output_file);
            break;
        case NODE_TYPE_STRUCT_REF:
            fprintf(output_file, "STRUCT_REF: %s\n", node->struct_ref.name);
            break;
        case NODE_TYPE_UNION_DEF:
            fprintf(output_file, "UNION_DEF: %s\n", node->union_def.name ? node->union_def.name : "(anonymous)");
            print_ast(node->union_def.members, indent + 1, output_file);
            break;
        case NODE_TYPE_UNION_REF:
            fprintf(output_file, "UNION_REF: %s\n", node->union_ref.name);
            break;
        case NODE_TYPE_ENUM:
            fprintf(output_file, "ENUM: %s\n", node->enum_specifier.name);
            print_ast(node->enum_specifier.enumerators, indent + 1, output_file);
            break;
        case NODE_TYPE_ENUMERATOR:
            fprintf(output_file, "ENUMERATOR: %s\n", node->enumerator.name);
            if (node->enumerator.value) {
                print_ast(node->enumerator.value, indent + 1, output_file);
            }
            break;
        case NODE_TYPE_TYPEDEF:
            fprintf(output_file, "TYPEDEF: %s\n", node->typedef_node.name);
            print_type(node->typedef_node.type, output_file);
            fprintf(output_file, "\n");
            break;
        case NODE_TYPE_TERNARY_OP:
            fprintf(output_file, "TERNARY_OP\n");
            print_ast(node->ternary_op.condition, indent + 1, output_file);
            print_ast(node->ternary_op.true_expr, indent + 1, output_file);
            print_ast(node->ternary_op.false_expr, indent + 1, output_file);
            break;
        case NODE_TYPE_RETURN:
            fprintf(output_file, "RETURN\n");
            print_ast(node->return_statement.statement, indent + 1, output_file);
            break;
        case NODE_TYPE_STATEMENT_LIST:
            fprintf(output_file, "STATEMENT_LIST\n");
            for (int i = 0; i < node->statement_list.count; i++) {
                print_ast(node->statement_list.statements[i], indent + 1, output_file);
            }
            break;
        case NODE_TYPE_FUNCTION_DEFINITION:
            fprintf(output_file, "FUNCTION_DEFINITION: %s", node->function_definition.declarator->variable.name);
            Type *ret_type = node->function_definition.return_type;
            if (ret_type && ret_type->is_inline) {
                fprintf(output_file, " (inline)");
            }
            fprintf(output_file, ", returns ");
            print_type(ret_type, output_file);
            fprintf(output_file, "\n");
            print_ast(node->function_definition.declarations, indent + 1, output_file);
            print_ast(node->function_definition.body, indent + 1, output_file);
            break;
        case NODE_TYPE_FUNC_CALL:
            fprintf(output_file, "FUNC_CALL: %s\n", node->func_call.name);
            print_ast(node->func_call.args, indent + 1, output_file);
            break;
        case NODE_TYPE_PARAM_LIST:
            fprintf(output_file, "PARAM_LIST\n");
            for (int i = 0; i < node->param_list.count; i++) {
                print_ast(node->param_list.params[i], indent + 1, output_file);
            }
            break;
        case NODE_TYPE_ARG_LIST:
            fprintf(output_file, "ARG_LIST\n");
            for (int i = 0; i < node->arg_list.count; i++) {
                print_ast(node->arg_list.args[i], indent + 1, output_file);
            }
            break;
        case NODE_TYPE_ARRAY_ACCESS:
            fprintf(output_file, "ARRAY_ACCESS\n");
            print_ast(node->array_access.array, indent + 1, output_file);
            print_ast(node->array_access.index, indent + 1, output_file);
            break;
        case NODE_TYPE_MEMBER_ACCESS:
            fprintf(output_file, "MEMBER_ACCESS: %s\n", node->member_access.member_name);
            print_ast(node->member_access.struct_or_union, indent + 1, output_file);
            break;
        case NODE_TYPE_SIZEOF:
            fprintf(output_file, "SIZEOF: ");
            print_type(node->sizeof_op.type, output_file);
            fprintf(output_file, "\n");
            break;
        case NODE_TYPE_PROGRAM:
            fprintf(output_file, "PROGRAM\n");
            print_ast(node->program.statements, indent + 1, output_file);
            break;
        case NODE_TYPE_CAST:
            fprintf(output_file, "CAST to ");
            print_type(node->cast.to_type, output_file);
            fprintf(output_file, "\n");
            print_ast(node->cast.expr, indent + 1, output_file);
            break;
        case NODE_TYPE_INITIALIZER_LIST:
            fprintf(output_file, "INITIALIZER_LIST\n");
            for (int i = 0; i < node->initializer_list.count; i++) {
                print_ast(node->initializer_list.initializers[i], indent + 1, output_file);
            }
            break;
        case NODE_TYPE_TYPE_DECL:
            fprintf(output_file, "TYPE_DECL: ");
            print_type(node->var_decl.var_type, output_file);
            fprintf(output_file, "\n");
            break;
        case NODE_TYPE_DECL_LIST:
            fprintf(output_file, "DECL_LIST\n");
            for (int i = 0; i < node->statement_list.count; i++) {
                print_ast(node->statement_list.statements[i], indent + 1, output_file);
            }
            break;
    }
}

int is_arithmetic_type(Type *type) {
    if (!type) return 0;
    return type->base == TYPE_INT || type->base == TYPE_CHAR ||
           type->base == TYPE_SHORT || type->base == TYPE_LONG ||
           type->base == TYPE_FLOAT || type->base == TYPE_DOUBLE ||
           type->base == TYPE_BOOL;
}

int is_scalar_type(Type *type) {
    if (!type) return 0;
    return is_arithmetic_type(type) || type->base == TYPE_POINTER;
}

// Helper function to check if a type is one of the global singleton types
int is_global_singleton_type(Type *type) {
    return type == global_int_type || type == global_float_type ||
           type == global_char_type || type == global_void_type ||
           type == global_bool_type;
}

// Create a clone of a Type for safe independent ownership/freeing.
// - Returns the same pointer for global singleton base types.
// - Recursively clones pointer/array/function chains.
// - Duplicates name strings; does not duplicate members AST (free_type doesn't free members).
Type *clone_type(Type *type) {
    if (!type) return NULL;
    if (is_global_singleton_type(type)) {
        return type; // singletons are shared
    }

    Type *copy = (Type *)malloc(sizeof(Type));
    if (!copy) { perror("Failed to allocate Type clone"); exit(EXIT_FAILURE); }
    // Start with a shallow copy, then fix pointers we need to own independently
    *copy = *type;

    // Clone nested type if present
    if (type->ptr_to) {
        copy->ptr_to = clone_type(type->ptr_to);
    }
    // Duplicate name if present
    if (type->name) {
        copy->name = strdup(type->name);
        if (!copy->name) { perror("strdup failed in clone_type"); exit(EXIT_FAILURE); }
    }
    // members stays as-is; free_type does not free it
    return copy;
}

// Function to recursively free a Type structure
void free_type(Type *type) {
    if (!type) {
        return;
    }

    // Do not free global singleton types
    if (is_global_singleton_type(type)) {
        return;
    }

    // Recursively free nested types that are owned
    if (type->ptr_to) {
        free_type(type->ptr_to);
    }
    if (type->name) {
        free(type->name);
    }
    // For TYPE_FUNCTION, members points to a param_list ASTNode, which needs to be freed
    // For TYPE_STRUCT/UNION, members points to a statement_list ASTNode, which needs to be freed
    // This requires a free_ast_node function to handle the ASTNode structure.
    // For now, we'll assume ASTNodes are freed separately or handled by a different mechanism.
    // If members is a simple list of types (e.g., for function parameters), it would need specific handling.
    // Given the current structure, members is an ASTNode*, so it should be freed by free_ast_node.
    // To avoid circular dependencies or double frees, we'll only free the Type struct itself here.
    // The ASTNode* members should be freed when the AST is freed.

    free(type);
}
