#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "symtab.h"
#include "codegen.h"
#include "tac.h" // Include for 3-address code generation

extern int yyparse(void);
extern ASTNode *root;
int debug = 0;
SymbolTable *symbol_table;

// Declare the initialization function from parser.y
extern void yyparse_init();

int main(int argc, char **argv) {
    // Initialize symbol table and pre-declare functions
    yyparse_init();

    char *input_file = NULL;
    char *output_file = "a.s";
    char *tac_output_file = "a.tac"; // Default output file for 3-address code
    char *ast_output_file = NULL; // New: AST output file
    int i;
    TACInstruction *tac_code = NULL; // Declare tac_code here

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-g") == 0) {
            debug = 1;
        } else if (strcmp(argv[i], "-o") == 0 && (i + 1 < argc)) {
            output_file = argv[++i];
        } else if (strcmp(argv[i], "-tac") == 0 && (i + 1 < argc)) {
            tac_output_file = argv[++i];
        } else if (strcmp(argv[i], "-ast") == 0 && (i + 1 < argc)) { // New: Handle -ast flag
            ast_output_file = argv[++i];
        } else if (input_file == NULL) {
            input_file = argv[i];
        } else {
            fprintf(stderr, "Usage: %s [-g] [-o <output file>] [-tac <tac output file>] [-ast <ast output file>] <input file>\n", argv[0]);
            // Cleanup before returning
            symtab_destroy(symbol_table);
            return 1;
        }
    }

    if (input_file == NULL) {
        fprintf(stderr, "Usage: %s [-g] [-o <output file>] [-tac <tac output file>] [-ast <ast output file>] <input file>\n", argv[0]);
        // Cleanup before returning
        symtab_destroy(symbol_table);
        return 1;
    }

    FILE *file = fopen(input_file, "r");
    if (!file) {
        perror(input_file);
        // Cleanup before returning
        symtab_destroy(symbol_table);
        return 1;
    }
    extern FILE *yyin;
    yyin = file;

    fprintf(stderr, "DEBUG: Starting yyparse().\n");
    if (yyparse() == 0) {
        fprintf(stderr, "DEBUG: yyparse() successful.\n");
        // Write AST if requested with -ast, or print to stdout when -g is set
        if (ast_output_file || debug) {
            FILE *ast_file = stdout; // Default to stdout when -g only
            if (ast_output_file) {
                ast_file = fopen(ast_output_file, "w");
                if (!ast_file) {
                    perror(ast_output_file);
                    symtab_destroy(symbol_table);
                    return 1;
                }
            }
            fprintf(ast_file, "Original AST:\n");
            print_ast(root, 0, ast_file);

            if (ast_file != stdout) {
                fclose(ast_file);
            }
        }
        // root = fold_constants(root); // Temporarily disabled for debugging
        // if (debug) {
        //     printf("\nOptimized AST:\n");
        //     print_ast(root, 0);
        // }

        // Generate and print 3-address code
        fprintf(stderr, "DEBUG: Generating TAC.\n");
        tac_code = generate_tac(root); // Assign to the declared tac_code
        if (tac_code) {
            print_tac(tac_code, tac_output_file);
            printf("3-Address Code written to %s\n", tac_output_file);
            fprintf(stderr, "DEBUG: TAC generated.\n");
        } else {
            fprintf(stderr, "Error: Failed to generate 3-Address Code.\n");
        }

        fprintf(stderr, "DEBUG: Starting code generation.\n");
        generate_code(root, output_file);
        fprintf(stderr, "DEBUG: Code generation complete.\n");
    } else {
        fprintf(stderr, "DEBUG: Compilation failed due to parsing errors.\n");
        // Free symbol table
        symtab_destroy(symbol_table);
        return 1;
    }

    // Free TAC code
    if (tac_code) {
        free_tac_list(tac_code);
        fprintf(stderr, "DEBUG: TAC list freed.\n");
    }
    // Free symbol table
    symtab_destroy(symbol_table);
    fprintf(stderr, "DEBUG: Symbol table destroyed.\n");
    return 0;
}
