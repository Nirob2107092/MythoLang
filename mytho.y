%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mytho_shared.h"

#define MAX_SYMBOLS 100
Function functionTable[MAX_FUNCTIONS];
int functionCount = 0;

typedef struct {
    char name[50];
    DataType type;
    Value val;
} Symbol;

#define MAX_SCOPES 20
typedef struct {
    Symbol symbols[MAX_SYMBOLS];
    int count;
} Scope;

Scope scopeStack[MAX_SCOPES];
int scopeTop = 0;

int yylex(void);
void yyerror(const char *s);

extern int yylineno;
extern FILE *yyin;
FILE *outputFile;   /* execution output     -> output.txt     */
FILE *tacFile;      /* intermediate code    -> tac_output.txt  */
FILE *optFile;      /* optimization log     -> opt_output.txt  */

void pushScope(void);
void popScope(void);
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
StmtNode *programRoot = NULL;

ExprNode* makeIntLiteralNode(int v);
ExprNode* makeFloatLiteralNode(double v);
ExprNode* makeCharLiteralNode(char v);
ExprNode* makeBoolLiteralNode(int v);
ExprNode* makeIdentifierNode(char *name);
ExprNode* makeBinaryExprNode(const char *op, ExprNode *left, ExprNode *right);
ExprNode* makeUnaryExprNode(const char *op, ExprNode *expr);

StmtNode* makeDeclNode(DataType type, char *name, ExprNode *expr);
StmtNode* makeAssignNode(char *name, ExprNode *expr);
StmtNode* makePrintNode(ExprNode *expr);
StmtNode* makeIfNode(ExprNode *cond, StmtNode *thenBlock, StmtNode *elseBlock);
StmtNode* makeWhileNode(ExprNode *cond, StmtNode *body);
StmtNode* makeForNode(StmtNode *initStmt, ExprNode *cond, StmtNode *updateStmt, StmtNode *body);
StmtNode* makeDoWhileNode(StmtNode *body, ExprNode *cond);
StmtNode* makeBreakNode(void);
StmtNode* makeContinueNode(void);
StmtNode* appendStatement(StmtNode *list, StmtNode *stmt);

ExprValue evalExprNode(ExprNode *expr);
ExecResult execStmt(StmtNode *stmt);
ExecResult execBlock(StmtNode *block);

void registerFunction(char *name, DataType returnType, char paramNames[][50], DataType paramTypes[], int paramCount, StmtNode *body);
Function* lookupFunction(char *name);
ExprValue callFunction(char *name, ExprNode *args);

ExprNode* appendArgument(ExprNode *list, ExprNode *arg);
StmtNode* makeReturnNode(ExprNode *expr);
ExprNode* makeFunctionCallNode(char *name, ExprNode *args);

int tacTempCount = 0;
int tacLabelCount = 0;
char* newTemp(void);
char* newLabel(void);
char* generateTACExpr(ExprNode *expr);
void generateTACStmt(StmtNode *stmt);
void generateTACBlock(StmtNode *block);

ExprNode* constantFold(ExprNode *expr);
StmtNode* optimizeStmt(StmtNode *stmt);
StmtNode* optimizeBlock(StmtNode *block);

char tempParamNames[MAX_PARAMS][50];
DataType tempParamTypes[MAX_PARAMS];
int tempParamCount = 0;
%}

%union {
    int ival;
    double fval;
    char cval;
    char* sval;
    DataType dtype;
    ExprNode* exprNode;
    StmtNode* stmtNode;
}

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

%type <stmtNode> function_def
%type <stmtNode> function_list
%type <exprNode> arg_list
%type <exprNode> arg_list_nonempty
%type <exprNode> expression
%type <stmtNode> statement
%type <stmtNode> statement_list
%type <stmtNode> declaration
%type <stmtNode> assignment
%type <stmtNode> print_stmt
%type <stmtNode> if_stmt
%type <stmtNode> while_stmt
%type <stmtNode> for_stmt
%type <stmtNode> do_while_stmt
%type <stmtNode> else_part
%type <stmtNode> else_if_list
%type <dtype> type_spec
%type <stmtNode> main_function

%%

program
    : function_list main_function
      {
          programRoot = $2;
      }
    ;
function_list
    : function_list function_def
      {
          $$ = NULL;
      }
    | /* empty */
      {
          $$ = NULL;
      }
    ;

main_function
    : MAIN LPAREN RPAREN LBRACE statement_list RBRACE
      {
          $$ = $5;
      }
    ;

function_def
    : FUNCTION IDENTIFIER LPAREN
      {
          tempParamCount = 0;
      }
      param_list RPAREN RETTYPE type_spec LBRACE statement_list RBRACE
      {
          registerFunction($2, $8, tempParamNames, tempParamTypes, tempParamCount, $10);
          $$ = NULL;
      }
    ;

param_list
    : param_list COMMA param
    | param
    | /* empty */
    ;
param
    : type_spec IDENTIFIER
      {
          if (tempParamCount >= MAX_PARAMS) {
              fprintf(outputFile, "Semantic Error: too many parameters\n");
              exit(1);
          }
          strcpy(tempParamNames[tempParamCount], $2);
          tempParamTypes[tempParamCount] = $1;
          tempParamCount++;
      }
    ;

statement_list
    : statement_list statement
      {
          $$ = appendStatement($1, $2);
      }
    | /* empty */
      {
          $$ = NULL;
      }
    ;

statement
    : declaration DOT      { $$ = $1; }
    | assignment DOT       { $$ = $1; }
    | print_stmt DOT       { $$ = $1; }
    | if_stmt              { $$ = $1; }
    | while_stmt           { $$ = $1; }
    | for_stmt             { $$ = $1; }
    | do_while_stmt        { $$ = $1; }
    | BREAK DOT            { $$ = makeBreakNode(); }
    | CONTINUE DOT         { $$ = makeContinueNode(); }
    | RETURN expression DOT { $$ = makeReturnNode($2); }
    ;

declaration
    : type_spec IDENTIFIER
      {
          $$ = makeDeclNode($1, $2, NULL);
      }
    | type_spec IDENTIFIER ASSIGN expression
      {
          $$ = makeDeclNode($1, $2, $4);
      }
    ;

assignment
    : IDENTIFIER ASSIGN expression
      {
          $$ = makeAssignNode($1, $3);
      }
    ;

print_stmt
    : PRINT LPAREN expression RPAREN
      {
          $$ = makePrintNode($3);
      }
    ;

