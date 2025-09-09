#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "parser.h"

extern SymbolTable *symbol_table;

static FILE *output_file;

static void generate_data_section(ASTNode *node);
static void generate_text_section(ASTNode *node, Scope *scope);
static void generate_expression(ASTNode *node, Scope *scope);

void generate_code(ASTNode *root, const char *output_filename) {
    output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror(output_filename);
        return;
    }

    fprintf(output_file, ".data\n");
    generate_data_section(root);

    fprintf(output_file, ".text\n");
    generate_text_section(root, symbol_table->current_scope);

    fclose(output_file);
}

static void generate_data_section(ASTNode *node) {
    if (!node) {
        return;
    }

    if (node->type == NODE_TYPE_PROGRAM) {
        generate_data_section(node->program.statements);
    } else if (node->type == NODE_TYPE_STATEMENT_LIST) {
        for (int i = 0; i < node->statement_list.count; i++) {
            generate_data_section(node->statement_list.statements[i]);
        }
    } else if (node->type == NODE_TYPE_VAR_DECL) {
        // Assuming global scope for now
        if (node->var_decl.var_type->base == TYPE_INT) {
            fprintf(output_file, "%s: .long %d\n", node->var_decl.name, node->var_decl.init_expr ? node->var_decl.init_expr->integer_value : 0);
        }
    }
}

static int get_var_decl_size(ASTNode *node) {
    if (!node) {
        return 0;
    }

    int size = 0;
    if (node->type == NODE_TYPE_STATEMENT_LIST) {
        for (int i = 0; i < node->statement_list.count; i++) {
            size += get_var_decl_size(node->statement_list.statements[i]);
        }
    } else if (node->type == NODE_TYPE_VAR_DECL) {
        size += 4; // Assuming all local variables are 4 bytes (int)
    }
    
    return size;
}

static int calculate_stack_frame_size(ASTNode *node) {
    int size = get_var_decl_size(node);
    // Align to 16 bytes
    return (size + 15) & -16;
}

static Symbol *lookup_symbol(Scope *scope, const char *name) {
    while (scope) {
        for (int i = 0; i < TABLE_SIZE; i++) {
            Symbol *s = scope->table[i];
            while (s) {
                if (strcmp(s->name, name) == 0) {
                    return s;
                }
                s = s->next;
            }
        }
        scope = scope->parent;
    }
    return NULL;
}

static void generate_text_section(ASTNode *node, Scope *scope) {
    if (!node) {
        return;
    }

    switch (node->type) {
        case NODE_TYPE_PROGRAM:
            generate_text_section(node->program.statements, scope);
            break;
        case NODE_TYPE_STATEMENT_LIST:
            {
                Scope *new_scope = node->statement_list.scope ? node->statement_list.scope : scope;
                for (int i = 0; i < node->statement_list.count; i++) {
                    generate_text_section(node->statement_list.statements[i], new_scope);
                }
            }
            break;
        case NODE_TYPE_FUNCTION_DEFINITION: {
            fprintf(output_file, ".globl %s\n", node->function_definition.declarator->var_decl.name);
            fprintf(output_file, "%s:\n", node->function_definition.declarator->var_decl.name);
            
            // Prologue
            fprintf(output_file, "  pushq %%rbp\n");
            fprintf(output_file, "  movq %%rsp, %%rbp\n");
            int frame_size = calculate_stack_frame_size(node->function_definition.body);
            if (frame_size > 0) {
                fprintf(output_file, "  subq $%d, %%rsp\n", frame_size);
            }

            generate_text_section(node->function_definition.body, node->function_definition.scope);

            // Epilogue
            fprintf(output_file, "  movq %%rbp, %%rsp\n");
            fprintf(output_file, "  popq %%rbp\n");
            fprintf(output_file, "  ret\n");
            break;
        }
        case NODE_TYPE_RETURN:
            if (node->return_statement.statement) {
                generate_expression(node->return_statement.statement, scope);
            }
            break;
        case NODE_TYPE_VAR_DECL:
            if (node->var_decl.init_expr) {
                generate_expression(node->var_decl.init_expr, scope);
                Symbol *s = lookup_symbol(scope, node->var_decl.name);
                if (s) {
                    fprintf(output_file, "  movl %%eax, %d(%%rbp)\n", s->offset);
                }
            }
            break;
        default:
            generate_expression(node, scope);
            break;
    }
}

static void generate_expression(ASTNode *node, Scope *scope) {
    if (!node) {
        return;
    }

    switch (node->type) {
        case NODE_TYPE_BINARY_OP:
            generate_expression(node->binary_op.right, scope);
            fprintf(output_file, "  pushq %%rax\n");
            generate_expression(node->binary_op.left, scope);
            fprintf(output_file, "  popq %%rcx\n");
            switch (node->binary_op.op) {
                case T_ADD:
                    fprintf(output_file, "  addl %%ecx, %%eax\n");
                    break;
                case T_SUB:
                    fprintf(output_file, "  subl %%ecx, %%eax\n");
                    break;
            }
            break;
        case NODE_TYPE_VARIABLE: {
            Symbol *s = lookup_symbol(scope, node->variable.name);
            if (s) {
                fprintf(output_file, "  movl %d(%%rbp), %%eax\n", s->offset);
            }
            break;
        }
        case NODE_TYPE_INTEGER:
            fprintf(output_file, "  movl $%d, %%eax\n", node->integer_value);
            break;
        default:
            break;
    }
}
