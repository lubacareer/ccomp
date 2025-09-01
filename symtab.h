#ifndef SYMTAB_H
#define SYMTAB_H

#define TABLE_SIZE 1024

// The type of a symbol
typedef enum {
    SYMBOL_VARIABLE,
    SYMBOL_FUNCTION,
    SYMBOL_TYPEDEF,
    SYMBOL_ENUM_MEMBER,
} SymbolType;

// The data type of a variable symbol
typedef enum {
    DATA_TYPE_VOID,
    DATA_TYPE_INT,
    DATA_TYPE_CHAR,
    DATA_TYPE_FLOAT,
    DATA_TYPE_DOUBLE,
    DATA_TYPE_POINTER,
    DATA_TYPE_ARRAY,
    DATA_TYPE_STRUCT,
    DATA_TYPE_UNION,
    DATA_TYPE_BOOL,
} DataType;

// Forward declaration
struct ASTNode;

// A symbol in the symbol table
typedef struct Symbol {
    char *name;
    SymbolType type;
    DataType data_type;
    int scope_level;
    struct Symbol *next; // For hash table chaining

    // For functions
    DataType return_type;
    struct ASTNode *params;
} Symbol;

// A single scope, implemented as a hash table
typedef struct Scope {
    int level;
    Symbol **table;
    struct Scope *parent;
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

int symtab_insert(SymbolTable *st, const char *name, SymbolType type, DataType data_type, DataType return_type, struct ASTNode *params);
Symbol* symtab_lookup(SymbolTable *st, const char *name);
Symbol* symtab_lookup_current_scope(SymbolTable *st, const char *name);

void add_typedef_name(SymbolTable *st, const char *name);
int is_typedef_name(SymbolTable *st, const char *name);

#endif // SYMTAB_H