if_stmt
    : IF LPAREN expression RPAREN LBRACE statement_list RBRACE else_if_list else_part
      {
          StmtNode *elseChain = $8;
          if (elseChain == NULL)
              elseChain = $9;
          else {
              StmtNode *tail = elseChain;
              while (tail->elseBlock != NULL)
                  tail = tail->elseBlock;
              tail->elseBlock = $9;
          }
          $$ = makeIfNode($3, $6, elseChain);
      }
    ;
else_if_list
    : else_if_list ELSE_IF LPAREN expression RPAREN LBRACE statement_list RBRACE
      {
          StmtNode *node = makeIfNode($4, $7, NULL);
          if ($1 == NULL) $$ = node;
          else {
              StmtNode *tail = $1;
              while (tail->elseBlock != NULL)
                  tail = tail->elseBlock;
              tail->elseBlock = node;
              $$ = $1;
          }
      }
    | /* empty */
      {
          $$ = NULL;
      }
    ;

else_part
    : ELSE LBRACE statement_list RBRACE
      {
          $$ = $3;
      }
    | /* empty */
      {
          $$ = NULL;
      }
    ;

while_stmt
    : WHILE LPAREN expression RPAREN LBRACE statement_list RBRACE
      {
          $$ = makeWhileNode($3, $6);
      }
    ;

for_stmt
    : FOR LPAREN assignment COLON expression COLON assignment RPAREN LBRACE statement_list RBRACE
      {
          $$ = makeForNode($3, $5, $7, $10);
      }
    ;

do_while_stmt
    : DO LBRACE statement_list RBRACE WHILE LPAREN expression RPAREN DOT
      {
          $$ = makeDoWhileNode($3, $7);
      }
    ;

type_spec
    : KEYWORD_INT      { $$ = TYPE_INT; }
    | KEYWORD_FLOAT    { $$ = TYPE_FLOAT; }
    | KEYWORD_DOUBLE   { $$ = TYPE_DOUBLE; }
    | KEYWORD_LONG     { $$ = TYPE_INT; }
    | KEYWORD_CHAR     { $$ = TYPE_CHAR; }
    | KEYWORD_BOOL     { $$ = TYPE_BOOL; }
    ;

expression
    : expression OP_ADD expression   { $$ = makeBinaryExprNode("add", $1, $3); }
    | expression OP_SUB expression   { $$ = makeBinaryExprNode("sub", $1, $3); }
    | expression OP_MUL expression   { $$ = makeBinaryExprNode("mul", $1, $3); }
    | expression OP_DIV expression   { $$ = makeBinaryExprNode("div", $1, $3); }
    | expression OP_MOD expression   { $$ = makeBinaryExprNode("mod", $1, $3); }
    | expression OP_LT expression    { $$ = makeBinaryExprNode("lt", $1, $3); }
    | expression OP_GT expression    { $$ = makeBinaryExprNode("gt", $1, $3); }
    | expression OP_LE expression    { $$ = makeBinaryExprNode("le", $1, $3); }
    | expression OP_GE expression    { $$ = makeBinaryExprNode("ge", $1, $3); }
    | expression OP_EQ expression    { $$ = makeBinaryExprNode("eq", $1, $3); }
    | expression OP_NE expression    { $$ = makeBinaryExprNode("ne", $1, $3); }
    | expression OP_AND expression   { $$ = makeBinaryExprNode("and", $1, $3); }
    | expression OP_OR expression    { $$ = makeBinaryExprNode("or", $1, $3); }
    | OP_NOT expression              { $$ = makeUnaryExprNode("not", $2); }
    | LPAREN expression RPAREN       { $$ = $2; }
    | INT_LITERAL                    { $$ = makeIntLiteralNode($1); }
    | FLOAT_LITERAL                  { $$ = makeFloatLiteralNode($1); }
    | CHAR_LITERAL                   { $$ = makeCharLiteralNode($1); }
    | BOOL_LITERAL                   { $$ = makeBoolLiteralNode($1); }
    | IDENTIFIER                     { $$ = makeIdentifierNode($1); }
    | IDENTIFIER LPAREN arg_list RPAREN   { $$ = makeFunctionCallNode($1, $3); }
    ;

arg_list
    : arg_list_nonempty { $$ = $1; }
    | /* empty */       { $$ = NULL; }
    ;

arg_list_nonempty
    : arg_list_nonempty COMMA expression
      {
          $$ = appendArgument($1, $3);
      }
    | expression
      {
          $$ = $1;
      }
    ;

%%

/* ================================================================
   AST CONSTRUCTORS
   ================================================================ */

ExprNode* makeIntLiteralNode(int v) {
    ExprNode *node = malloc(sizeof(ExprNode));
    node->kind = EXPR_LITERAL; node->type = TYPE_INT;
    node->literal.iVal = v; node->name = NULL;
    node->left = node->right = NULL;
    node->args = node->next = NULL; node->op[0] = '\0';
    return node;
}

ExprNode* makeFloatLiteralNode(double v) {
    ExprNode *node = malloc(sizeof(ExprNode));
    node->kind = EXPR_LITERAL; node->type = TYPE_FLOAT;
    node->literal.dVal = v; node->name = NULL;
    node->left = node->right = NULL;
    node->args = node->next = NULL; node->op[0] = '\0';
    return node;
}

ExprNode* makeCharLiteralNode(char v) {
    ExprNode *node = malloc(sizeof(ExprNode));
    node->kind = EXPR_LITERAL; node->type = TYPE_CHAR;
    node->literal.cVal = v; node->name = NULL;
    node->left = node->right = NULL;
    node->args = node->next = NULL; node->op[0] = '\0';
    return node;
}

ExprNode* makeBoolLiteralNode(int v) {
    ExprNode *node = malloc(sizeof(ExprNode));
    node->kind = EXPR_LITERAL; node->type = TYPE_BOOL;
    node->literal.bVal = v; node->name = NULL;
    node->left = node->right = NULL;
    node->args = node->next = NULL; node->op[0] = '\0';
    return node;
}

ExprNode* makeIdentifierNode(char *name) {
    ExprNode *node = malloc(sizeof(ExprNode));
    node->kind = EXPR_IDENTIFIER; node->type = TYPE_INVALID;
    node->name = strdup(name);
    node->left = node->right = NULL;
    node->args = node->next = NULL; node->op[0] = '\0';
    return node;
}

