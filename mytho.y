%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mytho_shared.h"

#define MAX_SYMBOLS 100



typedef struct {
    char name[50];
    DataType type;
    Value val;
} Symbol;

Symbol symbolTable[MAX_SYMBOLS];
int symbolCount = 0;

int yylex(void);
void yyerror(const char *s);

extern int yylineno;
extern FILE *yyin;
FILE *outputFile;

/* function prototypes */
void insertSymbol(char *name, DataType type);
int lookupSymbol(char *name);
void updateSymbol(char *name, ExprValue expr);
ExprValue getSymbolValue(char *name);
int isAssignable(DataType target, DataType source);
ExprValue evaluateArithmetic(ExprValue a, ExprValue b, int op);
const char* typeToString(DataType t);
ExprValue evaluateRelational(ExprValue a, ExprValue b, int op);
ExprValue evaluateLogical(ExprValue a, ExprValue b, int op);
ExprValue evaluateNot(ExprValue a);
%}

%union {
    int ival;
    double fval;
    char cval;
    char* sval;
    DataType dtype;
    ExprValue expr;
}

/* tokens from lexer */
%token KEYWORD_INT KEYWORD_FLOAT KEYWORD_DOUBLE KEYWORD_LONG KEYWORD_CHAR KEYWORD_BOOL KEYWORD_VOID
%token IF ELSE_IF ELSE FOR WHILE DO SWITCH CASE DEFAULT BREAK CONTINUE RETURN
%token FUNCTION MAIN PRINT INPUT
%token ASSIGN RETTYPE
%token OP_ADD OP_SUB OP_MUL OP_DIV OP_MOD
%token OP_AND OP_OR OP_NOT OP_XOR OP_POW
%token OP_LT OP_GT OP_LE OP_GE OP_EQ OP_NE
%token ROOT FLOOR_FN CEIL_FN ABS_FN LOG_FN SIN_FN COS_FN TAN_FN
%token ASIN_FN ACOS_FN ATAN_FN AMBROSIA_FN
%token LPAREN RPAREN LBRACE RBRACE DOT COLON COMMA
%token INVALID

%token <ival> INT_LITERAL BOOL_LITERAL
%token <fval> FLOAT_LITERAL
%token <cval> CHAR_LITERAL
%token <sval> IDENTIFIER STRING_LITERAL


%left OP_OR
%left OP_AND
%right OP_NOT
%left OP_EQ OP_NE OP_LT OP_GT OP_LE OP_GE
%left OP_ADD OP_SUB
%left OP_MUL OP_DIV OP_MOD
%right OP_POW

%type <expr> expression
%type <dtype> type_spec

%%

program
    : main_function
      {
          fprintf(outputFile, "Parsing Successful\n");
      }
    ;

main_function
    : MAIN LPAREN RPAREN LBRACE statement_list RBRACE
    ;

statement_list
    : statement_list statement
    | /* empty */
    ;

statement
    : declaration DOT
    | assignment DOT
    | print_stmt DOT
    ;

declaration
    : type_spec IDENTIFIER
      {
          insertSymbol($2, $1);
      }
    | type_spec IDENTIFIER ASSIGN expression
      {
          insertSymbol($2, $1);
          updateSymbol($2, $4);
      }
    ;

assignment
    : IDENTIFIER ASSIGN expression
      {
          updateSymbol($1, $3);
      }
    ;

print_stmt
    : PRINT LPAREN expression RPAREN
      {
          if ($3.type == TYPE_INT)
              fprintf(outputFile, "%d\n", $3.val.iVal);
          else if ($3.type == TYPE_FLOAT)
              fprintf(outputFile, "%f\n", $3.val.fVal);
          else if ($3.type == TYPE_DOUBLE)
              fprintf(outputFile, "%lf\n", $3.val.dVal);
          else if ($3.type == TYPE_CHAR)
              fprintf(outputFile, "%c\n", $3.val.cVal);
          else if ($3.type == TYPE_BOOL)
              fprintf(outputFile, "%s\n", $3.val.bVal ? "true" : "false");
      }
    ;

