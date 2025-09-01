# C Compiler Project (ccomp)

This is a simple C compiler written in C using Flex and Bison.

## Current Stage

The compiler is currently in the **semantic analysis and code generation stage**. It can perform a variety of semantic checks and generate MIPS assembly code for a subset of the C language.

### Features

*   **Lexical Analysis and Parsing**: The compiler can tokenize a C source file and build an Abstract Syntax Tree (AST) from it.
*   **Semantic Analysis**: The compiler performs a variety of semantic checks, including:
    *   Type checking for expressions and assignments.
    *   Scope checking for variables and functions.
    *   Function call validation (number and type of arguments).
    *   Checks for `main` function uniqueness and signature.
*   **Code Generation**: The compiler can generate MIPS assembly code for:
    *   Global and local variable declarations.
    *   Simple arithmetic expressions.
    *   Function definitions and return statements.

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

The `Makefile` includes a `run` target that preprocesses and compiles a test file. To run the default test (`tests/test9.c`), use:

```bash
make run
```

You can also run the compiler on any preprocessed C file:

```bash
./ccomp <input_file>.i
```

### Running the Tests

The `Makefile` includes a `test` target that runs the compiler on all the test files in the `tests` directory.

```bash
make test
```

### Printing the AST

To print the Abstract Syntax Tree (AST), run the compiler with the `-g` flag:

```bash
./ccomp -g tests/test1.c
```

### Cleaning the Project

To remove all generated files, including the executable, object files, and intermediate C files, run the `clean` target:

```bash
make clean
