# ccomp — A Simple C Compiler

ccomp is a teaching-oriented C compiler built with Flex (lexer), Bison (parser), and C.
It parses C into an Abstract Syntax Tree (AST), performs semantic checks using symbol
tables, emits three-address code (TAC), and generates x86-64 AT&T assembly that can be
assembled and linked with `gcc`.

## Features

- Lexing and parsing to an AST.
- Semantic analysis: scopes, basic type checks, function signatures and calls.
- TAC generation with control flow and expressions.
- x86-64 assembly generation (AT&T syntax) for a C subset.

## Prerequisites

You need a standard C toolchain with Flex and Bison:

- gcc
- make
- flex
- bison

Install examples:

- Debian/Ubuntu: `sudo apt-get update && sudo apt-get install -y build-essential flex bison`
- Fedora: `sudo dnf install -y gcc make flex bison`
- Arch: `sudo pacman -S --needed base-devel flex bison`
- macOS (Homebrew): `brew install flex bison`

Note: Ensure your PATH uses Homebrew’s `flex`/`bison` if the system versions are too old.

## Build

Builds the compiler and regenerates `lexer.c`/`parser.c` as needed:

```bash
make
```

This produces the `./ccomp` executable in the project root.

Useful targets:

- `make clean` — remove build outputs and generated files.

## Usage

Basic syntax (validated against `main.c`):

```text
./ccomp [-g] [-o <asm.s>] [-tac <out.tac>] [-ast <ast.txt>] <input.c>
```

- `-g`: print the AST to stdout (for debugging).
- `-o <asm.s>`: set assembly output file (default: `a.s`).
- `-tac <out.tac>`: set TAC output file (default: `a.tac`).
- `-ast <ast.txt>`: write AST to a file instead of stdout.

The compiler always emits TAC and assembly. To turn the assembly into an executable,
compile it with gcc.

### Examples

Generate AST and TAC for the full feature test (as requested), plus assembly:

```bash
./ccomp -ast ast.txt -tac out.tac tests/full_feature_test.c
```

Assemble and run the generated program (uses default `a.s`):

```bash
gcc -o a.out a.s
./a.out
```

Choose custom output names for both TAC and assembly:

```bash
./ccomp -tac ir.tac -o program.s tests/test.c
gcc -o program program.s
./program
```

## Development Notes

Generation steps used by the Makefile:

- Lexer: `flex -o lexer.c lexer.l`
- Parser: `bison -d -Wcounterexamples -o parser.c parser.y`

Run `make` to rebuild incrementally; `make clean` to start fresh.

## Tests

Sample sources live under `tests/`. You can invoke `./ccomp` directly on any of them
as shown in the examples above.

## Limitations

This is an educational compiler covering a subset of C. The generated assembly targets
x86-64 with AT&T syntax and may not cover all language features.

