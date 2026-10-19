# Compiler Design

A C++ compiler-design project exploring core stages of a compiler for a subset of C-like language, from symbol management and lexical analysis to syntax analysis and assembly code generation. The repository organizes the work into separate modules built with **C++**, **Flex**, and **Bison/Yacc**.

## Project Overview

The codebase covers several important compiler concepts:

- **Symbol Table:** Scoped symbol management, including insertion, lookup, deletion, and scope traversal.
- **Lexical Analysis:** Token recognition for keywords, identifiers, literals, operators, and delimiters, along with diagnostic logging.
- **Syntax Analysis:** Grammar rules for C-like program constructs, parse-tree representation, and parser diagnostics.
- **Code Generation:** Assembly generation routines and a peephole optimization pass for generated assembly.

These modules provide a practical look at how source code is processed across different compiler stages.

## Repository Structure

```text
Compiler-main/
├── 2005050_symbol_table/     # Symbol table implementation and command-driven tests
├── 2005050_lexer/            # Flex-based lexical analyzer and examples
├── 2005050_parser/           # Lexer/parser grammar and parse-tree utilities
└── 2005050_ICG/              # Code-generation routines, build script, and sample inputs
```

Each directory contains its own source files and supporting inputs or output artifacts.

## Technologies

- **Language:** C++
- **Lexer generator:** Flex
- **Parser generator:** Bison/Yacc
- **Build tools:** GNU `g++`, Bash
- **Target assembly syntax:** 16-bit x86-style assembly (MASM/TASM conventions)

## Getting Started

### Prerequisites

On a Linux environment, install the relevant development tools. For example, on Ubuntu/Debian:

```bash
sudo apt update
sudo apt install g++ flex bison libfl-dev
```

### Symbol Table

```bash
cd 2005050_symbol_table
g++ 2005050_main.cpp -o symbol_table
./symbol_table
```

This module reads commands from `input.txt` and writes results to `output.txt` (in append mode).

### Lexical Analyzer

```bash
cd 2005050_lexer/2005050
flex 2005050.l
g++ lex.yy.c -lfl -o lexer
./lexer input.txt
```

The lexer records token and diagnostic information in its corresponding text output files.

### Parser

From `2005050_parser/`, generate the parser and scanner sources:

```bash
bison -d -y 2005050.y
flex 2005050.l
g++ y.tab.c lex.yy.c -lfl -o parser
./parser path/to/input.c
```

### Code Generation

The `2005050_ICG/` directory includes a Bash script to generate, compile, and run the Flex/Bison-based program with a sample input:

```bash
cd 2005050_ICG
bash 2005050.sh
```

You can also run the generated executable with another included input file:

```bash
./test test1_i.c
```

Depending on the input, the code-generation module writes assembly and diagnostic artifacts such as `code.asm`, `optimized_code.asm`, `parsetree.txt`, and `log.txt`. Existing output files may be appended to by the programs, so clear or back them up before comparing separate runs.

## Example Inputs and Outputs

The repository includes sample C-like source files in `2005050_ICG/`, as well as example lexer input and symbol-table commands. These are useful for exploring tokenization, grammar actions, scope handling, and the assembly-generation routines.

## Notes

The components are intended for educational exploration of compiler implementation techniques. Build and runtime behavior depends on the source constructs exercised and the local toolchain. Generated assembly uses legacy 16-bit x86 conventions and requires a compatible assembler/runtime environment if you want to assemble and execute it.

**Course**: CSE 310 - Compiler Sessional Coursework
**Institution**: Bangladesh University of Engineering and Technology (BUET)
