#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "symtab.h"
#include "codegen.h"

extern int yyparse(void);
extern ASTNode *root;
int debug = 0;
SymbolTable *symbol_table;

int main(int argc, char **argv) {
    symbol_table = symtab_create();
    char *input_file = NULL;
    char *output_file = "a.s";
    int i;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-g") == 0) {
            debug = 1;
        } else if (input_file == NULL) {
            input_file = argv[i];
        } else if (output_file == NULL) {
            output_file = argv[i];
        } else {
            fprintf(stderr, "Usage: %s [-g] <input file> [output file]\n", argv[0]);
            return 1;
        }
    }

    if (input_file == NULL) {
        fprintf(stderr, "Usage: %s [-g] <input file> [output file]\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(input_file, "r");
    if (!file) {
        perror(input_file);
        return 1;
    }
    extern FILE *yyin;
    yyin = file;

    if (yyparse() == 0) {
        if (debug) {
            printf("Original AST:\n");
            print_ast(root, 0);
        }
        root = fold_constants(root);
        if (debug) {
            printf("\nOptimized AST:\n");
            print_ast(root, 0);
        }
        generate_code(root, output_file);
    }

    // symtab_destroy(symbol_table); // Scopes are now owned by the AST
    return 0;
}