ExprNode* makeBinaryExprNode(const char *op, ExprNode *left, ExprNode *right) {
    ExprNode *node = malloc(sizeof(ExprNode));
    node->kind = EXPR_BINARY; node->type = TYPE_INVALID;
    strcpy(node->op, op);
    node->left = left; node->right = right;
    node->name = NULL; node->args = node->next = NULL;
    return node;
}

ExprNode* makeUnaryExprNode(const char *op, ExprNode *expr) {
    ExprNode *node = malloc(sizeof(ExprNode));
    node->kind = EXPR_UNARY; node->type = TYPE_INVALID;
    strcpy(node->op, op);
    node->left = expr; node->right = NULL;
    node->name = NULL; node->args = node->next = NULL;
    return node;
}

ExprNode* makeFunctionCallNode(char *name, ExprNode *args) {
    ExprNode *node = malloc(sizeof(ExprNode));
    node->kind = EXPR_FUNC_CALL; node->type = TYPE_INVALID;
    node->name = strdup(name); node->args = args;
    node->left = node->right = NULL;
    node->next = NULL; node->op[0] = '\0';
    return node;
}

ExprNode* appendArgument(ExprNode *list, ExprNode *arg) {
    if (list == NULL) return arg;
    ExprNode *cur = list;
    while (cur->next != NULL) cur = cur->next;
    cur->next = arg;
    return list;
}

StmtNode* makeDeclNode(DataType type, char *name, ExprNode *expr) {
    StmtNode *node = malloc(sizeof(StmtNode));
    node->kind = STMT_DECL; node->declaredType = type;
    node->name = strdup(name); node->expr = expr;
    node->condition = NULL;
    node->initStmt = node->updateStmt = NULL;
    node->body = node->thenBlock = node->elseBlock = NULL;
    node->next = NULL;
    return node;
}

StmtNode* makeAssignNode(char *name, ExprNode *expr) {
    StmtNode *node = malloc(sizeof(StmtNode));
    node->kind = STMT_ASSIGN; node->name = strdup(name);
    node->expr = expr; node->condition = NULL;
    node->initStmt = node->updateStmt = NULL;
    node->body = node->thenBlock = node->elseBlock = NULL;
    node->next = NULL;
    return node;
}

StmtNode* makePrintNode(ExprNode *expr) {
    StmtNode *node = malloc(sizeof(StmtNode));
    node->kind = STMT_PRINT; node->expr = expr;
    node->name = NULL; node->condition = NULL;
    node->initStmt = node->updateStmt = NULL;
    node->body = node->thenBlock = node->elseBlock = NULL;
    node->next = NULL;
    return node;
}

StmtNode* makeIfNode(ExprNode *cond, StmtNode *thenBlock, StmtNode *elseBlock) {
    StmtNode *node = malloc(sizeof(StmtNode));
    node->kind = STMT_IF; node->condition = cond;
    node->thenBlock = thenBlock; node->elseBlock = elseBlock;
    node->name = NULL; node->expr = NULL;
    node->initStmt = node->updateStmt = NULL;
    node->body = NULL; node->next = NULL;
    return node;
}

StmtNode* makeWhileNode(ExprNode *cond, StmtNode *body) {
    StmtNode *node = malloc(sizeof(StmtNode));
    node->kind = STMT_WHILE; node->condition = cond;
    node->body = body; node->name = NULL; node->expr = NULL;
    node->initStmt = node->updateStmt = NULL;
    node->thenBlock = node->elseBlock = NULL;
    node->next = NULL;
    return node;
}

StmtNode* makeForNode(StmtNode *initStmt, ExprNode *cond, StmtNode *updateStmt, StmtNode *body) {
    StmtNode *node = malloc(sizeof(StmtNode));
    node->kind = STMT_FOR; node->initStmt = initStmt;
    node->condition = cond; node->updateStmt = updateStmt;
    node->body = body; node->name = NULL; node->expr = NULL;
    node->thenBlock = node->elseBlock = NULL;
    node->next = NULL;
    return node;
}

StmtNode* makeDoWhileNode(StmtNode *body, ExprNode *cond) {
    StmtNode *node = malloc(sizeof(StmtNode));
    node->kind = STMT_DO_WHILE; node->body = body;
    node->condition = cond; node->name = NULL; node->expr = NULL;
    node->initStmt = node->updateStmt = NULL;
    node->thenBlock = node->elseBlock = NULL;
    node->next = NULL;
    return node;
}

StmtNode* makeBreakNode(void) {
    StmtNode *node = malloc(sizeof(StmtNode));
    node->kind = STMT_BREAK; node->name = NULL; node->expr = NULL;
    node->condition = NULL; node->initStmt = node->updateStmt = NULL;
    node->body = node->thenBlock = node->elseBlock = NULL;
    node->next = NULL;
    return node;
}

StmtNode* makeContinueNode(void) {
    StmtNode *node = malloc(sizeof(StmtNode));
    node->kind = STMT_CONTINUE; node->name = NULL; node->expr = NULL;
    node->condition = NULL; node->initStmt = node->updateStmt = NULL;
    node->body = node->thenBlock = node->elseBlock = NULL;
    node->next = NULL;
    return node;
}

StmtNode* makeReturnNode(ExprNode *expr) {
    StmtNode *node = malloc(sizeof(StmtNode));
    node->kind = STMT_RETURN; node->expr = expr;
    node->name = NULL; node->condition = NULL;
    node->initStmt = node->updateStmt = NULL;
    node->body = node->thenBlock = node->elseBlock = NULL;
    node->next = NULL;
    return node;
}

StmtNode* appendStatement(StmtNode *list, StmtNode *stmt) {
    if (list == NULL) return stmt;
    StmtNode *cur = list;
    while (cur->next != NULL) cur = cur->next;
    cur->next = stmt;
    return list;
}

/* ================================================================
   SYMBOL TABLE (scope-aware)
   ================================================================ */

void pushScope(void) {
    scopeTop++;
    if (scopeTop >= MAX_SCOPES) {
        fprintf(outputFile, "Error: scope nesting too deep\n");
        exit(1);
    }
    scopeStack[scopeTop].count = 0;
}