type_spec
    : KEYWORD_INT      { $$ = TYPE_INT; }
    | KEYWORD_FLOAT    { $$ = TYPE_FLOAT; }
    | KEYWORD_DOUBLE   { $$ = TYPE_DOUBLE; }
    | KEYWORD_LONG     { $$ = TYPE_INT; }   /* simplified for now */
    | KEYWORD_CHAR     { $$ = TYPE_CHAR; }
    | KEYWORD_BOOL     { $$ = TYPE_BOOL; }
    ;

expression
    : expression OP_ADD expression   { $$ = evaluateArithmetic($1, $3, 1); }
    | expression OP_SUB expression   { $$ = evaluateArithmetic($1, $3, 2); }
    | expression OP_MUL expression   { $$ = evaluateArithmetic($1, $3, 3); }
    | expression OP_DIV expression   { $$ = evaluateArithmetic($1, $3, 4); }

    | expression OP_MOD expression   {
                                        if ($1.type != TYPE_INT || $3.type != TYPE_INT) {
                                            fprintf(outputFile, "Type Error: modulus only allowed for int\n");
                                            exit(1);
                                        }
                                        $$.type = TYPE_INT;
                                        $$.val.iVal = $1.val.iVal % $3.val.iVal;
                                      }

    /* relational */
    | expression OP_LT expression    { $$ = evaluateRelational($1, $3, 1); }
    | expression OP_GT expression    { $$ = evaluateRelational($1, $3, 2); }
    | expression OP_LE expression    { $$ = evaluateRelational($1, $3, 3); }
    | expression OP_GE expression    { $$ = evaluateRelational($1, $3, 4); }
    | expression OP_EQ expression    { $$ = evaluateRelational($1, $3, 5); }
    | expression OP_NE expression    { $$ = evaluateRelational($1, $3, 6); }

    /* logical */
    | expression OP_AND expression   { $$ = evaluateLogical($1, $3, 1); }
    | expression OP_OR expression    { $$ = evaluateLogical($1, $3, 2); }
    | OP_NOT expression              { $$ = evaluateNot($2); }

    | LPAREN expression RPAREN       { $$ = $2; }

    | INT_LITERAL                    {
                                        $$.type = TYPE_INT;
                                        $$.val.iVal = $1;
                                      }
    | FLOAT_LITERAL                  {
                                        $$.type = TYPE_DOUBLE;
                                        $$.val.dVal = $1;
                                      }
    | CHAR_LITERAL                   {
                                        $$.type = TYPE_CHAR;
                                        $$.val.cVal = $1;
                                      }
    | BOOL_LITERAL                   {
                                        $$.type = TYPE_BOOL;
                                        $$.val.bVal = $1;
                                      }
    | IDENTIFIER                     {
                                        $$ = getSymbolValue($1);
                                      }
    ;
%%

const char* typeToString(DataType t) {
    switch(t) {
        case TYPE_INT: return "int";
        case TYPE_FLOAT: return "float";
        case TYPE_DOUBLE: return "double";
        case TYPE_CHAR: return "char";
        case TYPE_BOOL: return "bool";
        default: return "invalid";
    }
}

void insertSymbol(char *name, DataType type) {
    for(int i = 0; i < symbolCount; i++) {
        if(strcmp(symbolTable[i].name, name) == 0) {
            fprintf(outputFile, "Semantic Error: Variable '%s' already declared\n", name);
            exit(1);
        }
    }

    strcpy(symbolTable[symbolCount].name, name);
    symbolTable[symbolCount].type = type;

    /* default initialize */
    if (type == TYPE_INT) symbolTable[symbolCount].val.iVal = 0;
    else if (type == TYPE_FLOAT) symbolTable[symbolCount].val.fVal = 0.0f;
    else if (type == TYPE_DOUBLE) symbolTable[symbolCount].val.dVal = 0.0;
    else if (type == TYPE_CHAR) symbolTable[symbolCount].val.cVal = '\0';
    else if (type == TYPE_BOOL) symbolTable[symbolCount].val.bVal = 0;

    symbolCount++;
}

