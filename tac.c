#include "tac.h"
#include "symtab.h"
#include "parser.h" // Include parser.h for operator definitions
#include "ast.h"    // Include ast.h for free_type declaration
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Include for bool type

extern SymbolTable *symbol_table;                                // Declare symbol_table as extern
extern TypeAndOwnership get_expression_type(ASTNode *expr);      // Declare get_expression_type as extern
extern int is_global_singleton_type(Type *type);                 // Declare is_global_singleton_type as extern
extern int is_type_owned_by_symtab(SymbolTable *st, Type *type); // Declare is_type_owned_by_symtab as extern
extern int compare_types(Type *a, Type *b);

// Global variables for TAC generation
static TACInstruction *tac_head = NULL;
static TACInstruction *tac_tail = NULL;
static int temp_counter = 0;
static int label_counter = 0;
// static FILE *output_file = NULL; // File pointer for output - Moved to local in print_tac

// Helper function to create a new operand
static Operand create_operand(OperandType type, Type *data_type, bool owns_type_mem)
{
    Operand op;
    op.type = type;
    op.data_type = data_type;
    memset(&op.u, 0, sizeof(op.u));           // Initialize union to zero
    op.owns_string_memory = false;            // Initialize string ownership flag
    op.owns_data_type_memory = owns_type_mem; // Initialize Type ownership flag
    return op;
}

// Helper function to create a new temporary variable operand
static Operand new_temp(Type *data_type, bool owns_type_mem)
{
    Operand op = create_operand(OPERAND_TEMP, data_type, owns_type_mem);
    op.u.temp_id = temp_counter++;
    return op;
}

// Helper function to create a new label operand
static Operand new_label()
{
    Operand op = create_operand(OPERAND_LABEL, NULL, false); // Labels don't have data_types or own them
    char label_buffer[16];
    sprintf(label_buffer, "L%d", label_counter++);
    op.u.label_name = strdup(label_buffer); // Use strdup to allocate and copy
    op.owns_string_memory = true;           // This operand owns the allocated string
    return op;
}

// Helper function to emit a TAC instruction
// Forward declaration for cloning Type when we need unique ownership per instruction
extern Type *clone_type(Type *type);

static TACInstruction *emit(TACOp op, Operand result, Operand arg1, Operand arg2)
{
    TACInstruction *instr = (TACInstruction *)malloc(sizeof(TACInstruction));
    if (!instr)
    {
        perror("Failed to allocate TACInstruction");
        exit(EXIT_FAILURE);
    }
    instr->op = op;
    instr->result = result;
    instr->arg1 = arg1;
    instr->arg2 = arg2;
    instr->label_id = -1; // Default no label
    instr->next = NULL;

    // Ensure that owned resources are unique per-instruction copy to avoid double-frees
    // Duplicate strings if this operand claims ownership
    Operand *ops[3] = {&instr->result, &instr->arg1, &instr->arg2};
    for (int i = 0; i < 3; ++i)
    {
        Operand *opnd = ops[i];
        if (opnd->owns_string_memory)
        {
            if (opnd->type == OPERAND_VAR && opnd->u.var_name)
            {
                opnd->u.var_name = strdup(opnd->u.var_name);
            }
            else if (opnd->type == OPERAND_LABEL && opnd->u.label_name)
            {
                opnd->u.label_name = strdup(opnd->u.label_name);
            }
            else if (opnd->type == OPERAND_STRING_LITERAL && opnd->u.string_literal)
            {
                opnd->u.string_literal = strdup(opnd->u.string_literal);
            }
        }
        // If this operand owns its Type, clone it so each instruction frees its own copy
        if (opnd->owns_data_type_memory && opnd->data_type)
        {
            opnd->data_type = clone_type(opnd->data_type);
        }
    }

    if (tac_head == NULL)
    {
        tac_head = instr;
        tac_tail = instr;
    }
    else
    {
        tac_tail->next = instr;
        tac_tail = instr;
    }
    return instr;
}

// Forward declarations for recursive TAC generation
static Operand generate_expression_tac(ASTNode *node);
static void generate_statement_tac(ASTNode *node);

// Main function to generate 3-address code
TACInstruction *generate_tac(ASTNode *root)
{
    if (!root)
        return NULL;

    // Reset global counters for each new generation
    tac_head = NULL;
    tac_tail = NULL;
    temp_counter = 0;
    label_counter = 0;

    generate_statement_tac(root); // Start generating from the root (program node)

    return tac_head;
}

// Helper function to print operand
static void print_operand(FILE *f, Operand op)
{
    if (op.type == OPERAND_VAR)
    {
        fprintf(f, "%s", op.u.var_name);
    }
    else if (op.type == OPERAND_TEMP)
    {
        fprintf(f, "t%d", op.u.temp_id);
    }
    else if (op.type == OPERAND_INT_CONST)
    {
        fprintf(f, "%d", op.u.int_val);
    }
    else if (op.type == OPERAND_FLOAT_CONST)
    {
        fprintf(f, "%f", op.u.float_val);
    }
    else if (op.type == OPERAND_LABEL)
    {
        fprintf(f, "%s", op.u.label_name);
    }
    else if (op.type == OPERAND_STRING_LITERAL)
    {
        if (op.u.string_literal && op.u.string_literal[0] == '"')
            fprintf(f, "%s", op.u.string_literal); // already quoted
        else
            fprintf(f, "\"%s\"", op.u.string_literal);
    }
    else
    {
        fprintf(f, "UNKNOWN_OPERAND");
    }
}

