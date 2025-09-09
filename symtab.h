#ifndef SYMTAB_H
#define SYMTAB_H

#define TABLE_SIZE 1024

// The type of a symbol
typedef enum {
    SYMBOL_VARIABLE,
    SYMBOL_FUNCTION,
    SYMBOL_TYPEDEF,
    SYMBOL_ENUM_MEMBER,
    SYMBOL_ENUMERATOR,
    SYMBOL_LABEL, // New: For labels in goto statements
    SYMBOL_STRUCT,
    SYMBOL_UNION,
    SYMBOL_ENUM
} SymbolType;

// Forward declaration
struct ASTNode;
struct Type; // Forward declaration for Type

// A symbol in the symbol table
typedef struct Symbol {
    char *name;
    SymbolType type;
    struct Type *data_type; // Use Type* for more detailed type information
    int scope_level;
    struct Symbol *next; // For hash table chaining

    // For functions
    struct Type *return_type; // Use Type* for more detailed return type
    struct ASTNode *params;

    // For variables
    int offset;
    // For enumerators
    int enum_value;
} Symbol;

// A single scope, implemented as a hash table
typedef struct Scope {
    int level;
    Symbol **table;
    struct Scope *parent;
    int current_offset; // For local variable stack offsets
} Scope;

// The symbol table, which is a stack of scopes
typedef struct SymbolTable {
    Scope *current_scope;
} SymbolTable;

// Function declarations
SymbolTable* symtab_create();
void symtab_destroy(SymbolTable *st);

void symtab_enter_scope(SymbolTable *st);
void symtab_exit_scope(SymbolTable *st);

int symtab_insert(SymbolTable *st, const char *name, SymbolType type, struct Type *data_type, struct Type *return_type, struct ASTNode *params, int enum_val);
Symbol* symtab_lookup(SymbolTable *st, const char *name);
Symbol* symtab_lookup_current_scope(SymbolTable *st, const char *name);

void add_typedef_name(SymbolTable *st, const char *name, struct Type *actual_type);
struct Type* get_typedef_type(SymbolTable *st, const char *name);
int is_typedef_name(SymbolTable *st, const char *name);
int is_type_owned_by_symtab(SymbolTable *st, struct Type *type); // New: Declare helper function

#endif // SYMTAB_H
