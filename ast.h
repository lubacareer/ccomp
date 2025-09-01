#ifndef AST_H
#define AST_H

typedef enum {
    TYPE_INT,
    TYPE_POINTER,
    TYPE_ARRAY,
    TYPE_STRUCT,
    TYPE_UNION,
    TYPE_ENUM,
    TYPE_CHAR,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_VOID,
    TYPE_SHORT,
    TYPE_LONG,
    TYPE_TYPEDEF,
    TYPE_FUNCTION,
    TYPE_BOOL
} BaseType;

typedef struct Type {
    BaseType base;
    struct Type *ptr_to; // For pointers
    int array_size;      // For arrays
    char *name;          // For structs and unions
    struct ASTNode *members; // For structs and unions
    int is_signed;
    int is_unsigned;
    int is_const;
    int is_static;
    int is_extern;
    int is_volatile;
    int is_inline;
} Type;

typedef enum {
    NODE_TYPE_INTEGER,
    NODE_TYPE_FLOAT,
    NODE_TYPE_CHAR,
    NODE_TYPE_VARIABLE,
    NODE_TYPE_BINARY_OP,
    NODE_TYPE_UNARY_OP,
    NODE_TYPE_VAR_DECL,
    NODE_TYPE_ASSIGN,
    NODE_TYPE_IF,
    NODE_TYPE_WHILE,
    NODE_TYPE_DO_WHILE,
    NODE_TYPE_FOR,
    NODE_TYPE_SWITCH,
    NODE_TYPE_CASE,
    NODE_TYPE_BREAK,
    NODE_TYPE_CONTINUE,
    NODE_TYPE_GOTO,
    NODE_TYPE_LABEL,
    NODE_TYPE_STRUCT_DEF,
    NODE_TYPE_STRUCT_REF,
    NODE_TYPE_UNION_DEF,
    NODE_TYPE_UNION_REF,
    NODE_TYPE_ENUM,
    NODE_TYPE_ENUMERATOR,
    NODE_TYPE_TYPEDEF,
    NODE_TYPE_TERNARY_OP,
    NODE_TYPE_RETURN,
    NODE_TYPE_STATEMENT_LIST,
    NODE_TYPE_FUNCTION_DEFINITION,
    NODE_TYPE_FUNC_CALL,
    NODE_TYPE_PARAM_LIST,
    NODE_TYPE_ARG_LIST,
    NODE_TYPE_ARRAY_ACCESS,
    NODE_TYPE_MEMBER_ACCESS,
    NODE_TYPE_SIZEOF,
    NODE_TYPE_STRING_LITERAL,
    NODE_TYPE_PROGRAM,
    NODE_TYPE_CAST,
    NODE_TYPE_INITIALIZER_LIST,
    NODE_TYPE_TYPE_DECL
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        int integer_value;
        float float_value;
        char char_value;
        char *string_value;
        struct {
            int op;
            struct ASTNode *left;
            struct ASTNode *right;
        } binary_op;
        struct {
            int op;
            struct ASTNode *operand;
        } unary_op;
        struct {
            char *name;
        } variable;
        struct {
            char *name;
            Type *var_type;
            int is_const;
            int is_static;
            struct ASTNode *init_expr;
        } var_decl;
        struct {
            struct ASTNode *var;
            struct ASTNode *expr;
        } assign;
        struct {
            struct ASTNode *condition;
            struct ASTNode *then_branch;
            struct ASTNode *else_branch;
        } if_statement;
        struct {
            struct ASTNode *condition;
            struct ASTNode *body;
        } while_loop;
        struct {
            struct ASTNode *condition;
            struct ASTNode *body;
        } do_while_loop;
        struct {
            struct ASTNode *init;
            struct ASTNode *condition;
            struct ASTNode *increment;
            struct ASTNode *body;
        } for_loop;
        struct {
            struct ASTNode *expr;
            struct ASTNode *cases;
        } switch_statement;
        struct {
            struct ASTNode *value; // NULL for default case
        } case_statement;
        struct {
            char *name;
        } goto_statement;
        struct {
            char *name;
            struct ASTNode *statement;
        } label_statement;
        struct {
            char *name;
            struct ASTNode *members;
        } struct_def;
        struct {
            char *name;
        } struct_ref;
        struct {
            char *name;
            struct ASTNode *members;
        } union_def;
        struct {
            char *name;
        } union_ref;
        struct {
            char *name;
            struct ASTNode *enumerators;
        } enum_specifier;
        struct {
            char *name;
            struct ASTNode *value;
        } enumerator;
        struct {
            char *name;
            Type *type;
        } typedef_node;
        struct {
            struct ASTNode *condition;
            struct ASTNode *true_expr;
            struct ASTNode *false_expr;
        } ternary_op;
        struct {
            struct ASTNode *statement;
        } return_statement;
        struct {
            struct ASTNode **statements;
            int count;
        } statement_list;
        struct {
            char *name;
            Type *return_type;
            struct ASTNode *params;
            struct ASTNode *body;
        } function_definition;
        struct {
            char *name;
            struct ASTNode *args;
        } func_call;
        struct {
            struct ASTNode **params;
            int count;
        } param_list;
        struct {
            struct ASTNode **args;
            int count;
        } arg_list;
        struct {
            struct ASTNode *array;
            struct ASTNode *index;
        } array_access;
        struct {
            struct ASTNode *struct_or_union;
            char *member_name;
        } member_access;
        struct {
            Type *type;
        } sizeof_op;
        struct {
            struct ASTNode *statements;
        } program;
        struct {
            Type *to_type;
            struct ASTNode *expr;
        } cast;
        struct {
            struct ASTNode **initializers;
            int count;
        } initializer_list;
    };
} ASTNode;

