/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_MYTHO_TAB_H_INCLUDED
# define YY_YY_MYTHO_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    KEYWORD_INT = 258,             /* KEYWORD_INT  */
    KEYWORD_FLOAT = 259,           /* KEYWORD_FLOAT  */
    KEYWORD_DOUBLE = 260,          /* KEYWORD_DOUBLE  */
    KEYWORD_LONG = 261,            /* KEYWORD_LONG  */
    KEYWORD_CHAR = 262,            /* KEYWORD_CHAR  */
    KEYWORD_BOOL = 263,            /* KEYWORD_BOOL  */
    KEYWORD_VOID = 264,            /* KEYWORD_VOID  */
    IF = 265,                      /* IF  */
    ELSE_IF = 266,                 /* ELSE_IF  */
    ELSE = 267,                    /* ELSE  */
    FOR = 268,                     /* FOR  */
    WHILE = 269,                   /* WHILE  */
    DO = 270,                      /* DO  */
    SWITCH = 271,                  /* SWITCH  */
    CASE = 272,                    /* CASE  */
    DEFAULT = 273,                 /* DEFAULT  */
    BREAK = 274,                   /* BREAK  */
    CONTINUE = 275,                /* CONTINUE  */
    RETURN = 276,                  /* RETURN  */
    FUNCTION = 277,                /* FUNCTION  */
    MAIN = 278,                    /* MAIN  */
    PRINT = 279,                   /* PRINT  */
    INPUT = 280,                   /* INPUT  */
    ASSIGN = 281,                  /* ASSIGN  */
    RETTYPE = 282,                 /* RETTYPE  */
    OP_ADD = 283,                  /* OP_ADD  */
    OP_SUB = 284,                  /* OP_SUB  */
    OP_MUL = 285,                  /* OP_MUL  */
    OP_DIV = 286,                  /* OP_DIV  */
    OP_MOD = 287,                  /* OP_MOD  */
    OP_AND = 288,                  /* OP_AND  */
    OP_OR = 289,                   /* OP_OR  */
    OP_NOT = 290,                  /* OP_NOT  */
    OP_XOR = 291,                  /* OP_XOR  */
    OP_POW = 292,                  /* OP_POW  */
    OP_LT = 293,                   /* OP_LT  */
    OP_GT = 294,                   /* OP_GT  */
    OP_LE = 295,                   /* OP_LE  */
    OP_GE = 296,                   /* OP_GE  */
    OP_EQ = 297,                   /* OP_EQ  */
    OP_NE = 298,                   /* OP_NE  */
    ROOT = 299,                    /* ROOT  */
    FLOOR_FN = 300,                /* FLOOR_FN  */
    CEIL_FN = 301,                 /* CEIL_FN  */
    ABS_FN = 302,                  /* ABS_FN  */
    LOG_FN = 303,                  /* LOG_FN  */
    SIN_FN = 304,                  /* SIN_FN  */
    COS_FN = 305,                  /* COS_FN  */
    TAN_FN = 306,                  /* TAN_FN  */
    ASIN_FN = 307,                 /* ASIN_FN  */
    ACOS_FN = 308,                 /* ACOS_FN  */
    ATAN_FN = 309,                 /* ATAN_FN  */
    AMBROSIA_FN = 310,             /* AMBROSIA_FN  */
    LPAREN = 311,                  /* LPAREN  */
    RPAREN = 312,                  /* RPAREN  */
    LBRACE = 313,                  /* LBRACE  */
    RBRACE = 314,                  /* RBRACE  */
    DOT = 315,                     /* DOT  */
    COLON = 316,                   /* COLON  */
    COMMA = 317,                   /* COMMA  */
    INVALID = 318,                 /* INVALID  */
    INT_LITERAL = 319,             /* INT_LITERAL  */
    BOOL_LITERAL = 320,            /* BOOL_LITERAL  */
    FLOAT_LITERAL = 321,           /* FLOAT_LITERAL  */
    CHAR_LITERAL = 322,            /* CHAR_LITERAL  */
    IDENTIFIER = 323,              /* IDENTIFIER  */
    STRING_LITERAL = 324           /* STRING_LITERAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 40 "mytho.y"

    int ival;
    double fval;
    char cval;
    char* sval;
    DataType dtype;
    ExprValue expr;

#line 142 "mytho.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MYTHO_TAB_H_INCLUDED  */
