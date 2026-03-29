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
- **Duplicate function declaration detection**
- **Argument type mismatch checking** (validates each argument against parameter type)
- **Return type checking** (validates returned value matches declared return type)
- **Missing return detection** (errors on non-void functions without `back` statement)
- **Void function support** (`Abyss` keyword for void return type)

### Exponentiation

The `**` operator is supported for numeric exponentiation with right-associative precedence (higher than multiplication).

```
zeus x := 2 ** 3 .       //myth result: 8
apollo y := 2.0 ** 10.0 . //myth result: 1024.0
```

### Built-in Math Functions

| Mytholang      | C equivalent | Description                         |
| -------------- | ------------ | ----------------------------------- |
| `root(x)`      | `sqrt(x)`    | Square root                         |
| `abs(x)`       | `fabs(x)`    | Absolute value                      |
| `flr(x)`       | `floor(x)`   | Floor                               |
| `ceil(x)`      | `ceil(x)`    | Ceiling                             |
| `logarithm(x)` | `log(x)`     | Natural logarithm                   |
| `sine(x)`      | `sin(x)`     | Sine                                |
| `cosine(x)`    | `cos(x)`     | Cosine                              |
| `tan(x)`       | `tan(x)`     | Tangent                             |
| `asine(x)`     | `asin(x)`    | Arc sine                            |
| `acosine(x)`   | `acos(x)`    | Arc cosine                          |
| `atan(x)`      | `atan(x)`    | Arc tangent                         |
| `ambrosia(x)`  | _(custom)_   | Perfect number check (returns bool) |

All standard built-in functions accept numeric operands (int, float, double) and reject bool/char. Return type matches the operand type (except `abs` on int returns int).

`ambrosia(x)` is a **custom built-in boolean function** unique to Mytholang. It checks whether an integer is a **perfect number** — a number equal to the sum of its proper divisors (e.g. 6 = 1+2+3, 28 = 1+2+4+7+14). It requires an `int` operand and returns `truth` (bool).

### Input with listen()

The `listen()` function reads integer input from stdin at runtime.

```
zeus x := listen() .   //myth reads an integer from user
proclaim(x) .          //myth prints it
```

`listen()` returns `TYPE_INT`. The value can be assigned to float/double variables through implicit type conversion.

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

### Example 5: Exponentiation

```
Prometheus() {
    zeus x := 2 ** 3 .
    proclaim(x) .
}
```

**output.txt:**

```
8

Parsing Successful
```

### Example 6: Built-in Math Functions

```
Prometheus() {
    apollo a := root(25.0) .
    apollo b := abs(-4.0) .
    apollo c := ceil(2.3) .
    proclaim(a) .
    proclaim(b) .
    proclaim(c) .
}
```

**output.txt:**

```
5.000000
4.000000
3.000000

Parsing Successful
```

### Example 7: User Input with listen()

```
Prometheus() {
    zeus x := listen() .
    proclaim(x) .
}
```

If user types `7`:

**output.txt:**

```
7

Parsing Successful
```

### Example 8: Semantic Error Detection

```
ritual sum(zeus a, zeus b) :-> zeus {
    proclaim(a) .
}

Prometheus() {
    zeus z := sum(2, 3) .
}
```

**output.txt:**

```
2
Semantic Error: function 'sum' missing return statement
```

### Example 9: ambrosia() — Perfect Number Check

```
Prometheus() {
    truth a := ambrosia(6) .
    proclaim(a) .
    truth b := ambrosia(28) .
    proclaim(b) .
    truth c := ambrosia(12) .
    proclaim(c) .
}
```

**output.txt:**

```
true
true
false

Parsing Successful
```

6 is perfect (1+2+3=6), 28 is perfect (1+2+4+7+14=28), 12 is not (1+2+3+4+6=16≠12).

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
| Duplicate Function Declaration Check                   | ✅ Completed |
| Argument Type Mismatch Detection                       | ✅ Completed |
| Return Type Validation                                 | ✅ Completed |
| Missing Return Detection                               | ✅ Completed |
| Void Function Support (`Abyss`)                        | ✅ Completed |
| Exponentiation (`**`)                                  | ✅ Completed |
| Built-in Math Functions (root, abs, flr, ceil, etc.)   | ✅ Completed |
| Custom Function: ambrosia() (perfect number check)     | ✅ Completed |
| User Input (`listen()`)                                | ✅ Completed |
| Constant Folding Optimization                          | ✅ Completed |
| Intermediate Code Generation (TAC)                     | ✅ Completed |

---

## Author

Nirob — Compiler Design Project
