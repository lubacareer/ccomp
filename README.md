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

### Cleaning the Project

To remove all generated files, including the executable, object files, and intermediate C files, run the `clean` target:

```bash
make clean
