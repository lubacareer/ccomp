#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include "ast.h" // Include ast.h for Type definition
#include "parser.h" // Include parser.h for operator definitions

extern SymbolTable *symbol_table;
extern Symbol *current_function_symbol;

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
    new_scope->current_offset = 0; // Initialize offset for new scope
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
            // Free Type* data_type and return_type if they were dynamically allocated
            // This is a simplification, a full compiler would need to track ownership
            // of Type* objects to avoid double-free or premature free.
            // For now, assuming Type* are either static or freed elsewhere if needed.
            free(current);
            current = next;
        }
    }
    free(scope_to_free->table);
    free(scope_to_free);
}

// Insert a symbol into the current scope
int symtab_insert(SymbolTable *st, const char *name, SymbolType type, Type *data_type, Type *return_type, struct ASTNode *params, int enum_val) {
    Symbol *existing_symbol = symtab_lookup_current_scope(st, name);

    if (existing_symbol != NULL) {
        // Allow re-declaration of functions if the existing one is a function declaration
        if (existing_symbol->type == SYMBOL_FUNCTION && type == SYMBOL_FUNCTION) {
            // If an existing symbol is a function and the new symbol is also a function,
            // it's a re-declaration or definition. Update the existing symbol.
            // A more robust compiler would perform stricter checks for compatibility
            // between declaration and definition.
            existing_symbol->data_type = data_type;
            existing_symbol->return_type = return_type;
            existing_symbol->params = params;
            return 1; // Successfully updated
        } else if (existing_symbol->type == SYMBOL_VARIABLE && type == SYMBOL_FUNCTION) {
            // This case should ideally be caught by the parser as a type mismatch,
            // but as a safeguard, prevent a variable from being redefined as a function.
            return 0;
        } else if (existing_symbol->type == SYMBOL_VARIABLE && type == SYMBOL_VARIABLE) {
            // Allow re-declaration of global variables (extern)
            // A more robust compiler would perform stricter checks for compatibility
            // between declarations.
            if (st->current_scope->level == 0) { // Only for global scope
                return 1; // Successfully updated
            }
        } else if (existing_symbol->type == SYMBOL_TYPEDEF && type == SYMBOL_TYPEDEF) {
            // Allow re-declaration of typedefs
            return 1; // Successfully updated
        } else if (existing_symbol->type == SYMBOL_ENUMERATOR && type == SYMBOL_ENUMERATOR) {
            // Allow re-declaration of enumerators (though typically they are unique)
            return 1; // Successfully updated
        } else if (existing_symbol->type == SYMBOL_STRUCT && type == SYMBOL_STRUCT) {
            // Allow re-declaration of structs
            return 1; // Successfully updated
        } else if (existing_symbol->type == SYMBOL_UNION && type == SYMBOL_UNION) {
            // Allow re-declaration of unions
            return 1; // Successfully updated
        } else if (existing_symbol->type == SYMBOL_ENUM && type == SYMBOL_ENUM) {
            // Allow re-declaration of enums
            return 1; // Successfully updated
        }
        return 0; // Symbol already exists and cannot be redefined
    }

    unsigned int index = hash(name);
    Symbol *new_symbol = (Symbol*)malloc(sizeof(Symbol));
    new_symbol->name = strdup(name);
    new_symbol->type = type;
    new_symbol->data_type = data_type;
    new_symbol->scope_level = st->current_scope->level;
    new_symbol->return_type = return_type;
    new_symbol->params = params;
    new_symbol->enum_value = 0; // Initialize enum_value

    if (type == SYMBOL_VARIABLE && new_symbol->scope_level > 0) { // Not global
        // Calculate offset based on type size (simplified, assuming all types are 4 bytes for now)
        st->current_scope->current_offset -= 4; 
        new_symbol->offset = st->current_scope->current_offset;
    } else if (type == SYMBOL_ENUMERATOR) {
        new_symbol->enum_value = enum_val;
        new_symbol->offset = 0; // Enumerators don't have stack offsets
    } else {
        new_symbol->offset = 0; // Global variables and functions have no stack offset
    }

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
void add_typedef_name(SymbolTable *st, const char *name, Type *actual_type) {
    symtab_insert(st, name, SYMBOL_TYPEDEF, actual_type, NULL, NULL, 0);
}

// Get the actual type of a typedef name
Type* get_typedef_type(SymbolTable *st, const char *name) {
    Symbol *symbol = symtab_lookup(st, name);
    if (symbol != NULL && symbol->type == SYMBOL_TYPEDEF) {
        return symbol->data_type;
    }
    return NULL;
}

// Check if a name is a typedef name
int is_typedef_name(SymbolTable *st, const char *name) {
    Symbol *symbol = symtab_lookup(st, name);
    return (symbol != NULL && symbol->type == SYMBOL_TYPEDEF);
}

// New: Helper function to check if a Type* is owned by the symbol table
int is_type_owned_by_symtab(SymbolTable *st, Type *type) {
    // Iterate through all symbols in all scopes to see if this type is referenced
    // This is a potentially expensive operation, but necessary to ensure correctness.
    // A more optimized approach might involve a separate set of "owned types" in the symbol table.
    Scope *scope = st->current_scope;
    while (scope != NULL) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Symbol *current = scope->table[i];
            while (current != NULL) {
                if (current->data_type == type || current->return_type == type) {
                    return 1; // Found a match, type is owned by symtab
                }
                // Also check nested types if applicable (e.g., pointer to a type in symtab)
                // This would require a recursive check, which is complex.
                // For now, a direct comparison is sufficient for the immediate problem.
                current = current->next;
            }
        }
        scope = scope->parent;
    }
    return 0; // Type is not found in symbol table
}

extern void yyerror(const char *s);
extern int compare_types(Type *a, Type *b);
extern int is_arithmetic_type(Type *type);
extern int is_scalar_type(Type *type);
extern int is_integer_type(Type *type);
extern Symbol *get_current_function();
extern TypeAndOwnership get_expression_type(ASTNode *expr);