Type *create_type(BaseType base);
Type *create_pointer_type(Type *ptr_to);
Type *create_array_type(Type *base_type, int size);
Type *create_function_type(Type *return_type, ASTNode *params);

ASTNode *create_integer_node(int value);
ASTNode *create_float_node(char *value);
ASTNode *create_char_node(char *value);
ASTNode *create_string_literal_node(char *value);
ASTNode *create_variable_node(char *name);
ASTNode *create_binary_op_node(int op, ASTNode *left, ASTNode *right);
ASTNode *create_unary_op_node(int op, ASTNode *operand);
ASTNode *create_var_decl_node(char *name, Type *type, int is_const, int is_static, struct ASTNode *init_expr);
ASTNode *create_sizeof_node(Type *type);
ASTNode *create_assign_node(ASTNode *var, ASTNode *expr);
ASTNode *create_if_node(ASTNode *condition, ASTNode *then_branch, ASTNode *else_branch);
ASTNode *create_while_node(ASTNode *condition, ASTNode *body);
ASTNode *create_do_while_node(ASTNode *body, ASTNode *condition);
ASTNode *create_for_node(ASTNode *init, ASTNode *condition, ASTNode *increment, ASTNode *body);
ASTNode *create_switch_node(ASTNode *expr, ASTNode *cases);
ASTNode *create_case_node(ASTNode *value);
ASTNode *create_break_node();
ASTNode *create_continue_node();
ASTNode *create_goto_node(char *name);
ASTNode *create_label_node(char *name, ASTNode *statement);
ASTNode *create_struct_def_node(char *name, ASTNode *members);
ASTNode *create_struct_ref_node(char *name);
ASTNode *create_union_def_node(char *name, ASTNode *members);
ASTNode *create_union_ref_node(char *name);
Type *create_type_from_specifier(ASTNode *specifier);
Type *create_type_from_union_specifier(ASTNode *specifier);
Type *create_type_from_enum_specifier(ASTNode *specifier);
ASTNode *create_type_decl_node(Type *type);
ASTNode *create_decl_list_node(Type *base_type, ASTNode *declarators);
ASTNode *create_enum_specifier_node(char *name, ASTNode *enumerators);
ASTNode *create_enumerator_node(char *name, ASTNode *value);
ASTNode *create_typedef_node(char *name, Type *type);
ASTNode *create_ternary_op_node(ASTNode *condition, ASTNode *true_expr, ASTNode *false_expr);
ASTNode *create_return_node(ASTNode *statement);
ASTNode *create_statement_list_node();
void add_statement_to_list(ASTNode *list, ASTNode *statement);
ASTNode *create_function_definition_node(Type *return_type, ASTNode *declarator, ASTNode *params, ASTNode *body);
ASTNode *create_func_call_node(char *name, ASTNode *args);
ASTNode *create_param_list_node();
void add_param_to_list(ASTNode *list, ASTNode *param);
ASTNode *create_arg_list_node();
void add_arg_to_list(ASTNode *list, ASTNode *arg);
ASTNode *create_array_access_node(ASTNode *array, ASTNode *index);
ASTNode *create_member_access_node(ASTNode *struct_or_union, char *member_name);
ASTNode *create_program_node();
void add_toplevel_statement_to_program(ASTNode *program, ASTNode *statement);
ASTNode *create_cast_node(Type *to_type, ASTNode *expr);
ASTNode *create_initializer_list_node();
void add_initializer_to_list(ASTNode *list, ASTNode *initializer);
void print_ast(ASTNode *node, int indent);
void generate_dot(ASTNode *node);

#endif // AST_H