void popScope(void) {
    if (scopeTop <= 0) {
        fprintf(outputFile, "Error: cannot pop global scope\n");
        exit(1);
    }
    scopeTop--;
}

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
    Scope *sc = &scopeStack[scopeTop];
    for(int i = 0; i < sc->count; i++) {
        if(strcmp(sc->symbols[i].name, name) == 0) {
            fprintf(outputFile, "Semantic Error: Variable '%s' already declared in this scope\n", name);
            exit(1);
        }
    }
    strcpy(sc->symbols[sc->count].name, name);
    sc->symbols[sc->count].type = type;
    if (type == TYPE_INT) sc->symbols[sc->count].val.iVal = 0;
    else if (type == TYPE_FLOAT) sc->symbols[sc->count].val.fVal = 0.0f;
    else if (type == TYPE_DOUBLE) sc->symbols[sc->count].val.dVal = 0.0;
    else if (type == TYPE_CHAR) sc->symbols[sc->count].val.cVal = '\0';
    else if (type == TYPE_BOOL) sc->symbols[sc->count].val.bVal = 0;
    sc->count++;
}

int lookupSymbol(char *name) {
    for (int s = scopeTop; s >= 0; s--) {
        for (int i = 0; i < scopeStack[s].count; i++) {
            if (strcmp(scopeStack[s].symbols[i].name, name) == 0)
                return (s * MAX_SYMBOLS) + i;
        }
    }
    return -1;
}

int isAssignable(DataType target, DataType source) {
    if (target == source) return 1;
    if (target == TYPE_FLOAT && source == TYPE_INT) return 1;
    if (target == TYPE_DOUBLE && source == TYPE_INT) return 1;
    if (target == TYPE_DOUBLE && source == TYPE_FLOAT) return 1;
    return 0;
}

void updateSymbol(char *name, ExprValue expr) {
    int encoded = lookupSymbol(name);
    if(encoded == -1) {
        fprintf(outputFile, "Semantic Error: Variable '%s' not declared\n", name);
        exit(1);
    }
    int s = encoded / MAX_SYMBOLS;
    int i = encoded % MAX_SYMBOLS;
    Symbol *sym = &scopeStack[s].symbols[i];
    DataType target = sym->type;
    DataType source = expr.type;
    if (!isAssignable(target, source)) {
        fprintf(outputFile, "Type Error: cannot assign %s to %s variable '%s'\n",
                typeToString(source), typeToString(target), name);
        exit(1);
    }
    if (target == TYPE_INT) sym->val.iVal = expr.val.iVal;
    else if (target == TYPE_FLOAT) {
        if (source == TYPE_INT) sym->val.fVal = (float)expr.val.iVal;
        else sym->val.fVal = expr.val.fVal;
    }
    else if (target == TYPE_DOUBLE) {
        if (source == TYPE_INT) sym->val.dVal = (double)expr.val.iVal;
        else if (source == TYPE_FLOAT) sym->val.dVal = (double)expr.val.fVal;
        else sym->val.dVal = expr.val.dVal;
    }
    else if (target == TYPE_CHAR) sym->val.cVal = expr.val.cVal;
    else if (target == TYPE_BOOL) sym->val.bVal = expr.val.bVal;
}

ExprValue getSymbolValue(char *name) {
    int encoded = lookupSymbol(name);
    ExprValue result;
    if(encoded == -1) {
        fprintf(outputFile, "Semantic Error: Variable '%s' not declared\n", name);
        exit(1);
    }
    int s = encoded / MAX_SYMBOLS;
    int i = encoded % MAX_SYMBOLS;
    Symbol *sym = &scopeStack[s].symbols[i];
    result.type = sym->type;
    result.val = sym->val;
    return result;
}

/* ================================================================
   FUNCTION TABLE
   ================================================================ */

void registerFunction(char *name, DataType returnType,
                      char paramNames[][50], DataType paramTypes[],
                      int paramCount, StmtNode *body) {
    if (functionCount >= MAX_FUNCTIONS) {
        fprintf(outputFile, "Error: too many functions\n");
        exit(1);
    }
    Function *f = &functionTable[functionCount++];
    strncpy(f->name, name, 49);
    f->returnType = returnType;
    f->paramCount = paramCount;
    f->body = body;
    for (int i = 0; i < paramCount; i++) {
        strncpy(f->paramNames[i], paramNames[i], 49);
        f->paramTypes[i] = paramTypes[i];
    }
}

Function* lookupFunction(char *name) {
    for (int i = 0; i < functionCount; i++) {
        if (strcmp(functionTable[i].name, name) == 0)
            return &functionTable[i];
    }
    return NULL;
}

ExprValue callFunction(char *name, ExprNode *args) {
    Function *f = lookupFunction(name);
    if (f == NULL) {
        fprintf(outputFile, "Semantic Error: function '%s' not defined\n", name);
        exit(1);
    }
    ExprValue argVals[MAX_PARAMS];
    int argCount = 0;
    ExprNode *cur = args;
    while (cur != NULL) {
        if (argCount >= MAX_PARAMS) {
            fprintf(outputFile, "Semantic Error: too many arguments to '%s'\n", name);
            exit(1);
        }
        argVals[argCount++] = evalExprNode(cur);
        cur = cur->next;
    }
    if (argCount != f->paramCount) {
        fprintf(outputFile, "Semantic Error: function '%s' expects %d args, got %d\n",
                name, f->paramCount, argCount);
        exit(1);
    }
    pushScope();
    for (int i = 0; i < f->paramCount; i++) {
        insertSymbol(f->paramNames[i], f->paramTypes[i]);
        updateSymbol(f->paramNames[i], argVals[i]);
    }
    ExecResult res = execBlock(f->body);
    popScope();
    if (res.status == EXEC_RETURN) return res.returnValue;
    ExprValue defaultVal;
    defaultVal.type = f->returnType;
    if (f->returnType == TYPE_INT) defaultVal.val.iVal = 0;
    else if (f->returnType == TYPE_FLOAT) defaultVal.val.fVal = 0.0f;
    else if (f->returnType == TYPE_DOUBLE) defaultVal.val.dVal = 0.0;
    else if (f->returnType == TYPE_BOOL) defaultVal.val.bVal = 0;
    return defaultVal;
}

/* ================================================================
   ARITHMETIC / RELATIONAL / LOGICAL EVALUATORS
   ================================================================ */

