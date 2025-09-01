#include <stdio.h>
#include <string.h>
#include "ast.h"

extern int yyparse(void);
extern ASTNode *root;
int debug = 0;

int main(int argc, char **argv) {
    char *input_file = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-g") == 0) {
            debug = 1;
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
        // Placeholder for code generation
    }

    return 0;
}
