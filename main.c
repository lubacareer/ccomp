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
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-g") == 0) {
            debug = 1;
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                output_file = argv[++i];
            } else {
                fprintf(stderr, "Missing filename after -o\n");
                return 1;
            }
        } else {
            input_file = argv[i];
        }
    }

    if (input_file) {
        FILE *file = fopen(input_file, "r");
        if (!file) {
            perror(input_file);
            return 1;
        }
        extern FILE *yyin;
        yyin = file;
    }

    if (yyparse() == 0) {
        if (debug) {
            printf("AST:\n");
            print_ast(root, 0);
        }
        generate_code(root, output_file);
    }

    symtab_destroy(symbol_table);
    return 0;
}