ExprValue evaluateArithmetic(ExprValue a, ExprValue b, int op) {
    ExprValue result;
    if (a.type == TYPE_CHAR || a.type == TYPE_BOOL ||
        b.type == TYPE_CHAR || b.type == TYPE_BOOL) {
        fprintf(outputFile, "Type Error: invalid arithmetic operation\n");
        exit(1);
    }
    if (a.type == TYPE_DOUBLE || b.type == TYPE_DOUBLE) {
        double x = (a.type == TYPE_DOUBLE) ? a.val.dVal :
                   (a.type == TYPE_FLOAT)  ? a.val.fVal : a.val.iVal;
        double y = (b.type == TYPE_DOUBLE) ? b.val.dVal :
                   (b.type == TYPE_FLOAT)  ? b.val.fVal : b.val.iVal;
        result.type = TYPE_DOUBLE;
        if (op == 1) result.val.dVal = x + y;
        else if (op == 2) result.val.dVal = x - y;
        else if (op == 3) result.val.dVal = x * y;
        else if (op == 4) {
            if (y == 0) { yyerror("division by zero"); result.val.dVal = 0; }
            else result.val.dVal = x / y;
        }
    }
    else if (a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        float x = (a.type == TYPE_FLOAT) ? a.val.fVal : a.val.iVal;
        float y = (b.type == TYPE_FLOAT) ? b.val.fVal : b.val.iVal;
        result.type = TYPE_FLOAT;
        if (op == 1) result.val.fVal = x + y;
        else if (op == 2) result.val.fVal = x - y;
        else if (op == 3) result.val.fVal = x * y;
        else if (op == 4) {
            if (y == 0) { yyerror("division by zero"); result.val.fVal = 0; }
            else result.val.fVal = x / y;
        }
    }
    else {
        int x = a.val.iVal; int y = b.val.iVal;
        result.type = TYPE_INT;
        if (op == 1) result.val.iVal = x + y;
        else if (op == 2) result.val.iVal = x - y;
        else if (op == 3) result.val.iVal = x * y;
        else if (op == 4) {
            if (y == 0) { yyerror("division by zero"); result.val.iVal = 0; }
            else result.val.iVal = x / y;
        }
    }
    return result;
}

