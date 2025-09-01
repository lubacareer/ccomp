# C Compiler Project (ccomp)

This is a simple C compiler written in C using Flex and Bison.

## Current Stage

The compiler is currently in the **lexical analysis and parsing stage**. It can tokenize a C source file and build an Abstract Syntax Tree (AST) from it. However, it is still under active development and does not yet generate executable code. The parser has known issues and may fail on complex C syntax.

## Getting Started

### Prerequisites

- `gcc`
- `flex`
- `bison`
- `make`

### Building the Compiler

To build the compiler, run the `make` command:

```bash
make
```

This will create the `ccomp` executable in the project directory.

### Running the Compiler

The `Makefile` includes a `run` target that preprocesses the `test.c` file and then runs the compiler on it.

```bash
make run
```

This command is equivalent to:

```bash
gcc -E test.c -o test.i
./ccomp test.i
```

You can also run the compiler on any preprocessed C file:

```bash
./ccomp <input_file>.i
```

### Printing the AST

To print the Abstract Syntax Tree (AST), run the compiler with the `-g` flag:

```bash
./ccomp -g test.i
```

This is the `test.c` file that is used to generate the AST:

```c
#define MAX_SIZE 100

// External variable declaration
extern int global_counter;

// Volatile variable
volatile int status_register;

// Struct definition
struct Point {
    int x;
    int y;
};

// Union definition
union Data {
    int i;
    float f;
    char str[20];
};

// Enum definition
enum Color {
    RED,
    GREEN,
    BLUE
};

// Typedef for a struct
typedef struct Point Point2D;

// Static variable
static int file_scope_variable = 0;

// Const variable
const double PI = 3.14159;

// Forward declaration of a struct
struct Node;

// Function prototype
void print_point(Point2D p);

// Inline function
inline int max(int a, int b) {
    return a > b ? a : b;
}

// A static inline function
static inline int min(int a, int b) {
    return a < b ? a : b;
}

// Function with complex declarator (pointer to function)
void (*signal_handler)(int);

int main() {
    // Multiple declarations
    int i = 0, j, k = 10;
    
    // Array of pointers
    char *messages[3];
    messages[0] = "Hello";
    messages[1] = "World";
    messages[2] = "!";

    // Pointer to an array
    int (*matrix)[2];
    int arr[2][2] = {{1, 2}, {3, 4}};
    matrix = arr;

    // Struct and union usage
    Point2D p1 = {10, 20};
    union Data data;
    data.i = 10;

    // Control flow: for loop and if-else
    for (i = 0; i < 3; i++) {
        if (i % 2 == 0) {
            print_point(p1);
        } else {
            // do nothing
        }
    }

    // Control flow: while and do-while
    int count = 5;
    while (count > 0) {
        count--;
    }
    do {
        count++;
    } while (count < 5);

    // Control flow: switch (removed for testing)
    int day = 4;
    if (day == 6) {
    } else if (day == 7) {
    } else {
    }
}

void print_point(Point2D p) {
    // This function is just a stub for demonstration
}
```

This will produce the following output:

```
AST:
PROGRAM
  STATEMENT_LIST
    STATEMENT_LIST
      VAR_DECL: global_counter (extern) of type INT
    STATEMENT_LIST
      VAR_DECL: status_register (volatile) of type INT
    TYPE_DECL: STRUCT Point
    TYPE_DECL: UNION Data
    TYPE_DECL: ENUM Color
    TYPEDEF: (null)
STRUCT Point
    STATEMENT_LIST
      VAR_DECL: file_scope_variable of type INT =
        INTEGER: 0
    STATEMENT_LIST
      VAR_DECL: PI of type DOUBLE =
        FLOAT: 3.141590
    TYPE_DECL: STRUCT Node
    STATEMENT_LIST
      VAR_DECL: print_point of type FUNCTION returning VOID
    FUNCTION_DEFINITION: max (inline), returns INT
      STATEMENT_LIST
        RETURN
          TERNARY_OP
            BINARY_OP: >
              VARIABLE: a
              VARIABLE: b
            VARIABLE: a
            VARIABLE: b
    FUNCTION_DEFINITION: min (inline), returns INT
      STATEMENT_LIST
        RETURN
          TERNARY_OP
            BINARY_OP: <
              VARIABLE: a
              VARIABLE: b
            VARIABLE: a
            VARIABLE: b
    STATEMENT_LIST
      VAR_DECL: signal_handler of type POINTER to FUNCTION returning VOID
    FUNCTION_DEFINITION: main, returns INT
      STATEMENT_LIST
        STATEMENT_LIST
          VAR_DECL: i of type INT =
            INTEGER: 0
          VAR_DECL: j of type INT
          VAR_DECL: k of type INT =
            INTEGER: 10
        STATEMENT_LIST
          VAR_DECL: messages of type POINTER to ARRAY of 0 CHAR
        ASSIGN
          ARRAY_ACCESS
            VARIABLE: messages
            INTEGER: 0
          STRING_LITERAL: "Hello"
        ASSIGN
          ARRAY_ACCESS
            VARIABLE: messages
            INTEGER: 1
          STRING_LITERAL: "World"
        ASSIGN
          ARRAY_ACCESS
            VARIABLE: messages
            INTEGER: 2
          STRING_LITERAL: "!"
        STATEMENT_LIST
          VAR_DECL: matrix of type ARRAY of 0 POINTER to INT
        STATEMENT_LIST
          VAR_DECL: arr of type ARRAY of 0 ARRAY of 0 INT =
            INITIALIZER_LIST
              INITIALIZER_LIST
                INTEGER: 1
                INTEGER: 2
              INITIALIZER_LIST
                INTEGER: 3
                INTEGER: 4
        ASSIGN
          VARIABLE: matrix
          VARIABLE: arr
        STATEMENT_LIST
          VAR_DECL: p1 of type TYPEDEF Point2D =
            INITIALIZER_LIST
              INTEGER: 10
              INTEGER: 20
        STATEMENT_LIST
          VAR_DECL: data of type UNION Data
        ASSIGN
          MEMBER_ACCESS: i
            VARIABLE: data
          INTEGER: 10
        FOR
          ASSIGN
            VARIABLE: i
            INTEGER: 0
          BINARY_OP: <
            VARIABLE: i
            INTEGER: 3
          UNARY_OP: ++
            VARIABLE: i
          STATEMENT_LIST
            IF
              BINARY_OP: ==
                BINARY_OP: %
                  VARIABLE: i
                  INTEGER: 2
                INTEGER: 0
              STATEMENT_LIST
                FUNC_CALL: (null)
                  ARG_LIST
                    VARIABLE: p1
            ELSE
              STATEMENT_LIST
        STATEMENT_LIST
          VAR_DECL: count of type INT =
            INTEGER: 5
        WHILE
          BINARY_OP: >
            VARIABLE: count
            INTEGER: 0
          STATEMENT_LIST
            UNARY_OP: --
              VARIABLE: count
        DO_WHILE
          STATEMENT_LIST
            UNARY_OP: ++
              VARIABLE: count
          BINARY_OP: <
            VARIABLE: count
            INTEGER: 5
        STATEMENT_LIST
          VAR_DECL: day of type INT =
            INTEGER: 4
        IF
          BINARY_OP: ==
            VARIABLE: day
            INTEGER: 6
          STATEMENT_LIST
        ELSE
          IF
            BINARY_OP: ==
              VARIABLE: day
              INTEGER: 7
            STATEMENT_LIST
          ELSE
            STATEMENT_LIST
    FUNCTION_DEFINITION: print_point, returns VOID
      STATEMENT_LIST
```

### Cleaning the Project

To remove all generated files, including the executable, object files, and intermediate C files, run the `clean` target:

```bash
make clean
