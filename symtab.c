#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

// Hash function
static unsigned int hash(const char *name) {
    unsigned int hash = 0;
    while (*name) {
        hash = (hash << 5) + *name++;
    }
    return hash % TABLE_SIZE;
}

// Create a new symbol table
SymbolTable* symtab_create() {
    SymbolTable *st = (SymbolTable*)malloc(sizeof(SymbolTable));
    st->current_scope = NULL;
    symtab_enter_scope(st); // Enter the global scope
    return st;
}

// Destroy a symbol table
void symtab_destroy(SymbolTable *st) {
    while (st->current_scope != NULL) {
        symtab_exit_scope(st);
    }
    free(st);
}

// Enter a new scope
void symtab_enter_scope(SymbolTable *st) {
    Scope *new_scope = (Scope*)malloc(sizeof(Scope));
    new_scope->level = (st->current_scope == NULL) ? 0 : st->current_scope->level + 1;
    new_scope->table = (Symbol**)calloc(TABLE_SIZE, sizeof(Symbol*));
    new_scope->parent = st->current_scope;
    st->current_scope = new_scope;
}

// Exit the current scope
void symtab_exit_scope(SymbolTable *st) {
    if (st->current_scope == NULL) {
        return; // Should not happen
    }

    Scope *scope_to_free = st->current_scope;
    st->current_scope = scope_to_free->parent;

    for (int i = 0; i < TABLE_SIZE; ++i) {
        Symbol *current = scope_to_free->table[i];
        while (current != NULL) {
            Symbol *next = current->next;
            free(current->name);
            free(current);
            current = next;
        }
    }
    free(scope_to_free->table);
    free(scope_to_free);
}

// Insert a symbol into the current scope
int symtab_insert(SymbolTable *st, const char *name, SymbolType type, DataType data_type, DataType return_type, struct ASTNode *params) {
    if (symtab_lookup_current_scope(st, name) != NULL) {
        return 0; // Symbol already exists in the current scope
    }

    unsigned int index = hash(name);
    Symbol *new_symbol = (Symbol*)malloc(sizeof(Symbol));
    new_symbol->name = strdup(name);
    new_symbol->type = type;
    new_symbol->data_type = data_type;
    new_symbol->scope_level = st->current_scope->level;
    new_symbol->return_type = return_type;
    new_symbol->params = params;
    new_symbol->next = st->current_scope->table[index];
    st->current_scope->table[index] = new_symbol;

    return 1;
}

// Lookup a symbol in the current scope and all parent scopes
Symbol* symtab_lookup(SymbolTable *st, const char *name) {
    Scope *scope = st->current_scope;
    while (scope != NULL) {
        unsigned int index = hash(name);
        Symbol *current = scope->table[index];
        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                return current;
            }
            current = current->next;
        }
        scope = scope->parent;
    }
    return NULL;
}

// Lookup a symbol in the current scope only
Symbol* symtab_lookup_current_scope(SymbolTable *st, const char *name) {
    if (st->current_scope == NULL) {
        return NULL;
    }

    unsigned int index = hash(name);
    Symbol *current = st->current_scope->table[index];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Add a typedef name to the symbol table
void add_typedef_name(SymbolTable *st, const char *name) {
    symtab_insert(st, name, SYMBOL_TYPEDEF, DATA_TYPE_VOID, DATA_TYPE_VOID, NULL);
}

// Check if a name is a typedef name
int is_typedef_name(SymbolTable *st, const char *name) {
    Symbol *symbol = symtab_lookup(st, name);
    return (symbol != NULL && symbol->type == SYMBOL_TYPEDEF);
}
