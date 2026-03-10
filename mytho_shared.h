#ifndef MYTHO_SHARED_H
#define MYTHO_SHARED_H

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_BOOL,
    TYPE_INVALID
} DataType;

typedef union {
    int iVal;
    float fVal;
    double dVal;
    char cVal;
    int bVal;
} Value;

typedef struct {
    DataType type;
    Value val;
} ExprValue;

#endif