int lookupSymbol(char *name) {
    for(int i = 0; i < symbolCount; i++) {
        if(strcmp(symbolTable[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int isAssignable(DataType target, DataType source) {
    if (target == source) return 1;

    /* widening conversions */
    if (target == TYPE_FLOAT && source == TYPE_INT) return 1;
    if (target == TYPE_DOUBLE && source == TYPE_INT) return 1;
    if (target == TYPE_DOUBLE && source == TYPE_FLOAT) return 1;

    return 0;
}

void updateSymbol(char *name, ExprValue expr) {
    int index = lookupSymbol(name);

    if(index == -1) {
        fprintf(outputFile, "Semantic Error: Variable '%s' not declared\n", name);
        exit(1);
    }

    DataType target = symbolTable[index].type;
    DataType source = expr.type;

    if (!isAssignable(target, source)) {
        fprintf(outputFile, "Type Error: cannot assign %s to %s variable '%s'\n",
                typeToString(source), typeToString(target), name);
        exit(1);
    }

    if (target == TYPE_INT) {
        symbolTable[index].val.iVal = expr.val.iVal;
    }
    else if (target == TYPE_FLOAT) {
        if (source == TYPE_INT)
            symbolTable[index].val.fVal = (float)expr.val.iVal;
        else
            symbolTable[index].val.fVal = expr.val.fVal;
    }
    else if (target == TYPE_DOUBLE) {
        if (source == TYPE_INT)
            symbolTable[index].val.dVal = (double)expr.val.iVal;
        else if (source == TYPE_FLOAT)
            symbolTable[index].val.dVal = (double)expr.val.fVal;
        else
            symbolTable[index].val.dVal = expr.val.dVal;
    }
    else if (target == TYPE_CHAR) {
        symbolTable[index].val.cVal = expr.val.cVal;
    }
    else if (target == TYPE_BOOL) {
        symbolTable[index].val.bVal = expr.val.bVal;
    }
}

ExprValue getSymbolValue(char *name) {
    int index = lookupSymbol(name);
    ExprValue result;

    if(index == -1) {
        fprintf(outputFile, "Semantic Error: Variable '%s' not declared\n", name);
        exit(1);
    }

    result.type = symbolTable[index].type;
    result.val = symbolTable[index].val;
    return result;
}

ExprValue evaluateArithmetic(ExprValue a, ExprValue b, int op) {
    ExprValue result;

    /* char and bool arithmetic not allowed for now */
    if (a.type == TYPE_CHAR || a.type == TYPE_BOOL ||
        b.type == TYPE_CHAR || b.type == TYPE_BOOL) {
        fprintf(outputFile, "Type Error: invalid arithmetic operation\n");
        exit(1);
    }

    /* promote to double if either is double */
    if (a.type == TYPE_DOUBLE || b.type == TYPE_DOUBLE) {
        double x = (a.type == TYPE_DOUBLE) ? a.val.dVal :
                   (a.type == TYPE_FLOAT)  ? a.val.fVal :
                                             a.val.iVal;

        double y = (b.type == TYPE_DOUBLE) ? b.val.dVal :
                   (b.type == TYPE_FLOAT)  ? b.val.fVal :
                                             b.val.iVal;

        result.type = TYPE_DOUBLE;

        if (op == 1) result.val.dVal = x + y;
        else if (op == 2) result.val.dVal = x - y;
        else if (op == 3) result.val.dVal = x * y;
        else if (op == 4) {
            if (y == 0) {
                yyerror("division by zero");
                result.val.dVal = 0;
            } else {
                result.val.dVal = x / y;
            }
        }
    }
    /* promote to float if either is float */
    else if (a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        float x = (a.type == TYPE_FLOAT) ? a.val.fVal : a.val.iVal;
        float y = (b.type == TYPE_FLOAT) ? b.val.fVal : b.val.iVal;

        result.type = TYPE_FLOAT;

        if (op == 1) result.val.fVal = x + y;
        else if (op == 2) result.val.fVal = x - y;
        else if (op == 3) result.val.fVal = x * y;
        else if (op == 4) {
            if (y == 0) {
                yyerror("division by zero");
                result.val.fVal = 0;
            } else {
                result.val.fVal = x / y;
            }
        }
    }
    /* otherwise int */
    else {
        int x = a.val.iVal;
        int y = b.val.iVal;

        result.type = TYPE_INT;

        if (op == 1) result.val.iVal = x + y;
        else if (op == 2) result.val.iVal = x - y;
        else if (op == 3) result.val.iVal = x * y;
        else if (op == 4) {
            if (y == 0) {
                yyerror("division by zero");
                result.val.iVal = 0;
            } else {
                result.val.iVal = x / y;
            }
        }
    }

    return result;
}
ExprValue evaluateRelational(ExprValue a, ExprValue b, int op) {
    ExprValue result;
    result.type = TYPE_BOOL;

    /* equality / inequality for bool allowed */
    if ((a.type == TYPE_BOOL || b.type == TYPE_BOOL)) {
        if (a.type != TYPE_BOOL || b.type != TYPE_BOOL) {
            fprintf(outputFile, "Type Error: cannot compare bool with non-bool\n");
            exit(1);
        }

        if (op == 5) result.val.bVal = (a.val.bVal == b.val.bVal);
        else if (op == 6) result.val.bVal = (a.val.bVal != b.val.bVal);
        else {
            fprintf(outputFile, "Type Error: invalid relational operation on bool\n");
            exit(1);
        }

        return result;
    }

    /* char comparisons allowed */
    if (a.type == TYPE_CHAR && b.type == TYPE_CHAR) {
        char x = a.val.cVal;
        char y = b.val.cVal;

        if (op == 1) result.val.bVal = (x < y);
        else if (op == 2) result.val.bVal = (x > y);
        else if (op == 3) result.val.bVal = (x <= y);
        else if (op == 4) result.val.bVal = (x >= y);
        else if (op == 5) result.val.bVal = (x == y);
        else if (op == 6) result.val.bVal = (x != y);

        return result;
    }

    /* char with non-char not allowed */
    if (a.type == TYPE_CHAR || b.type == TYPE_CHAR) {
        fprintf(outputFile, "Type Error: cannot compare char with non-char\n");
        exit(1);
    }

    /* numeric comparisons */
    double x = (a.type == TYPE_DOUBLE) ? a.val.dVal :
               (a.type == TYPE_FLOAT)  ? a.val.fVal :
                                         a.val.iVal;

    double y = (b.type == TYPE_DOUBLE) ? b.val.dVal :
               (b.type == TYPE_FLOAT)  ? b.val.fVal :
                                         b.val.iVal;

    if (op == 1) result.val.bVal = (x < y);
    else if (op == 2) result.val.bVal = (x > y);
    else if (op == 3) result.val.bVal = (x <= y);
    else if (op == 4) result.val.bVal = (x >= y);
    else if (op == 5) result.val.bVal = (x == y);
    else if (op == 6) result.val.bVal = (x != y);

    return result;
}
ExprValue evaluateLogical(ExprValue a, ExprValue b, int op) {
    ExprValue result;
    result.type = TYPE_BOOL;

    if (a.type != TYPE_BOOL || b.type != TYPE_BOOL) {
        fprintf(outputFile, "Type Error: logical operators require bool operands\n");
        exit(1);
    }

    if (op == 1) result.val.bVal = a.val.bVal && b.val.bVal;   /* AND */
    else if (op == 2) result.val.bVal = a.val.bVal || b.val.bVal; /* OR */

    return result;
}
ExprValue evaluateNot(ExprValue a) {
    ExprValue result;
    result.type = TYPE_BOOL;

    if (a.type != TYPE_BOOL) {
        fprintf(outputFile, "Type Error: NOT operator requires bool operand\n");
        exit(1);
    }

    result.val.bVal = !a.val.bVal;
    return result;
}

void yyerror(const char *s) {
    fprintf(outputFile, "Syntax Error at line %d: %s\n", yylineno, s);
}

int main(void) {
    yyin = fopen("input_mytho.txt", "r");
    if (!yyin) {
        perror("input_mytho.txt");
        return 1;
    }

    outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        perror("output.txt");
        fclose(yyin);
        return 1;
    }

    yyparse();

    fclose(yyin);
    fclose(outputFile);

    return 0;
}