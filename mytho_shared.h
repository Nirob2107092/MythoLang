#ifndef MYTHO_SHARED_H
#define MYTHO_SHARED_H

typedef enum
{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_BOOL,
    TYPE_INVALID
} DataType;

typedef union
{
    int iVal;
    float fVal;
    double dVal;
    char cVal;
    int bVal;
} Value;

typedef struct
{
    DataType type;
    Value val;
} ExprValue;

/* forward declarations */
typedef struct ExprNode ExprNode;
typedef struct StmtNode StmtNode;

/* Expression AST */

typedef enum
{
    EXPR_LITERAL,
    EXPR_IDENTIFIER,
    EXPR_BINARY,
    EXPR_UNARY
} ExprKind;

struct ExprNode
{
    ExprKind kind;
    DataType type;

    char op[16];

    Value literal;
    char *name;

    ExprNode *left;
    ExprNode *right;
};

/* Statement AST */

typedef enum
{
    STMT_DECL,
    STMT_ASSIGN,
    STMT_PRINT,
    STMT_IF,
    STMT_WHILE,
    STMT_FOR,
    STMT_DO_WHILE,
    STMT_BREAK,
    STMT_CONTINUE
} StmtKind;

struct StmtNode
{
    StmtKind kind;

    char *name;
    DataType declaredType;

    ExprNode *expr;
    ExprNode *condition;

    StmtNode *initStmt;
    StmtNode *updateStmt;

    StmtNode *body;
    StmtNode *thenBlock;
    StmtNode *elseBlock;

    StmtNode *next;
};

typedef enum
{
    EXEC_NORMAL,
    EXEC_BREAK,
    EXEC_CONTINUE
} ExecStatus;

typedef struct
{
    ExecStatus status;
} ExecResult;

#endif