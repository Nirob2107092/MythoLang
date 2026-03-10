%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SYMBOLS 100

typedef struct {
    char name[50];
    char type[20];
    int value;
} Symbol;

Symbol symbolTable[MAX_SYMBOLS];
int symbolCount = 0;
int yylex(void);
void yyerror(const char *s);

extern int yylineno;
extern FILE *yyin;
FILE *outputFile;

void insertSymbol(char *name, char *type);
void updateSymbol(char *name, int value);
int getSymbolValue(char *name);
int lookupSymbol(char *name);
%}

%union {
    int ival;
    double fval;
    char cval;
    char* sval;
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

/* precedence */
%left OP_ADD OP_SUB
%left OP_MUL OP_DIV OP_MOD
%right OP_POW

/* expression value types */
%type <ival> expression
%type <sval> type_spec

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
          fprintf(outputFile, "%d\n", $3);
      }
;

type_spec
    : KEYWORD_INT      { $$ = "int"; }
    | KEYWORD_FLOAT    { $$ = "float"; }
    | KEYWORD_DOUBLE   { $$ = "double"; }
    | KEYWORD_LONG     { $$ = "long"; }
    | KEYWORD_CHAR     { $$ = "char"; }
    | KEYWORD_BOOL     { $$ = "bool"; }
;

expression
    : expression OP_ADD expression   { $$ = $1 + $3; }
    | expression OP_SUB expression   { $$ = $1 - $3; }
    | expression OP_MUL expression   { $$ = $1 * $3; }
    | expression OP_DIV expression   { 
                                        if ($3 == 0) {
                                            yyerror("division by zero");
                                            $$ = 0;
                                        } else {
                                            $$ = $1 / $3;
                                        }
                                      }
    | expression OP_MOD expression   { $$ = $1 % $3; }
    | LPAREN expression RPAREN       { $$ = $2; }
    | INT_LITERAL                    { $$ = $1; }
    | IDENTIFIER { $$ = getSymbolValue($1); } 
    ;

%%

void insertSymbol(char *name, char *type) {
    for(int i = 0; i < symbolCount; i++) {
        if(strcmp(symbolTable[i].name, name) == 0) {
            fprintf(outputFile, "Semantic Error: Variable '%s' already declared\n", name);
            exit(1);
        }
    }

    strcpy(symbolTable[symbolCount].name, name);
    strcpy(symbolTable[symbolCount].type, type);
    symbolTable[symbolCount].value = 0;
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
void updateSymbol(char *name, int value) {

    int index = lookupSymbol(name);

    if(index == -1) {
        fprintf(outputFile,
        "Semantic Error: Variable '%s' not declared\n", name);
        exit(1);
    }

    symbolTable[index].value = value;
}
int getSymbolValue(char *name) {

    int index = lookupSymbol(name);

    if(index == -1) {
        fprintf(outputFile,
        "Semantic Error: Variable '%s' not declared\n", name);
        exit(1);
    }

    return symbolTable[index].value;
}

void yyerror(const char *s) {
    fprintf(outputFile, "Syntax Error at line %d\n", yylineno);
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
        return 1;
    }

    yyparse();

    fclose(yyin);
    fclose(outputFile);

    return 0;
}