// Generate TAC for an expression
static Operand generate_expression_tac(ASTNode *node)
{
    if (!node)
        return create_operand(OPERAND_NONE, NULL, false);

    Operand op_result, op_left, op_right;

    switch (node->type)
    {
    case NODE_TYPE_INTEGER:
        op_result = create_operand(OPERAND_INT_CONST, create_type(TYPE_INT), true); // Owns its type
        op_result.u.int_val = node->integer_value;
        return op_result;
    case NODE_TYPE_FLOAT:
        op_result = create_operand(OPERAND_FLOAT_CONST, create_type(TYPE_FLOAT), true); // Owns its type
        op_result.u.float_val = node->float_value;                                      // Use the pre-calculated float value
        return op_result;
    case NODE_TYPE_CHAR:
        op_result = create_operand(OPERAND_INT_CONST, create_type(TYPE_CHAR), true); // Owns its type
        op_result.u.int_val = node->char_value;
        return op_result;
    case NODE_TYPE_STRING_LITERAL:
        op_result = create_operand(OPERAND_STRING_LITERAL, create_pointer_type(create_type(TYPE_CHAR)), true); // Owns its type
        op_result.u.string_literal = node->string_value;
        return op_result;
    case NODE_TYPE_VARIABLE:
        Symbol *s = symtab_lookup(symbol_table, node->variable.name);
        if (s)
        {
            op_result = create_operand(OPERAND_VAR, s->data_type, false); // Does NOT own its type (owned by symtab)
            op_result.u.var_name = node->variable.name;
            return op_result;
        }
        fprintf(stderr, "Error: Undefined variable '%s'\n", node->variable.name);
        exit(EXIT_FAILURE);
    case NODE_TYPE_ASSIGN:
        // Handle lvalues properly
        if (node->assign.var->type == NODE_TYPE_ARRAY_ACCESS)
        {
            Operand op_array = generate_expression_tac(node->assign.var->array_access.array);
            Operand op_index = generate_expression_tac(node->assign.var->array_access.index);
            Operand op_value = generate_expression_tac(node->assign.expr);
            emit(TAC_ARRAY_STORE, op_array, op_index, op_value);
            return op_array;
        }
        else
        {
            op_right = generate_expression_tac(node->assign.expr);
            op_left = generate_expression_tac(node->assign.var); // variable or member access becomes lvalue
            emit(TAC_ASSIGN, op_left, op_right, create_operand(OPERAND_NONE, NULL, false));
            return op_left; // Assignment returns the value of the left operand
        }
    case NODE_TYPE_BINARY_OP:
    {
        Operand op_left_expr = generate_expression_tac(node->binary_op.left);
        Operand op_right_expr = generate_expression_tac(node->binary_op.right);

        TypeAndOwnership left_tao = get_expression_type(node->binary_op.left);
        TypeAndOwnership right_tao = get_expression_type(node->binary_op.right);
        Type *left_type = left_tao.type;
        Type *right_type = right_tao.type;

        Type *result_type = NULL;
        bool result_type_is_new = false;

        if ((left_type && left_type->base == TYPE_FLOAT) || (right_type && right_type->base == TYPE_FLOAT))
        {
            result_type = create_type(TYPE_FLOAT);
        }
        else if (node->binary_op.op == T_LOGICAL_AND || node->binary_op.op == T_LOGICAL_OR ||
                 node->binary_op.op == T_EQ || node->binary_op.op == T_NE ||
                 node->binary_op.op == T_LT || node->binary_op.op == T_LE ||
                 node->binary_op.op == T_GT || node->binary_op.op == T_GE)
        {
            result_type = create_type(TYPE_BOOL);
        }
        else
        {
            result_type = create_type(TYPE_INT);
        }

        // If result_type is not a global singleton, it's a newly created type
        if (!is_global_singleton_type(result_type))
        {
            result_type_is_new = true;
        }

        op_result = new_temp(result_type, result_type_is_new);

        TACOp tac_op;
        switch (node->binary_op.op)
        {
        case T_ADD:
            tac_op = TAC_ADD;
            break;
        case T_SUB:
            tac_op = TAC_SUB;
            break;
        case T_MUL:
            tac_op = TAC_MUL;
            break;
        case T_DIV:
            tac_op = TAC_DIV;
            break;
        case T_MOD:
            tac_op = TAC_MOD;
            break;
        case T_EQ:
            tac_op = TAC_EQ;
            break; // ==
        case T_NE:
            tac_op = TAC_NE;
            break; // !=
        case T_LT:
            tac_op = TAC_LT;
            break;
        case T_LE:
            tac_op = TAC_LE;
            break; // <=
        case T_GT:
            tac_op = TAC_GT;
            break;
        case T_GE:
            tac_op = TAC_GE;
            break;          // >=
        case T_LOGICAL_AND: // Short-circuit AND
        {
            op_result = new_temp(create_type(TYPE_BOOL), true);                                  // Result of logical AND is boolean, new_temp owns it
            Operand const_true = create_operand(OPERAND_INT_CONST, create_type(TYPE_INT), true); // Owns its type
            const_true.u.int_val = 1;
            Operand const_false = create_operand(OPERAND_INT_CONST, create_type(TYPE_INT), true); // Owns its type
            const_false.u.int_val = 0;

            Operand label_false_branch = new_label();
            Operand label_end_and = new_label();

            emit(TAC_IF_FALSE_GOTO, label_false_branch, op_left_expr, create_operand(OPERAND_NONE, NULL, false));
            emit(TAC_IF_FALSE_GOTO, label_false_branch, op_right_expr, create_operand(OPERAND_NONE, NULL, false));
            emit(TAC_ASSIGN, op_result, const_true, create_operand(OPERAND_NONE, NULL, false)); // result = 1 (true)
            emit(TAC_GOTO, label_end_and, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
            emit(TAC_LABEL, label_false_branch, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
            emit(TAC_ASSIGN, op_result, const_false, create_operand(OPERAND_NONE, NULL, false)); // result = 0 (false)
            emit(TAC_LABEL, label_end_and, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));

            // Free types from children if they were newly allocated and not used as result
            // if (left_tao.is_newly_allocated && left_type != result_type)
            //     free_type(left_type);
            // if (right_tao.is_newly_allocated && right_type != result_type)
            //     free_type(right_type);
            return op_result;
        }
        case T_LOGICAL_OR: // Short-circuit OR
        {
            Operand label_true = new_label();
            Operand label_end = new_label();
            emit(TAC_IF_TRUE_GOTO, label_true, op_left_expr, create_operand(OPERAND_NONE, NULL, false));
            emit(TAC_IF_TRUE_GOTO, label_true, op_right_expr, create_operand(OPERAND_NONE, NULL, false));
            op_result = new_temp(create_type(TYPE_BOOL), true);                                   // Result of logical OR is boolean, new_temp owns it
            Operand const_false = create_operand(OPERAND_INT_CONST, create_type(TYPE_INT), true); // Owns its type
            const_false.u.int_val = 0;
            emit(TAC_ASSIGN, op_result, const_false, create_operand(OPERAND_NONE, NULL, false)); // result = 0 (false)
            emit(TAC_GOTO, label_end, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
            emit(TAC_LABEL, label_true, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
            Operand const_true = create_operand(OPERAND_INT_CONST, create_type(TYPE_INT), true); // Owns its type
            const_true.u.int_val = 1;
            emit(TAC_ASSIGN, op_result, const_true, create_operand(OPERAND_NONE, NULL, false)); // result = 1 (true)
            emit(TAC_LABEL, label_end, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));

            // Free types from children if they were newly allocated and not used as result
            // if (left_tao.is_newly_allocated && left_type != result_type)
            //     free_type(left_type);
            // if (right_tao.is_newly_allocated && right_type != result_type)
            //     free_type(right_type);
            return op_result;
        }
        default:
            fprintf(stderr, "Error: Unknown binary operator %d\n", node->binary_op.op);
            exit(EXIT_FAILURE);
        }
        emit(tac_op, op_result, op_left_expr, op_right_expr);

        // Free types from children if they were newly allocated and not used as result
        // if (left_tao.is_newly_allocated && left_type != result_type)
        //     free_type(left_type);
        // if (right_tao.is_newly_allocated && right_type != result_type)
        //     free_type(right_type);
        return op_result;
    }
    case NODE_TYPE_UNARY_OP:
    {
        Operand op_operand = generate_expression_tac(node->unary_op.operand);
        TypeAndOwnership operand_tao = get_expression_type(node->unary_op.operand);
        Type *operand_type = operand_tao.type;

        Type *result_type = NULL;
        bool result_type_is_new = false;

        if (node->unary_op.op == T_BITWISE_AND)
        { // Address-of operator allocates a new pointer type
            result_type = create_pointer_type(operand_type);
            result_type_is_new = true; // safe: created here
        }
        else if (node->unary_op.op == T_MUL)
        { // Dereference operator: borrow the pointed-to type
            if (operand_type->base == TYPE_POINTER)
            {
                result_type = operand_type->ptr_to;
            }
            else
            {
                fprintf(stderr, "Error: Dereference operator can only be applied to pointers\n");
                exit(EXIT_FAILURE);
            }
            result_type_is_new = false; // borrowed
        }
        else if (node->unary_op.op == T_LOGICAL_NOT)
        { // Logical NOT returns BOOL singleton
            result_type = create_type(TYPE_BOOL);
            result_type_is_new = false;
        }
        else
        { // Other unary ops: type unchanged (borrowed)
            result_type = operand_type;
            result_type_is_new = false;
        }

        op_result = new_temp(result_type, result_type_is_new);

        TACOp unary_tac_op;
        switch (node->unary_op.op)
        {
        case T_SUB:
            unary_tac_op = TAC_NEG;
            break;
        case T_LOGICAL_NOT:
            unary_tac_op = TAC_NOT;
            break;
        case T_BITWISE_AND:
            unary_tac_op = TAC_ADDR;
            break; // Address-of operator
        case T_MUL:
            unary_tac_op = TAC_DEREF;
            break; // Dereference operator
        case T_INC:
            unary_tac_op = TAC_INC;
            break; // Increment operator
        case T_DEC:
            unary_tac_op = TAC_DEC;
            break; // Decrement operator
        default:
            fprintf(stderr, "Error: Unknown unary operator %d\n", node->unary_op.op);
            exit(EXIT_FAILURE);
        }
        // For ++/-- on simple variables, mutate the variable itself: i = i +/- 1
        if ((node->unary_op.op == T_INC || node->unary_op.op == T_DEC) && op_operand.type == OPERAND_VAR)
        {
            // Use the variable as both result and arg1 so print shows: x = x +/- 1
            emit(unary_tac_op, op_operand, op_operand, create_operand(OPERAND_NONE, NULL, false));
            op_result = op_operand; // expression yields the updated variable
        }
        else
        {
            emit(unary_tac_op, op_result, op_operand, create_operand(OPERAND_NONE, NULL, false));
        }

        // Free operand_type if it was newly allocated and not used as result
        // if (operand_tao.is_newly_allocated && operand_type != result_type)
        //     free_type(operand_type);
        return op_result;
    }
    case NODE_TYPE_FUNC_CALL:
        Symbol *func_symbol = symtab_lookup(symbol_table, node->func_call.name);
        if (!func_symbol || func_symbol->type != SYMBOL_FUNCTION)
        {
            fprintf(stderr, "Error: Function '%s' not defined.\n", node->func_call.name);
            exit(EXIT_FAILURE);
        }
        // Handle function call arguments
        if (node->func_call.args)
        {
            ASTNode *current_arg = node->func_call.args->arg_list.args[0];
            for (int i = 0; i < node->func_call.args->arg_list.count; ++i)
            {
                current_arg = node->func_call.args->arg_list.args[i];
                Operand arg_op = generate_expression_tac(current_arg);
                emit(TAC_PARAM, arg_op, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
            }
        }
        op_result = new_temp(func_symbol->return_type, false);                                   // new_temp does NOT own the return type (owned by symtab)
        Operand func_name_op = create_operand(OPERAND_VAR, NULL, false);                         // Function name is a string, not a Type*
        func_name_op.u.var_name = strdup(node->func_call.name);                                  // Duplicate the string to ensure ownership
        func_name_op.owns_string_memory = true;                                                  // This operand owns the allocated string
        emit(TAC_CALL, op_result, func_name_op, create_operand(OPERAND_INT_CONST, NULL, false)); // Arg2 stores number of args
        tac_tail->arg2.u.int_val = node->func_call.args ? node->func_call.args->arg_list.count : 0;
        return op_result;
    case NODE_TYPE_ARRAY_ACCESS:
    {
        Operand op_array = generate_expression_tac(node->array_access.array);
        Operand op_index = generate_expression_tac(node->array_access.index);

        TypeAndOwnership array_tao = get_expression_type(node->array_access.array);
        TypeAndOwnership index_tao = get_expression_type(node->array_access.index);
        Type *array_type = array_tao.type;
        Type *index_type = index_tao.type;

        Type *result_type = NULL;
        bool result_type_is_new = false;

        if (array_type && array_type->base == TYPE_ARRAY)
        {
            result_type = array_type->ptr_to;
        }
        else if (array_type && array_type->base == TYPE_POINTER)
        {
            result_type = array_type->ptr_to;
        }
        else
        {
            fprintf(stderr, "Error: [] operator can only be used with arrays or pointers\n");
            exit(EXIT_FAILURE);
        }

        // Result type is borrowed from array/pointer element type
        result_type_is_new = false;

        op_result = new_temp(result_type, result_type_is_new);
        emit(TAC_ARRAY_LOAD, op_result, op_array, op_index);

        // Free types from children if they were newly allocated and not used as result
        // if (array_tao.is_newly_allocated && array_type != result_type)
        //     free_type(array_type);
        // if (index_tao.is_newly_allocated && index_type != result_type)
        //     free_type(index_type);
        return op_result;
    }
    case NODE_TYPE_MEMBER_ACCESS:
    {
        TypeAndOwnership base_tao = get_expression_type(node->member_access.struct_or_union);
        Type *base_type = base_tao.type;

        Type *result_type = NULL;
        bool result_type_is_new = false;

        if (node->member_access.op == T_ARROW)
        {
            if (base_type->base == TYPE_POINTER)
            {
                base_type = base_type->ptr_to;
            }
            else
            {
                fprintf(stderr, "Error: Arrow operator can only be applied to pointer to struct/union types\n");
                exit(EXIT_FAILURE);
            }
        }

        if (base_type->base != TYPE_STRUCT && base_type->base != TYPE_UNION)
        {
            fprintf(stderr, "Error: Member access operator can only be used with struct/union types\n");
            exit(EXIT_FAILURE);
        }

        /* base_type was resolved; we already handled -> by dereferencing if needed */

        if (base_type->members && base_type->members->type == NODE_TYPE_STATEMENT_LIST)
        {
            int top_count = base_type->members->statement_list.count;
            for (int i = 0; i < top_count && !result_type; i++)
            {
                ASTNode *item = base_type->members->statement_list.statements[i];

                if (item->type == NODE_TYPE_VAR_DECL)
                {
                    if (item->var_decl.name &&
                        strcmp(item->var_decl.name, node->member_access.member_name) == 0)
                    {
                        result_type = item->var_decl.var_type;
                        break;
                    }
                }
                else if (item->type == NODE_TYPE_STATEMENT_LIST)
                {
                    int m = item->statement_list.count;
                    for (int j = 0; j < m && !result_type; j++)
                    {
                        ASTNode *mem = item->statement_list.statements[j];
                        if (mem->type == NODE_TYPE_VAR_DECL &&
                            mem->var_decl.name &&
                            strcmp(mem->var_decl.name, node->member_access.member_name) == 0)
                        {
                            result_type = mem->var_decl.var_type;
                            break;
                        }
                    }
                }
                else if (item->type == NODE_TYPE_DECL_LIST)
                {
                    int k = item->statement_list.count;
                    for (int j = 0; j < k && !result_type; j++)
                    {
                        ASTNode *mem = item->statement_list.statements[j];
                        if (mem->type == NODE_TYPE_VAR_DECL &&
                            mem->var_decl.name &&
                            strcmp(mem->var_decl.name, node->member_access.member_name) == 0)
                        {
                            result_type = mem->var_decl.var_type;
                            break;
                        }
                    }
                }
            }
        }

        if (!result_type)
        {
            fprintf(stderr, "Error: Member not found in struct/union\n");
            exit(EXIT_FAILURE);
        }

        /* then proceed to create the temp and emit, as you already do */
        // Member result type is defined in the struct/union; borrow it
        result_type_is_new = false;

        // Treat member lvalues/rvalues as named variables "base.member" for TAC simplicity
        char *full_name = (char *)malloc(strlen(node->member_access.struct_or_union->variable.name) + strlen(node->member_access.member_name) + 2);
        sprintf(full_name, "%s.%s", node->member_access.struct_or_union->variable.name, node->member_access.member_name);
        op_result = create_operand(OPERAND_VAR, result_type, false);
        op_result.u.var_name = full_name;
        op_result.owns_string_memory = true; // This operand owns the allocated string

        // Free base_type if it was newly allocated and not used as result
        // if (base_tao.is_newly_allocated && base_type != result_type)
        //     free_type(base_type);
        return op_result;
    }
    case NODE_TYPE_CAST:
    {
        Operand op_expr = generate_expression_tac(node->cast.expr);
        Type *result_type = node->cast.to_type;
        bool result_type_is_new = false; // Cast type is from AST, not newly allocated here

        op_result = new_temp(result_type, result_type_is_new);
        emit(TAC_CAST, op_result, op_expr, create_operand(OPERAND_NONE, NULL, false));
        return op_result;
    }
    case NODE_TYPE_TERNARY_OP:
    {
        fprintf(stderr, "DEBUG: Entered NODE_TYPE_TERNARY_OP case in generate_expression_tac.\n"); // New debug print
        Operand cond_op = generate_expression_tac(node->ternary_op.condition);
        Operand true_op = generate_expression_tac(node->ternary_op.true_expr);
        Operand false_op = generate_expression_tac(node->ternary_op.false_expr);

        TypeAndOwnership cond_tao = get_expression_type(node->ternary_op.condition);
        TypeAndOwnership true_tao = get_expression_type(node->ternary_op.true_expr);
        TypeAndOwnership false_tao = get_expression_type(node->ternary_op.false_expr);
        Type *condition_type = cond_tao.type;
        Type *true_type = true_tao.type;
        Type *false_type = false_tao.type;

        Type *result_type = NULL;
        bool result_type_is_new = false;

        if (is_arithmetic_type(true_type) && is_arithmetic_type(false_type))
        {
            if (true_type->base == TYPE_DOUBLE || false_type->base == TYPE_DOUBLE)
                result_type = create_type(TYPE_DOUBLE);
            else if (true_type->base == TYPE_FLOAT || false_type->base == TYPE_FLOAT)
                result_type = create_type(TYPE_FLOAT);
            else
                result_type = create_type(TYPE_INT);
        }
        else if (true_type->base == TYPE_POINTER && false_type->base == TYPE_POINTER)
        {
            if (compare_types(true_type, false_type))
            {
                result_type = true_type;
            }
            else
            {
                fprintf(stderr, "Error: Incompatible pointer types in ternary operator expressions\n");
                exit(EXIT_FAILURE);
            }
        }
        else if ((true_type->base == TYPE_POINTER && false_type->base == TYPE_INT && node->ternary_op.false_expr->type == NODE_TYPE_INTEGER && node->ternary_op.false_expr->integer_value == 0) ||
                 (false_type->base == TYPE_POINTER && true_type->base == TYPE_INT && node->ternary_op.true_expr->type == NODE_TYPE_INTEGER && node->ternary_op.true_expr->integer_value == 0))
        {
            result_type = (true_type->base == TYPE_POINTER) ? true_type : false_type;
        }
        else
        {
            fprintf(stderr, "Error: Incompatible types in ternary operator expressions\n");
            exit(EXIT_FAILURE);
        }

        // Result type for ternary is borrowed (base types are singletons)
        result_type_is_new = false;

        op_result = new_temp(result_type, result_type_is_new);

        Operand label_true = new_label();
        Operand label_end = new_label();

        emit(TAC_IF_TRUE_GOTO, label_true, cond_op, create_operand(OPERAND_NONE, NULL, false));
        // False branch
        emit(TAC_ASSIGN, op_result, false_op, create_operand(OPERAND_NONE, NULL, false));
        emit(TAC_GOTO, label_end, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
        // True branch
        emit(TAC_LABEL, label_true, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
        emit(TAC_ASSIGN, op_result, true_op, create_operand(OPERAND_NONE, NULL, false));
        emit(TAC_LABEL, label_end, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));

        // Free types from children if they were newly allocated and not used as result
        // if (cond_tao.is_newly_allocated && condition_type != result_type)
        //     free_type(condition_type);
        // if (true_tao.is_newly_allocated && true_type != result_type)
        //     free_type(true_type);
        // if (false_tao.is_newly_allocated && false_type != result_type)
        //     free_type(false_type);
        return op_result;
    }
    case NODE_TYPE_ENUMERATOR:
        op_result = create_operand(OPERAND_INT_CONST, create_type(TYPE_INT), true); // Owns its type
        op_result.u.int_val = node->enumerator.value->integer_value;                // Enumerators are integer constants
        return op_result;
    default:
        fprintf(stderr, "Error: Unsupported AST node type for expression TAC generation: %d\n", node->type);
        exit(EXIT_FAILURE);
    }
}

// Generate TAC for a statement
static void generate_statement_tac(ASTNode *node)
{
    if (!node)
        return;

    Operand op_result, op_condition;
    Operand label_start, label_end, label_else;

    fprintf(stderr, "DEBUG: generate_statement_tac processing node type: %d\n", node->type); // Debug print

    switch (node->type)
    {
    case NODE_TYPE_PROGRAM:
        if (node->program.statements)
        {
            ASTNode **current_statement = node->program.statements->statement_list.statements;
            for (int i = 0; i < node->program.statements->statement_list.count; ++i)
            {
                generate_statement_tac(current_statement[i]);
            }
        }
        break;
    case NODE_TYPE_STATEMENT_LIST:
        if (node->statement_list.statements)
        {
            ASTNode **current_statement = node->statement_list.statements;
            for (int i = 0; i < node->statement_list.count; ++i)
            {
                generate_statement_tac(current_statement[i]);
            }
        }
        break;
    case NODE_TYPE_VAR_DECL:
        // Variable declarations might involve initialization
        if (node->var_decl.init_expr)
        {
            Operand var_op = create_operand(OPERAND_VAR, node->var_decl.var_type, false); // Does NOT own its type (owned by symtab)
            var_op.u.var_name = node->var_decl.name;

            if (node->var_decl.init_expr->type == NODE_TYPE_INITIALIZER_LIST)
            {
                // Handle initializer list for arrays/structs
                // This is a simplified approach; a full compiler would handle
                // nested initializer lists and different aggregate types.
                for (int i = 0; i < node->var_decl.init_expr->initializer_list.count; ++i)
                {
                    ASTNode *initializer = node->var_decl.init_expr->initializer_list.initializers[i];
                    Operand init_val_op = generate_expression_tac(initializer);
                    Operand index_op = create_operand(OPERAND_INT_CONST, create_type(TYPE_INT), true); // Owns its type
                    index_op.u.int_val = i;
                    emit(TAC_ARRAY_STORE, var_op, index_op, init_val_op);
                }
            }
            else
            {
                // Handle single expression initialization
                Operand init_op = generate_expression_tac(node->var_decl.init_expr);
                emit(TAC_ASSIGN, var_op, init_op, create_operand(OPERAND_NONE, NULL, false));
            }
        }
        break;
    case NODE_TYPE_ASSIGN:
        generate_expression_tac(node); // Assignment is also an expression
        break;
    case NODE_TYPE_IF:
        op_condition = generate_expression_tac(node->if_statement.condition);
        label_else = new_label();
        label_end = new_label();

        emit(TAC_IF_FALSE_GOTO, label_else, op_condition, create_operand(OPERAND_NONE, NULL, false));
        generate_statement_tac(node->if_statement.then_branch);
        emit(TAC_GOTO, label_end, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
        emit(TAC_LABEL, label_else, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
        if (node->if_statement.else_branch)
        {
            generate_statement_tac(node->if_statement.else_branch);
        }
        emit(TAC_LABEL, label_end, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
        break;
    case NODE_TYPE_WHILE:
        label_start = new_label();
        label_end = new_label();

        emit(TAC_LABEL, label_start, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
        op_condition = generate_expression_tac(node->while_loop.condition);
        emit(TAC_IF_FALSE_GOTO, label_end, op_condition, create_operand(OPERAND_NONE, NULL, false));
        generate_statement_tac(node->while_loop.body);
        emit(TAC_GOTO, label_start, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
        emit(TAC_LABEL, label_end, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
        break;
    case NODE_TYPE_DO_WHILE:
        label_start = new_label();
        label_end = new_label();

        emit(TAC_LABEL, label_start, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
        generate_statement_tac(node->do_while_loop.body);
        op_condition = generate_expression_tac(node->do_while_loop.condition);
        emit(TAC_IF_TRUE_GOTO, label_start, op_condition, create_operand(OPERAND_NONE, NULL, false));
        emit(TAC_LABEL, label_end, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
        break;
    case NODE_TYPE_FOR:
        Operand for_label_start = new_label();
        Operand for_label_end = new_label();
        Operand for_label_increment = new_label();

        if (node->for_loop.init)
        {
            generate_statement_tac(node->for_loop.init);
        }
        emit(TAC_LABEL, for_label_start, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
        if (node->for_loop.condition)
        {
            op_condition = generate_expression_tac(node->for_loop.condition);
            emit(TAC_IF_FALSE_GOTO, for_label_end, op_condition, create_operand(OPERAND_NONE, NULL, false));
        }
        generate_statement_tac(node->for_loop.body);
        emit(TAC_LABEL, for_label_increment, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
        if (node->for_loop.increment)
        {
            generate_expression_tac(node->for_loop.increment);
        }
        emit(TAC_GOTO, for_label_start, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
        emit(TAC_LABEL, for_label_end, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
        break;
    case NODE_TYPE_RETURN:
        if (node->return_statement.statement)
        {
            op_result = generate_expression_tac(node->return_statement.statement);
            emit(TAC_RETURN, op_result, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
        }
        else
        {
            emit(TAC_RETURN, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
        }
        break;
    case NODE_TYPE_FUNCTION_DEFINITION:
        // Emit a label for the function entry point
        Operand func_label = create_operand(OPERAND_LABEL, NULL, false);
        func_label.u.label_name = node->function_definition.declarator->variable.name;
        emit(TAC_LABEL, func_label, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));

        // Generate TAC for function body
        generate_statement_tac(node->function_definition.body);
        break;
    case NODE_TYPE_FUNC_CALL:
        generate_expression_tac(node); // Function calls can also be statements
        break;
    case NODE_TYPE_GOTO:
        op_result = create_operand(OPERAND_LABEL, NULL, false);
        op_result.u.label_name = node->goto_statement.name;
        emit(TAC_GOTO, op_result, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
        break;
    case NODE_TYPE_LABEL:
        op_result = create_operand(OPERAND_LABEL, NULL, false);
        op_result.u.label_name = node->label_statement.name;
        emit(TAC_LABEL, op_result, create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false));
        generate_statement_tac(node->label_statement.statement);
        break;
    case NODE_TYPE_BREAK:
        // Need to find the nearest loop/switch end label
        // For now, a placeholder
        fprintf(stderr, "Warning: BREAK statement not fully implemented for TAC generation.\n");
        emit(TAC_GOTO, create_operand(OPERAND_LABEL, NULL, false), create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false)); // Placeholder
        break;
    case NODE_TYPE_CONTINUE:
        // Need to find the nearest loop increment/condition label
        // For now, a placeholder
        fprintf(stderr, "Warning: CONTINUE statement not fully implemented for TAC generation.\n");
        emit(TAC_GOTO, create_operand(OPERAND_LABEL, NULL, false), create_operand(OPERAND_NONE, NULL, false), create_operand(OPERAND_NONE, NULL, false)); // Placeholder
        break;
    case NODE_TYPE_SWITCH:
        fprintf(stderr, "Warning: SWITCH statement not fully implemented for TAC generation.\n");
        // This is complex, requires jump tables or a series of IF_EQ_GOTO
        break;
    case NODE_TYPE_CASE:
        fprintf(stderr, "Warning: CASE statement not fully implemented for TAC generation.\n");
        break;
    case NODE_TYPE_TYPE_DECL: // Handle standalone type declarations (e.g., struct Point;)
        // These do not generate executable code, so simply ignore for TAC.
        break;
    case NODE_TYPE_TYPEDEF: // Handle typedef declarations
        // Typedefs do not generate executable code, so simply ignore for TAC.
        break;
    case NODE_TYPE_DECL_LIST:
        if (node->statement_list.statements)
        { // Reusing statement_list for declarations
            ASTNode **current_declaration = node->statement_list.statements;
            for (int i = 0; i < node->statement_list.count; ++i)
            {
                generate_statement_tac(current_declaration[i]);
            }
        }
        break;
    default:
        // For other nodes that can be statements but are handled as expressions (e.g., binary ops, unary ops)
        // If they are top-level statements, generate their TAC and discard the result
        if (node->type >= NODE_TYPE_INTEGER && node->type <= NODE_TYPE_CAST)
        { // Assuming these are expression nodes
            generate_expression_tac(node);
        }
        else
        {
            fprintf(stderr, "Error: Unsupported AST node type for statement TAC generation: %d\n", node->type);
            exit(EXIT_FAILURE);
        }
        break;
    }
}

// Function to print 3-address code to a file
void print_tac(TACInstruction *head, const char *output_filename)
{
    FILE *output_file = fopen(output_filename, "w"); // Make output_file local
    if (!output_file)
    {
        perror("Failed to open output file for TAC");
        return;
    }

    TACInstruction *current = head;
    while (current)
    {
        switch (current->op)
        {
        case TAC_NOP:
            fprintf(output_file, "NOP\n");
            break;
        case TAC_ADD:
            print_operand(output_file, current->result);
            fprintf(output_file, " = ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, " + ");
            print_operand(output_file, current->arg2);
            fprintf(output_file, "\n");
            break;
        case TAC_SUB:
            print_operand(output_file, current->result);
            fprintf(output_file, " = ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, " - ");
            print_operand(output_file, current->arg2);
            fprintf(output_file, "\n");
            break;
        case TAC_MUL:
            print_operand(output_file, current->result);
            fprintf(output_file, " = ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, " * ");
            print_operand(output_file, current->arg2);
            fprintf(output_file, "\n");
            break;
        case TAC_DIV:
            print_operand(output_file, current->result);
            fprintf(output_file, " = ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, " / ");
            print_operand(output_file, current->arg2);
            fprintf(output_file, "\n");
            break;
        case TAC_MOD:
            print_operand(output_file, current->result);
            fprintf(output_file, " = ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, " %% ");
            print_operand(output_file, current->arg2);
            fprintf(output_file, "\n");
            break;
        case TAC_NEG:
            print_operand(output_file, current->result);
            fprintf(output_file, " = -");
            print_operand(output_file, current->arg1);
            fprintf(output_file, "\n");
            break;
        case TAC_INC:
            print_operand(output_file, current->result);
            fprintf(output_file, " = ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, " + 1\n"); // Simplified representation for INC
            break;
        case TAC_DEC:
            print_operand(output_file, current->result);
            fprintf(output_file, " = ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, " - 1\n"); // Simplified representation for DEC
            break;
        case TAC_ASSIGN:
            print_operand(output_file, current->result);
            fprintf(output_file, " = ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, "\n");
            break;
        case TAC_EQ:
            print_operand(output_file, current->result);
            fprintf(output_file, " = ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, " == ");
            print_operand(output_file, current->arg2);
            fprintf(output_file, "\n");
            break;
        case TAC_NE:
            print_operand(output_file, current->result);
            fprintf(output_file, " = ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, " != ");
            print_operand(output_file, current->arg2);
            fprintf(output_file, "\n");
            break;
        case TAC_LT:
            print_operand(output_file, current->result);
            fprintf(output_file, " = ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, " < ");
            print_operand(output_file, current->arg2);
            fprintf(output_file, "\n");
            break;
        case TAC_LE:
            print_operand(output_file, current->result);
            fprintf(output_file, " = ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, " <= ");
            print_operand(output_file, current->arg2);
            fprintf(output_file, "\n");
            break;
        case TAC_GT:
            print_operand(output_file, current->result);
            fprintf(output_file, " = ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, " > ");
            print_operand(output_file, current->arg2);
            fprintf(output_file, "\n");
            break;
        case TAC_GE:
            print_operand(output_file, current->result);
            fprintf(output_file, " = ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, " >= ");
            print_operand(output_file, current->arg2);
            fprintf(output_file, "\n");
            break;
        case TAC_AND:
            print_operand(output_file, current->result);
            fprintf(output_file, " = ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, " && ");
            print_operand(output_file, current->arg2);
            fprintf(output_file, "\n");
            break;
        case TAC_OR:
            print_operand(output_file, current->result);
            fprintf(output_file, " = ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, " || ");
            print_operand(output_file, current->arg2);
            fprintf(output_file, "\n");
            break;
        case TAC_NOT:
            print_operand(output_file, current->result);
            fprintf(output_file, " = !");
            print_operand(output_file, current->arg1);
            fprintf(output_file, "\n");
            break;
        case TAC_GOTO:
            fprintf(output_file, "GOTO ");
            print_operand(output_file, current->result);
            fprintf(output_file, "\n");
            break;
        case TAC_IF_TRUE_GOTO:
            fprintf(output_file, "IF ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, " GOTO ");
            print_operand(output_file, current->result);
            fprintf(output_file, "\n");
            break;
        case TAC_IF_FALSE_GOTO:
            fprintf(output_file, "IF_FALSE ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, " GOTO ");
            print_operand(output_file, current->result);
            fprintf(output_file, "\n");
            break;
        case TAC_CALL:
            print_operand(output_file, current->result);
            fprintf(output_file, " = CALL ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, ", %d\n", current->arg2.u.int_val);
            break;
        case TAC_RETURN:
            fprintf(output_file, "RETURN");
            if (current->result.type != OPERAND_NONE)
            {
                fprintf(output_file, " ");
                print_operand(output_file, current->result);
            }
            fprintf(output_file, "\n");
            break;
        case TAC_LABEL:
            fprintf(output_file, "LABEL ");
            print_operand(output_file, current->result);
            fprintf(output_file, ":\n");
            break;
        case TAC_PARAM:
            fprintf(output_file, "PARAM ");
            print_operand(output_file, current->result);
            fprintf(output_file, "\n");
            break;
        case TAC_ARG:
            fprintf(output_file, "ARG ");
            print_operand(output_file, current->result);
            fprintf(output_file, "\n");
            break;
        case TAC_ARRAY_LOAD:
            print_operand(output_file, current->result);
            fprintf(output_file, " = ");
            print_operand(output_file, current->arg1);
            fprintf(output_file, "[");
            print_operand(output_file, current->arg2);
            fprintf(output_file, "]\n");
            break;
        case TAC_ARRAY_STORE:
            print_operand(output_file, current->result);
            fprintf(output_file, "[");
            print_operand(output_file, current->arg1);
            fprintf(output_file, "] = ");
            print_operand(output_file, current->arg2);
            fprintf(output_file, "\n");
            break;
        case TAC_ADDR:
            print_operand(output_file, current->result);
            fprintf(output_file, " = &");
            print_operand(output_file, current->arg1);
            fprintf(output_file, "\n");
            break;
        case TAC_DEREF:
            print_operand(output_file, current->result);
            fprintf(output_file, " = *");
            print_operand(output_file, current->arg1);
            fprintf(output_file, "\n");
            break;
        case TAC_CAST:
            print_operand(output_file, current->result);
            fprintf(output_file, " = (");
            // Placeholder for type name, ideally would print actual type
            fprintf(output_file, "TYPE_UNKNOWN");
            fprintf(output_file, ")");
            print_operand(output_file, current->arg1);
            fprintf(output_file, "\n");
            break;
        case TAC_PRINT:
            fprintf(output_file, "PRINT ");
            print_operand(output_file, current->result);
            fprintf(output_file, "\n");
            break;
        }
        current = current->next;
    }

    fclose(output_file);
}

// Helper function to free operand-specific memory
void free_operand(Operand op)
{
    if (op.owns_string_memory)
    { // Only free if this operand owns the string memory
        if (op.type == OPERAND_VAR && op.u.var_name)
        {
            free(op.u.var_name);
        }
        else if (op.type == OPERAND_LABEL && op.u.label_name)
        {
            free(op.u.label_name);
        }
        else if (op.type == OPERAND_STRING_LITERAL && op.u.string_literal)
        {
            free(op.u.string_literal);
        }
    }
    if (op.owns_data_type_memory && op.data_type)
    {                            // Free data_type if this operand owns it
        free_type(op.data_type); // Use free_type to correctly deallocate Type structures
    }
}

// Function to free the TAC instruction list
void free_tac_list(TACInstruction *head)
{
    TACInstruction *current = head;
    while (current)
    {
        TACInstruction *next = current->next;
        free_operand(current->result);
        free_operand(current->arg1);
        free_operand(current->arg2);
        free(current);
        current = next;
    }
}
