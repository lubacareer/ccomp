#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "parser.h"

extern SymbolTable *symbol_table;

static FILE *output_file;

static void generate_data_section(ASTNode *node);
static void generate_text_section(ASTNode *node);

void generate_code(ASTNode *root, const char *output_filename) {
    output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror(output_filename);
        return;
    }

    fprintf(output_file, ".data\n");
    generate_data_section(root);

    fprintf(output_file, ".text\n");
    fprintf(output_file, ".globl main\n");
    generate_text_section(root);

    fclose(output_file);
}

static void generate_data_section(ASTNode *node) {
    if (!node) {
        return;
    }

    switch (node->type) {
        case NODE_TYPE_PROGRAM:
            generate_data_section(node->program.statements);
            break;
        case NODE_TYPE_STATEMENT_LIST:
            for (int i = 0; i < node->statement_list.count; i++) {
                generate_data_section(node->statement_list.statements[i]);
            }
            break;
        case NODE_TYPE_VAR_DECL:
            // For now, we only handle global variables.
            // We'll need to add scope checking to distinguish between global and local variables.
            if (node->var_decl.var_type->base == TYPE_INT) {
                fprintf(output_file, "%s: .word %d\n", node->var_decl.name, node->var_decl.init_expr ? node->var_decl.init_expr->integer_value : 0);
            }
            break;
        default:
            break;
    }
}

static int calculate_stack_frame_size(ASTNode *node) {
    if (!node) {
        return 0;
    }

    int size = 0;
    if (node->type == NODE_TYPE_STATEMENT_LIST) {
        for (int i = 0; i < node->statement_list.count; i++) {
            if (node->statement_list.statements[i]->type == NODE_TYPE_VAR_DECL) {
                size += 4; // Assuming all variables are 4 bytes
            }
        }
    }

    return size;
}

static int get_local_var_offset(const char *name) {
    int offset = 0;
    Scope *scope = symbol_table->current_scope;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol *s = scope->table[i];
        while (s) {
            if (s->type == SYMBOL_VARIABLE) {
                offset -= 4;
                if (strcmp(s->name, name) == 0) {
                    return offset;
                }
            }
            s = s->next;
        }
    }
    return 0; // Should not happen
}

static void generate_text_section(ASTNode *node) {
    if (!node) {
        return;
    }

    switch (node->type) {
        case NODE_TYPE_PROGRAM:
            generate_text_section(node->program.statements);
            break;
        case NODE_TYPE_STATEMENT_LIST:
            for (int i = 0; i < node->statement_list.count; i++) {
                generate_text_section(node->statement_list.statements[i]);
            }
            break;
        case NODE_TYPE_FUNCTION_DEFINITION: {
            int frame_size = calculate_stack_frame_size(node->function_definition.body);
            fprintf(output_file, "%s:\n", node->function_definition.name);
            // Standard function prologue
            fprintf(output_file, "  addi $sp, $sp, -%d\n", frame_size + 4);
            fprintf(output_file, "  sw $fp, %d($sp)\n", frame_size);
            fprintf(output_file, "  move $fp, $sp\n");

            generate_text_section(node->function_definition.body);

            // Standard function epilogue
            fprintf(output_file, "  move $sp, $fp\n");
            fprintf(output_file, "  lw $fp, %d($sp)\n", frame_size);
            fprintf(output_file, "  addi $sp, $sp, %d\n", frame_size + 4);
            fprintf(output_file, "  jr $ra\n");
            break;
        }
        case NODE_TYPE_RETURN:
            if (node->return_statement.statement) {
                generate_text_section(node->return_statement.statement);
                fprintf(output_file, "  move $v0, $t0\n");
            }
            break;
        case NODE_TYPE_BINARY_OP:
            generate_text_section(node->binary_op.left);
            fprintf(output_file, "  sw $t0, 0($sp)\n");
            fprintf(output_file, "  addiu $sp, $sp, -4\n");
            generate_text_section(node->binary_op.right);
            fprintf(output_file, "  lw $t1, 4($sp)\n");
            fprintf(output_file, "  addiu $sp, $sp, 4\n");
            switch (node->binary_op.op) {
                case T_ADD:
                    fprintf(output_file, "  add $t0, $t1, $t0\n");
                    break;
                case T_SUB:
                    fprintf(output_file, "  sub $t0, $t1, $t0\n");
                    break;
            }
            break;
        case NODE_TYPE_VAR_DECL:
            if (node->var_decl.init_expr) {
                generate_text_section(node->var_decl.init_expr);
                int offset = get_local_var_offset(node->var_decl.name);
                fprintf(output_file, "  sw $t0, %d($fp)\n", offset);
            }
            break;
        case NODE_TYPE_VARIABLE: {
            int offset = get_local_var_offset(node->variable.name);
            fprintf(output_file, "  lw $t0, %d($fp)\n", offset);
            break;
        }
        case NODE_TYPE_INTEGER:
            fprintf(output_file, "  li $t0, %d\n", node->integer_value);
            break;
        default:
            break;
    }
}
