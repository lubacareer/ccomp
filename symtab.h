#ifndef SYMTAB_H
#define SYMTAB_H

typedef struct Symbol {
    char *name;
    // Add more fields as needed, e.g., for type information
    struct Symbol *next;
} Symbol;

void add_typedef_name(const char *name);
int is_typedef_name(const char *name);

#endif // SYMTAB_H
