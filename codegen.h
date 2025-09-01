#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include "symtab.h"

void generate_code(ASTNode *root, const char *output_filename);

#endif // CODEGEN_H