ExprValue evaluateRelational(ExprValue a, ExprValue b, int op) {
    ExprValue result;
    result.type = TYPE_BOOL;
    if ((a.type == TYPE_BOOL || b.type == TYPE_BOOL)) {
        if (a.type != TYPE_BOOL || b.type != TYPE_BOOL) {
            fprintf(outputFile, "Type Error: cannot compare bool with non-bool\n");
            exit(1);
        }
        if (op == 5) result.val.bVal = (a.val.bVal == b.val.bVal);
        else if (op == 6) result.val.bVal = (a.val.bVal != b.val.bVal);
        else { fprintf(outputFile, "Type Error: invalid relational operation on bool\n"); exit(1); }
        return result;
    }
    if (a.type == TYPE_CHAR && b.type == TYPE_CHAR) {
        char x = a.val.cVal; char y = b.val.cVal;
        if (op == 1) result.val.bVal = (x < y);
        else if (op == 2) result.val.bVal = (x > y);
        else if (op == 3) result.val.bVal = (x <= y);
        else if (op == 4) result.val.bVal = (x >= y);
        else if (op == 5) result.val.bVal = (x == y);
        else if (op == 6) result.val.bVal = (x != y);
        return result;
    }
    if (a.type == TYPE_CHAR || b.type == TYPE_CHAR) {
        fprintf(outputFile, "Type Error: cannot compare char with non-char\n");
        exit(1);
    }
    double x = (a.type == TYPE_DOUBLE) ? a.val.dVal :
               (a.type == TYPE_FLOAT)  ? a.val.fVal : a.val.iVal;
    double y = (b.type == TYPE_DOUBLE) ? b.val.dVal :
               (b.type == TYPE_FLOAT)  ? b.val.fVal : b.val.iVal;
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
    if (op == 1) result.val.bVal = a.val.bVal && b.val.bVal;
    else if (op == 2) result.val.bVal = a.val.bVal || b.val.bVal;
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

/* ================================================================
   AST EVALUATOR (tree-walking interpreter)
   ================================================================ */

ExprValue evalExprNode(ExprNode *expr) {
    ExprValue left, right;

    if (expr->kind == EXPR_LITERAL) {
        ExprValue result;
        result.type = expr->type;
        result.val = expr->literal;
        return result;
    }
    if (expr->kind == EXPR_IDENTIFIER)
        return getSymbolValue(expr->name);

    if (expr->kind == EXPR_FUNC_CALL)
        return callFunction(expr->name, expr->args);

    if (expr->kind == EXPR_UNARY) {
        left = evalExprNode(expr->left);
        if (strcmp(expr->op, "not") == 0)
            return evaluateNot(left);
    }
    if (expr->kind == EXPR_BINARY) {
        left = evalExprNode(expr->left);
        right = evalExprNode(expr->right);
        if (strcmp(expr->op, "add") == 0) return evaluateArithmetic(left, right, 1);
        if (strcmp(expr->op, "sub") == 0) return evaluateArithmetic(left, right, 2);
        if (strcmp(expr->op, "mul") == 0) return evaluateArithmetic(left, right, 3);
        if (strcmp(expr->op, "div") == 0) return evaluateArithmetic(left, right, 4);
        if (strcmp(expr->op, "mod") == 0) {
            ExprValue result;
            if (left.type != TYPE_INT || right.type != TYPE_INT) {
                fprintf(outputFile, "Type Error: modulus only allowed for int\n"); exit(1);
            }
            result.type = TYPE_INT;
            result.val.iVal = left.val.iVal % right.val.iVal;
            return result;
        }
        if (strcmp(expr->op, "lt") == 0) return evaluateRelational(left, right, 1);
        if (strcmp(expr->op, "gt") == 0) return evaluateRelational(left, right, 2);
        if (strcmp(expr->op, "le") == 0) return evaluateRelational(left, right, 3);
        if (strcmp(expr->op, "ge") == 0) return evaluateRelational(left, right, 4);
        if (strcmp(expr->op, "eq") == 0) return evaluateRelational(left, right, 5);
        if (strcmp(expr->op, "ne") == 0) return evaluateRelational(left, right, 6);
        if (strcmp(expr->op, "and") == 0) return evaluateLogical(left, right, 1);
        if (strcmp(expr->op, "or") == 0) return evaluateLogical(left, right, 2);
    }
    fprintf(outputFile, "Runtime Error: invalid expression\n");
    exit(1);
}

ExecResult execStmt(StmtNode *stmt) {
    ExecResult result;
    result.status = EXEC_NORMAL;
    if (stmt == NULL) return result;

    switch (stmt->kind) {
        case STMT_DECL: {
            insertSymbol(stmt->name, stmt->declaredType);
            if (stmt->expr != NULL) {
                ExprValue val = evalExprNode(stmt->expr);
                updateSymbol(stmt->name, val);
            }
            break;
        }
        case STMT_ASSIGN: {
            ExprValue val = evalExprNode(stmt->expr);
            updateSymbol(stmt->name, val);
            break;
        }
        case STMT_PRINT: {
            ExprValue val = evalExprNode(stmt->expr);
            if (val.type == TYPE_INT) fprintf(outputFile, "%d\n", val.val.iVal);
            else if (val.type == TYPE_FLOAT) fprintf(outputFile, "%f\n", val.val.fVal);
            else if (val.type == TYPE_DOUBLE) fprintf(outputFile, "%lf\n", val.val.dVal);
            else if (val.type == TYPE_CHAR) fprintf(outputFile, "%c\n", val.val.cVal);
            else if (val.type == TYPE_BOOL) fprintf(outputFile, "%s\n", val.val.bVal ? "true" : "false");
            break;
        }
        case STMT_IF: {
            ExprValue cond = evalExprNode(stmt->condition);
            if (cond.type != TYPE_BOOL) {
                fprintf(outputFile, "Type Error: if condition must be boolean\n"); exit(1);
            }
            if (cond.val.bVal) return execBlock(stmt->thenBlock);
            else if (stmt->elseBlock != NULL) return execBlock(stmt->elseBlock);
            break;
        }
        case STMT_WHILE: {
            while (1) {
                ExprValue cond = evalExprNode(stmt->condition);
                if (cond.type != TYPE_BOOL) {
                    fprintf(outputFile, "Type Error: while condition must be boolean\n"); exit(1);
                }
                if (!cond.val.bVal) break;
                result = execBlock(stmt->body);
                if (result.status == EXEC_BREAK) { result.status = EXEC_NORMAL; break; }
                if (result.status == EXEC_CONTINUE) { result.status = EXEC_NORMAL; continue; }
                if (result.status == EXEC_RETURN) return result;
            }
            break;
        }
        case STMT_FOR: {
            if (stmt->initStmt) execStmt(stmt->initStmt);
            while (1) {
                ExprValue cond = evalExprNode(stmt->condition);
                if (cond.type != TYPE_BOOL) {
                    fprintf(outputFile, "Type Error: for condition must be boolean\n"); exit(1);
                }
                if (!cond.val.bVal) break;
                result = execBlock(stmt->body);
                if (result.status == EXEC_BREAK) { result.status = EXEC_NORMAL; break; }
                if (stmt->updateStmt) execStmt(stmt->updateStmt);
                if (result.status == EXEC_CONTINUE) { result.status = EXEC_NORMAL; continue; }
                if (result.status == EXEC_RETURN) return result;
            }
            break;
        }
        case STMT_DO_WHILE: {
            do {
                result = execBlock(stmt->body);
                if (result.status == EXEC_BREAK) { result.status = EXEC_NORMAL; break; }
                ExprValue cond = evalExprNode(stmt->condition);
                if (cond.type != TYPE_BOOL) {
                    fprintf(outputFile, "Type Error: do-while condition must be boolean\n"); exit(1);
                }
                if (result.status == EXEC_CONTINUE) result.status = EXEC_NORMAL;
                if (result.status == EXEC_RETURN) return result;
                if (!cond.val.bVal) break;
            } while (1);
            break;
        }
        case STMT_BREAK:
            result.status = EXEC_BREAK; return result;
        case STMT_CONTINUE:
            result.status = EXEC_CONTINUE; return result;
        case STMT_RETURN: {
            result.status = EXEC_RETURN;
            if (stmt->expr != NULL)
                result.returnValue = evalExprNode(stmt->expr);
            return result;
        }
    }
    return result;
}

ExecResult execBlock(StmtNode *block) {
    ExecResult result;
    result.status = EXEC_NORMAL;
    StmtNode *cur = block;
    while (cur != NULL) {
        result = execStmt(cur);
        if (result.status != EXEC_NORMAL) return result;
        cur = cur->next;
    }
    return result;
}

/* ================================================================
   CONSTANT FOLDING OPTIMIZATION
   ================================================================ */

ExprNode* constantFold(ExprNode *expr) {
    if (expr == NULL) return NULL;
    if (expr->kind == EXPR_LITERAL || expr->kind == EXPR_IDENTIFIER)
        return expr;

    if (expr->kind == EXPR_FUNC_CALL) {
        ExprNode *arg = expr->args;
        while (arg != NULL) {
            ExprNode *folded = constantFold(arg);
            *arg = *folded;
            arg = arg->next;
        }
        return expr;
    }

    if (expr->left)  expr->left  = constantFold(expr->left);
    if (expr->right) expr->right = constantFold(expr->right);

    if (expr->kind == EXPR_UNARY && strcmp(expr->op, "not") == 0) {
        if (expr->left->kind == EXPR_LITERAL && expr->left->type == TYPE_BOOL) {
            fprintf(optFile, "[OPT] Constant fold: NOT %s -> %s\n",
                    expr->left->literal.bVal ? "true" : "false",
                    expr->left->literal.bVal ? "false" : "true");
            return makeBoolLiteralNode(!expr->left->literal.bVal);
        }
        return expr;
    }

    if (expr->kind == EXPR_BINARY) {
        if (expr->left->kind != EXPR_LITERAL || expr->right->kind != EXPR_LITERAL)
            return expr;

        ExprNode *L = expr->left;
        ExprNode *R = expr->right;

        if (L->type == TYPE_INT && R->type == TYPE_INT) {
            int a = L->literal.iVal, b = R->literal.iVal;
            int res, isArith = 1;
            if      (strcmp(expr->op, "add") == 0) res = a + b;
            else if (strcmp(expr->op, "sub") == 0) res = a - b;
            else if (strcmp(expr->op, "mul") == 0) res = a * b;
            else if (strcmp(expr->op, "div") == 0) { if (b == 0) return expr; res = a / b; }
            else if (strcmp(expr->op, "mod") == 0) { if (b == 0) return expr; res = a % b; }
            else isArith = 0;
            if (isArith) {
                fprintf(optFile, "[OPT] Constant fold: %d %s %d -> %d\n", a, expr->op, b, res);
                return makeIntLiteralNode(res);
            }
            int boolRes, isRel = 1;
            if      (strcmp(expr->op, "lt") == 0) boolRes = (a < b);
            else if (strcmp(expr->op, "gt") == 0) boolRes = (a > b);
            else if (strcmp(expr->op, "le") == 0) boolRes = (a <= b);
            else if (strcmp(expr->op, "ge") == 0) boolRes = (a >= b);
            else if (strcmp(expr->op, "eq") == 0) boolRes = (a == b);
            else if (strcmp(expr->op, "ne") == 0) boolRes = (a != b);
            else isRel = 0;
            if (isRel) {
                fprintf(optFile, "[OPT] Constant fold: %d %s %d -> %s\n", a, expr->op, b, boolRes ? "true" : "false");
                return makeBoolLiteralNode(boolRes);
            }
        }

        if ((L->type == TYPE_FLOAT || L->type == TYPE_INT) &&
            (R->type == TYPE_FLOAT || R->type == TYPE_INT) &&
            (L->type == TYPE_FLOAT || R->type == TYPE_FLOAT)) {
            double a = (L->type == TYPE_FLOAT) ? L->literal.dVal : (double)L->literal.iVal;
            double b = (R->type == TYPE_FLOAT) ? R->literal.dVal : (double)R->literal.iVal;
            double res; int isArith = 1;
            if      (strcmp(expr->op, "add") == 0) res = a + b;
            else if (strcmp(expr->op, "sub") == 0) res = a - b;
            else if (strcmp(expr->op, "mul") == 0) res = a * b;
            else if (strcmp(expr->op, "div") == 0) { if (b == 0.0) return expr; res = a / b; }
            else isArith = 0;
            if (isArith) {
                fprintf(optFile, "[OPT] Constant fold: %g %s %g -> %g\n", a, expr->op, b, res);
                return makeFloatLiteralNode(res);
            }
        }

        if (L->type == TYPE_BOOL && R->type == TYPE_BOOL) {
            int a = L->literal.bVal, b = R->literal.bVal;
            int res, isLog = 1;
            if      (strcmp(expr->op, "and") == 0) res = a && b;
            else if (strcmp(expr->op, "or")  == 0) res = a || b;
            else isLog = 0;
            if (isLog) {
                fprintf(optFile, "[OPT] Constant fold: %s %s %s -> %s\n",
                        a ? "true" : "false", expr->op, b ? "true" : "false", res ? "true" : "false");
                return makeBoolLiteralNode(res);
            }
        }
    }
    return expr;
}

StmtNode* optimizeStmt(StmtNode *stmt) {
    if (stmt == NULL) return NULL;
    if (stmt->expr)      stmt->expr      = constantFold(stmt->expr);
    if (stmt->condition)  stmt->condition  = constantFold(stmt->condition);
    if (stmt->initStmt)   stmt->initStmt   = optimizeStmt(stmt->initStmt);
    if (stmt->updateStmt) stmt->updateStmt = optimizeStmt(stmt->updateStmt);
    if (stmt->body)       stmt->body       = optimizeBlock(stmt->body);
    if (stmt->thenBlock)  stmt->thenBlock  = optimizeBlock(stmt->thenBlock);
    if (stmt->elseBlock)  stmt->elseBlock  = optimizeBlock(stmt->elseBlock);
    return stmt;
}

StmtNode* optimizeBlock(StmtNode *block) {
    StmtNode *cur = block;
    while (cur != NULL) { optimizeStmt(cur); cur = cur->next; }
    return block;
}

/* ================================================================
   THREE-ADDRESS CODE (TAC) GENERATION
   ================================================================ */

char* newTemp(void) {
    char *buf = malloc(16);
    sprintf(buf, "t%d", tacTempCount++);
    return buf;
}

char* newLabel(void) {
    char *buf = malloc(16);
    sprintf(buf, "L%d", tacLabelCount++);
    return buf;
}

const char* opToSymbol(const char *op) {
    if (strcmp(op, "add") == 0) return "+";
    if (strcmp(op, "sub") == 0) return "-";
    if (strcmp(op, "mul") == 0) return "*";
    if (strcmp(op, "div") == 0) return "/";
    if (strcmp(op, "mod") == 0) return "%%";
    if (strcmp(op, "lt")  == 0) return "<";
    if (strcmp(op, "gt")  == 0) return ">";
    if (strcmp(op, "le")  == 0) return "<=";
    if (strcmp(op, "ge")  == 0) return ">=";
    if (strcmp(op, "eq")  == 0) return "==";
    if (strcmp(op, "ne")  == 0) return "!=";
    if (strcmp(op, "and") == 0) return "&&";
    if (strcmp(op, "or")  == 0) return "||";
    if (strcmp(op, "not") == 0) return "!";
    return op;
}

char* generateTACExpr(ExprNode *expr) {
    if (expr == NULL) return strdup("0");
    if (expr->kind == EXPR_LITERAL) {
        char *buf = malloc(64);
        if (expr->type == TYPE_INT) sprintf(buf, "%d", expr->literal.iVal);
        else if (expr->type == TYPE_FLOAT) sprintf(buf, "%g", expr->literal.dVal);
        else if (expr->type == TYPE_CHAR) sprintf(buf, "'%c'", expr->literal.cVal);
        else if (expr->type == TYPE_BOOL) sprintf(buf, "%s", expr->literal.bVal ? "true" : "false");
        else sprintf(buf, "0");
        return buf;
    }
    if (expr->kind == EXPR_IDENTIFIER) return strdup(expr->name);
    if (expr->kind == EXPR_FUNC_CALL) {
        ExprNode *arg = expr->args;
        int argc = 0;
        char *argTemps[MAX_PARAMS];
        while (arg != NULL) {
            argTemps[argc] = generateTACExpr(arg);
            fprintf(tacFile, "    param %s\n", argTemps[argc]);
            argc++; arg = arg->next;
        }
        char *t = newTemp();
        fprintf(tacFile, "    %s = call %s, %d\n", t, expr->name, argc);
        for (int i = 0; i < argc; i++) free(argTemps[i]);
        return t;
    }
    if (expr->kind == EXPR_UNARY) {
        char *operand = generateTACExpr(expr->left);
        char *t = newTemp();
        fprintf(tacFile, "    %s = %s %s\n", t, opToSymbol(expr->op), operand);
        free(operand); return t;
    }
    if (expr->kind == EXPR_BINARY) {
        char *left  = generateTACExpr(expr->left);
        char *right = generateTACExpr(expr->right);
        char *t = newTemp();
        fprintf(tacFile, "    %s = %s %s %s\n", t, left, opToSymbol(expr->op), right);
        free(left); free(right); return t;
    }
    return strdup("???");
}

void generateTACStmt(StmtNode *stmt) {
    if (stmt == NULL) return;
    switch (stmt->kind) {
        case STMT_DECL: {
            fprintf(tacFile, "    declare %s %s\n", typeToString(stmt->declaredType), stmt->name);
            if (stmt->expr != NULL) {
                char *val = generateTACExpr(stmt->expr);
                fprintf(tacFile, "    %s = %s\n", stmt->name, val);
                free(val);
            }
            break;
        }
        case STMT_ASSIGN: {
            char *val = generateTACExpr(stmt->expr);
            fprintf(tacFile, "    %s = %s\n", stmt->name, val);
            free(val); break;
        }
        case STMT_PRINT: {
            char *val = generateTACExpr(stmt->expr);
            fprintf(tacFile, "    print %s\n", val);
            free(val); break;
        }
        case STMT_IF: {
            char *cond = generateTACExpr(stmt->condition);
            char *labelElse = newLabel();
            char *labelEnd  = newLabel();
            fprintf(tacFile, "    ifFalse %s goto %s\n", cond, labelElse);
            free(cond);
            generateTACBlock(stmt->thenBlock);
            fprintf(tacFile, "    goto %s\n", labelEnd);
            fprintf(tacFile, "%s:\n", labelElse);
            if (stmt->elseBlock != NULL) {
                if (stmt->elseBlock->kind == STMT_IF) generateTACStmt(stmt->elseBlock);
                else generateTACBlock(stmt->elseBlock);
            }
            fprintf(tacFile, "%s:\n", labelEnd);
            free(labelElse); free(labelEnd); break;
        }
        case STMT_WHILE: {
            char *labelStart = newLabel();
            char *labelEnd   = newLabel();
            fprintf(tacFile, "%s:\n", labelStart);
            char *cond = generateTACExpr(stmt->condition);
            fprintf(tacFile, "    ifFalse %s goto %s\n", cond, labelEnd);
            free(cond);
            generateTACBlock(stmt->body);
            fprintf(tacFile, "    goto %s\n", labelStart);
            fprintf(tacFile, "%s:\n", labelEnd);
            free(labelStart); free(labelEnd); break;
        }
        case STMT_FOR: {
            char *labelStart = newLabel();
            char *labelEnd   = newLabel();
            if (stmt->initStmt) generateTACStmt(stmt->initStmt);
            fprintf(tacFile, "%s:\n", labelStart);
            char *cond = generateTACExpr(stmt->condition);
            fprintf(tacFile, "    ifFalse %s goto %s\n", cond, labelEnd);
            free(cond);
            generateTACBlock(stmt->body);
            if (stmt->updateStmt) generateTACStmt(stmt->updateStmt);
            fprintf(tacFile, "    goto %s\n", labelStart);
            fprintf(tacFile, "%s:\n", labelEnd);
            free(labelStart); free(labelEnd); break;
        }
        case STMT_DO_WHILE: {
            char *labelStart = newLabel();
            fprintf(tacFile, "%s:\n", labelStart);
            generateTACBlock(stmt->body);
            char *cond = generateTACExpr(stmt->condition);
            fprintf(tacFile, "    ifTrue %s goto %s\n", cond, labelStart);
            free(cond); free(labelStart); break;
        }
        case STMT_BREAK:
            fprintf(tacFile, "    break\n"); break;
        case STMT_CONTINUE:
            fprintf(tacFile, "    continue\n"); break;
        case STMT_RETURN: {
            if (stmt->expr != NULL) {
                char *val = generateTACExpr(stmt->expr);
                fprintf(tacFile, "    return %s\n", val);
                free(val);
            } else fprintf(tacFile, "    return\n");
            break;
        }
    }
}

void generateTACBlock(StmtNode *block) {
    StmtNode *cur = block;
    while (cur != NULL) { generateTACStmt(cur); cur = cur->next; }
}

void generateTACFunctions(void) {
    for (int i = 0; i < functionCount; i++) {
        Function *f = &functionTable[i];
        fprintf(tacFile, "\nfunction %s:\n", f->name);
        for (int j = 0; j < f->paramCount; j++)
            fprintf(tacFile, "    param %s %s\n", typeToString(f->paramTypes[j]), f->paramNames[j]);
        generateTACBlock(f->body);
        fprintf(tacFile, "    endfunction\n");
    }
}

/* ================================================================
   ERROR HANDLER & MAIN
   ================================================================ */

void yyerror(const char *s) {
    fprintf(outputFile, "Syntax Error at line %d: %s\n", yylineno, s);
}

int main(void) {
    yyin = fopen("input_mytho.txt", "r");
    if (!yyin) { perror("input_mytho.txt"); return 1; }

    outputFile = fopen("output.txt", "w");
    if (!outputFile) { perror("output.txt"); fclose(yyin); return 1; }

    tacFile = fopen("tac_output.txt", "w");
    if (!tacFile) { perror("tac_output.txt"); fclose(yyin); fclose(outputFile); return 1; }

    optFile = fopen("opt_output.txt", "w");
    if (!optFile) { perror("opt_output.txt"); fclose(yyin); fclose(outputFile); fclose(tacFile); return 1; }

    scopeStack[0].count = 0;
    yyparse();

    if (programRoot != NULL) {
        /* Phase 1: Constant Folding Optimization -> opt_output.txt */
        fprintf(optFile, "=== Constant Folding Optimization ===\n\n");
        programRoot = optimizeBlock(programRoot);
        for (int i = 0; i < functionCount; i++)
            functionTable[i].body = optimizeBlock(functionTable[i].body);
        fprintf(optFile, "\nOptimization Complete.\n");

        /* Phase 2: Three-Address Code Generation -> tac_output.txt */
        fprintf(tacFile, "=== Three-Address Code (TAC) ===\n");
        generateTACFunctions();
        fprintf(tacFile, "\nfunction Prometheus (main):\n");
        generateTACBlock(programRoot);
        fprintf(tacFile, "    endfunction\n");

        /* Phase 3: Execution -> output.txt */
        execBlock(programRoot);
        fprintf(outputFile, "\nParsing Successful\n");
    }

    fclose(yyin);
    fclose(outputFile);
    fclose(tacFile);
    fclose(optFile);
    return 0;
}
