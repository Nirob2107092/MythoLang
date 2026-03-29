# Mytholang Compiler (Flex + Bison)

A compiler for **Mytholang**, a custom programming language with mythology-themed keywords. Built using **Flex** (Lexical Analysis) and **Bison** (Syntax Analysis) with a tree-walking interpreter backend.

The compiler reads Mytholang source code from `input_mytho.txt`, performs lexical analysis, syntax analysis, optimization, intermediate code generation, and execution — writing results to three separate output files.

---

## Compiler Phases

| Phase                        | Description                                               | Output File            |
| ---------------------------- | --------------------------------------------------------- | ---------------------- |
| Lexical Analysis             | Tokenizes source code using Flex                          | _(internal)_           |
| Syntax Analysis              | Parses tokens into AST using Bison                        | _(internal)_           |
| Semantic Analysis            | Type checking, implicit type conversion, scope resolution | Errors in `output.txt` |
| Constant Folding             | Optimizes compile-time constant expressions               | `opt_output.txt`       |
| Intermediate Code Generation | Generates Three-Address Code (TAC)                        | `tac_output.txt`       |
| Execution                    | Tree-walking interpreter executes the AST                 | `output.txt`           |

---

## Features

### Lexical Analysis (Flex)

The lexer recognizes all Mytholang tokens including keywords, operators, literals, identifiers, and reports invalid tokens with line numbers.

**Data Types:**

| Mytholang   | Standard |
| ----------- | -------- |
| `zeus`      | int      |
| `apollo`    | float    |
| `hera`      | double   |
| `titan`     | long     |
| `charizard` | char     |
| `truth`     | bool     |
| `Abyss`     | void     |

**Control Statements:**

| Mytholang   | Standard |
| ----------- | -------- |
| `omen`      | if       |
| `fate`      | else if  |
| `destiny`   | else     |
| `cycle`     | for      |
| `eternal`   | while    |
| `invoke`    | do while |
| `judgement` | switch   |
| `verdict`   | case     |
| `otherwise` | default  |
| `halt`      | break    |
| `persist`   | continue |
| `back`      | return   |

**Operators:**

| Mytholang | Standard    |
| --------- | ----------- |
| `add`     | +           |
| `minus`   | -           |
| `forge`   | \*          |
| `divide`  | /           |
| `rem`     | %           |
| `AND`     | &&          |
| `OR`      | \|\|        |
| `NOT`     | !           |
| `XOR`     | ^           |
| `:=`      | assignment  |
| `:->`     | return type |

**Relational Operators:** `<` `>` `<=` `>=` `=` `=!`

**I/O Functions:**

| Mytholang    | Standard |
| ------------ | -------- |
| `proclaim()` | print    |
| `listen()`   | input    |

**Other:** Comments with `//myth`, string literals, char literals, bool literals (`true`/`false`).

### Syntax Analysis (Bison)

The parser supports a full grammar including:

- `Prometheus()` main function
- Variable declarations with optional initialization
- Variable assignments
- Arithmetic, relational, and logical expressions with operator precedence
- Print statements using `proclaim()`
- Conditional statements: `omen`/`fate`/`destiny` (if/else if/else)
- Loops: `eternal` (while), `cycle` (for), `invoke` (do-while)
- `halt` (break) and `persist` (continue)
- User-defined functions with `ritual`, parameters, and return types
- Function calls (including recursive calls)
- `back` (return) statements

### Semantic Analysis

- **Symbol Table** with scope support (global + function-local scopes)
- **Type Checking** on assignments, arithmetic, relational, and logical operations
- **Implicit Type Conversion**: int → float → double (automatic promotion)
- **Duplicate declaration detection** within the same scope
- **Undeclared variable detection**
- **Function argument count validation**

### Constant Folding Optimization

The compiler performs constant folding before code generation and execution. Compile-time constant expressions are evaluated at compile time and replaced with their results.

**What gets folded:**

- Integer arithmetic: `3 add 5` → `8`
- Float arithmetic: `2.5 forge 4.0` → `10.0`
- Relational comparisons: `3 < 5` → `true`
- Logical operations: `true AND false` → `false`
- Unary NOT: `NOT true` → `false`

**Output:** `opt_output.txt` logs each folding operation performed.

### Intermediate Code Generation (Three-Address Code)

The compiler generates TAC from the optimized AST, producing human-readable intermediate code with:

- Temporary variables (`t0`, `t1`, `t2`, ...)
- Labels for control flow (`L0`, `L1`, ...)
- `ifFalse`/`ifTrue` conditional jumps
- `goto` unconditional jumps
- `param`/`call` for function invocations
- `return` statements
- `declare`, `print`, `break`, `continue` instructions

