#include <string.h>
#include <stdlib.h>
#include "symtab.h"

static Symbol *head = NULL;

void add_typedef_name(const char *name) {
    Symbol *new_symbol = (Symbol *)malloc(sizeof(Symbol));
    new_symbol->name = strdup(name);
    new_symbol->next = head;
    head = new_symbol;
}

int is_typedef_name(const char *name) {
    Symbol *current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}
