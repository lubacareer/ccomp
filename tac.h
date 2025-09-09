#ifndef TAC_H
#define TAC_H

#include "ast.h" // For Type and ASTNode
#include <stdbool.h> // Include for bool type

// Define operand types for 3-address code
typedef enum {
    OPERAND_NONE,
    OPERAND_INT_CONST,
    OPERAND_FLOAT_CONST,
    OPERAND_VAR,
    OPERAND_LABEL,
    OPERAND_TEMP,
    OPERAND_STRING_LITERAL
} OperandType;

// Define an operand structure
typedef struct Operand {
    OperandType type;
    union {
        int int_val;
        float float_val;
        char *var_name;
        char *label_name;
        int temp_id;
        char *string_literal;
    } u;
    Type *data_type; // To store the type of the operand
    bool owns_string_memory; // New field to indicate ownership of dynamically allocated string memory
    bool owns_data_type_memory; // New field to indicate ownership of dynamically allocated Type memory
} Operand;

// Define 3-address code operation types
typedef enum {
    TAC_NOP, // No operation
    TAC_ADD, TAC_SUB, TAC_MUL, TAC_DIV, TAC_MOD,
    TAC_NEG, // Unary negation
    TAC_INC, TAC_DEC, // Increment/Decrement
    TAC_ASSIGN,
    TAC_EQ, TAC_NE, TAC_LT, TAC_LE, TAC_GT, TAC_GE,
    TAC_AND, TAC_OR, TAC_NOT, // Logical operations
    TAC_GOTO,
    TAC_IF_TRUE_GOTO, TAC_IF_FALSE_GOTO,
    TAC_CALL, TAC_RETURN,
    TAC_LABEL,
    TAC_PARAM, TAC_ARG,
    TAC_ARRAY_LOAD, TAC_ARRAY_STORE,
    TAC_ADDR, // Get address of a variable
    TAC_DEREF, // Dereference a pointer
    TAC_CAST,
    TAC_PRINT // For debugging/testing
} TACOp;

// Define a 3-address code instruction
typedef struct TACInstruction {
    TACOp op;
    Operand result;
    Operand arg1;
    Operand arg2;
    int label_id; // For TAC_LABEL, TAC_GOTO, TAC_IF_TRUE_GOTO, TAC_IF_FALSE_GOTO
    struct TACInstruction *next;
} TACInstruction;

// Function prototypes for TAC generation
TACInstruction *generate_tac(ASTNode *root);
void print_tac(TACInstruction *head, const char *output_filename);
void free_tac_list(TACInstruction *head);
void free_operand(Operand op);

#endif // TAC_H