**Output:** `tac_output.txt` contains the complete TAC listing.

### Execution

The tree-walking interpreter executes the AST and writes program output to `output.txt`.

---

## Project Structure

```
MythoLang/
│
├── mytho.l              # Flex lexer definition
├── mytho.y              # Bison parser grammar + compiler backend
├── mytho_shared.h       # Shared type definitions and AST structures
├── Makefile             # Build configuration
│
├── input_mytho.txt      # Source code input
├── output.txt           # Execution output
├── tac_output.txt       # Three-Address Code output
├── opt_output.txt       # Optimization log output
│
├── lex.yy.c             # Generated by Flex
├── mytho.tab.c          # Generated by Bison
├── mytho.tab.h          # Generated header
│
└── mytho.exe            # Compiled executable
```

---

## Example Mytholang Programs

### Example 1: Variables and Loops

```
Prometheus() {
    zeus a := 0 .
    eternal(a < 3) {
        proclaim(a) .
        a := a add 1 .
    }
}
```

**output.txt:**

```
0
1
2

Parsing Successful
```

### Example 2: Functions with Recursion

```
ritual factorial(zeus n) :-> zeus {
    omen(n <= 1) {
        back 1 .
    }
    back n forge factorial(n minus 1) .
}

Prometheus() {
    zeus result := factorial(5) .
    proclaim(result) .
}
```

**output.txt:**

```
120

Parsing Successful
```

### Example 3: Constant Folding

```
Prometheus() {
    zeus x := 3 add 5 .
    zeus y := 10 forge 2 .
    proclaim(x) .
    proclaim(y) .
}
```

**opt_output.txt:**

```
=== Constant Folding Optimization ===

[OPT] Constant fold: 3 add 5 -> 8
[OPT] Constant fold: 10 mul 2 -> 20

Optimization Complete.
```

**tac_output.txt:**

```
=== Three-Address Code (TAC) ===

function Prometheus (main):
    declare int x
    x = 8
    declare int y
    y = 20
    print x
    print y
    endfunction
```

**output.txt:**

```
8
20

Parsing Successful
```

### Example 4: If/Else and For Loop

```
ritual square(zeus n) :-> zeus {
    back n forge n .
}

Prometheus() {
    zeus total := 0 .
    zeus i := 1 .
    cycle(i := 1 : i <= 4 : i := i add 1) {
        total := total add square(i) .
    }
    proclaim(total) .
}
```

**output.txt:**

```
30

Parsing Successful
```

---

## Installation

### Requirements

- Flex
- Bison
- GCC

### Ubuntu / WSL

```bash
sudo apt update
sudo apt install flex bison gcc
```

### Windows

Use WSL (Ubuntu) or MSYS2.

---

## Build & Run

### Build

```bash
make clean
make
```

Or manually:

```bash
bison -d mytho.y
flex mytho.l
gcc -Wall -Wno-unused-function lex.yy.c mytho.tab.c -o mytho.exe -lfl -lm
```

### Run

1. Place your Mytholang program in `input_mytho.txt`
2. Run:

```bash
make run
```

Or:

```bash
./mytho.exe
```

3. Check the output files:

| File             | Contents                                         |
| ---------------- | ------------------------------------------------ |
| `output.txt`     | Program execution output + "Parsing Successful"  |
| `tac_output.txt` | Three-Address Code (intermediate representation) |
| `opt_output.txt` | Constant folding optimization log                |

---

## Implementation Status

| Compiler Phase                                         | Status       |
| ------------------------------------------------------ | ------------ |
| Lexical Analysis                                       | ✅ Completed |
| Syntax Analysis                                        | ✅ Completed |
| Semantic Analysis (Type Checking, Implicit Conversion) | ✅ Completed |
| Symbol Table (Scope-aware)                             | ✅ Completed |
| Variable Declaration & Assignment                      | ✅ Completed |
| Expression Evaluation                                  | ✅ Completed |
| Conditional Statements (if/else if/else)               | ✅ Completed |
| Loops (while, for, do-while)                           | ✅ Completed |
| Break / Continue                                       | ✅ Completed |
| Functions (definition, calls, recursion)               | ✅ Completed |
| Return Statements                                      | ✅ Completed |
| Constant Folding Optimization                          | ✅ Completed |
| Intermediate Code Generation (TAC)                     | ✅ Completed |

---

## Author

Nirob — Compiler Design Project
