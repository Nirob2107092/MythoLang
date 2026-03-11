/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "mytho.y"

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
void ensureBooleanCondition(ExprValue expr, const char *context);

#line 109 "mytho.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "mytho.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_KEYWORD_INT = 3,                /* KEYWORD_INT  */
  YYSYMBOL_KEYWORD_FLOAT = 4,              /* KEYWORD_FLOAT  */
  YYSYMBOL_KEYWORD_DOUBLE = 5,             /* KEYWORD_DOUBLE  */
  YYSYMBOL_KEYWORD_LONG = 6,               /* KEYWORD_LONG  */
  YYSYMBOL_KEYWORD_CHAR = 7,               /* KEYWORD_CHAR  */
  YYSYMBOL_KEYWORD_BOOL = 8,               /* KEYWORD_BOOL  */
  YYSYMBOL_KEYWORD_VOID = 9,               /* KEYWORD_VOID  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_ELSE_IF = 11,                   /* ELSE_IF  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_FOR = 13,                       /* FOR  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_DO = 15,                        /* DO  */
  YYSYMBOL_SWITCH = 16,                    /* SWITCH  */
  YYSYMBOL_CASE = 17,                      /* CASE  */
  YYSYMBOL_DEFAULT = 18,                   /* DEFAULT  */
  YYSYMBOL_BREAK = 19,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 20,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 21,                    /* RETURN  */
  YYSYMBOL_FUNCTION = 22,                  /* FUNCTION  */
  YYSYMBOL_MAIN = 23,                      /* MAIN  */
  YYSYMBOL_PRINT = 24,                     /* PRINT  */
  YYSYMBOL_INPUT = 25,                     /* INPUT  */
  YYSYMBOL_ASSIGN = 26,                    /* ASSIGN  */
  YYSYMBOL_RETTYPE = 27,                   /* RETTYPE  */
  YYSYMBOL_OP_ADD = 28,                    /* OP_ADD  */
  YYSYMBOL_OP_SUB = 29,                    /* OP_SUB  */
  YYSYMBOL_OP_MUL = 30,                    /* OP_MUL  */
  YYSYMBOL_OP_DIV = 31,                    /* OP_DIV  */
  YYSYMBOL_OP_MOD = 32,                    /* OP_MOD  */
  YYSYMBOL_OP_AND = 33,                    /* OP_AND  */
  YYSYMBOL_OP_OR = 34,                     /* OP_OR  */
  YYSYMBOL_OP_NOT = 35,                    /* OP_NOT  */
  YYSYMBOL_OP_XOR = 36,                    /* OP_XOR  */
  YYSYMBOL_OP_POW = 37,                    /* OP_POW  */
  YYSYMBOL_OP_LT = 38,                     /* OP_LT  */
  YYSYMBOL_OP_GT = 39,                     /* OP_GT  */
  YYSYMBOL_OP_LE = 40,                     /* OP_LE  */
  YYSYMBOL_OP_GE = 41,                     /* OP_GE  */
  YYSYMBOL_OP_EQ = 42,                     /* OP_EQ  */
  YYSYMBOL_OP_NE = 43,                     /* OP_NE  */
  YYSYMBOL_ROOT = 44,                      /* ROOT  */
  YYSYMBOL_FLOOR_FN = 45,                  /* FLOOR_FN  */
  YYSYMBOL_CEIL_FN = 46,                   /* CEIL_FN  */
  YYSYMBOL_ABS_FN = 47,                    /* ABS_FN  */
  YYSYMBOL_LOG_FN = 48,                    /* LOG_FN  */
  YYSYMBOL_SIN_FN = 49,                    /* SIN_FN  */
  YYSYMBOL_COS_FN = 50,                    /* COS_FN  */
  YYSYMBOL_TAN_FN = 51,                    /* TAN_FN  */
  YYSYMBOL_ASIN_FN = 52,                   /* ASIN_FN  */
  YYSYMBOL_ACOS_FN = 53,                   /* ACOS_FN  */
  YYSYMBOL_ATAN_FN = 54,                   /* ATAN_FN  */
  YYSYMBOL_AMBROSIA_FN = 55,               /* AMBROSIA_FN  */
  YYSYMBOL_LPAREN = 56,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 57,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 58,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 59,                    /* RBRACE  */
  YYSYMBOL_DOT = 60,                       /* DOT  */
  YYSYMBOL_COLON = 61,                     /* COLON  */
  YYSYMBOL_COMMA = 62,                     /* COMMA  */
  YYSYMBOL_INVALID = 63,                   /* INVALID  */
  YYSYMBOL_INT_LITERAL = 64,               /* INT_LITERAL  */
  YYSYMBOL_BOOL_LITERAL = 65,              /* BOOL_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 66,             /* FLOAT_LITERAL  */
  YYSYMBOL_CHAR_LITERAL = 67,              /* CHAR_LITERAL  */
  YYSYMBOL_IDENTIFIER = 68,                /* IDENTIFIER  */
  YYSYMBOL_STRING_LITERAL = 69,            /* STRING_LITERAL  */
  YYSYMBOL_YYACCEPT = 70,                  /* $accept  */
  YYSYMBOL_program = 71,                   /* program  */
  YYSYMBOL_main_function = 72,             /* main_function  */
  YYSYMBOL_statement_list = 73,            /* statement_list  */
  YYSYMBOL_statement = 74,                 /* statement  */
  YYSYMBOL_declaration = 75,               /* declaration  */
  YYSYMBOL_assignment = 76,                /* assignment  */
  YYSYMBOL_print_stmt = 77,                /* print_stmt  */
  YYSYMBOL_if_stmt = 78,                   /* if_stmt  */
  YYSYMBOL_else_if_list = 79,              /* else_if_list  */
  YYSYMBOL_else_part = 80,                 /* else_part  */
  YYSYMBOL_while_stmt = 81,                /* while_stmt  */
  YYSYMBOL_for_stmt = 82,                  /* for_stmt  */
  YYSYMBOL_do_while_stmt = 83,             /* do_while_stmt  */
  YYSYMBOL_type_spec = 84,                 /* type_spec  */
  YYSYMBOL_expression = 85                 /* expression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   420

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  52
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  125

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    80,    80,    87,    91,    92,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   108,   112,   120,   127,   145,
     152,   156,   160,   161,   165,   172,   179,   186,   187,   188,
     189,   190,   191,   195,   196,   197,   198,   200,   210,   211,
     212,   213,   214,   215,   218,   219,   220,   222,   224,   228,
     232,   236,   240
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "KEYWORD_INT",
  "KEYWORD_FLOAT", "KEYWORD_DOUBLE", "KEYWORD_LONG", "KEYWORD_CHAR",
  "KEYWORD_BOOL", "KEYWORD_VOID", "IF", "ELSE_IF", "ELSE", "FOR", "WHILE",
  "DO", "SWITCH", "CASE", "DEFAULT", "BREAK", "CONTINUE", "RETURN",
  "FUNCTION", "MAIN", "PRINT", "INPUT", "ASSIGN", "RETTYPE", "OP_ADD",
  "OP_SUB", "OP_MUL", "OP_DIV", "OP_MOD", "OP_AND", "OP_OR", "OP_NOT",
  "OP_XOR", "OP_POW", "OP_LT", "OP_GT", "OP_LE", "OP_GE", "OP_EQ", "OP_NE",
  "ROOT", "FLOOR_FN", "CEIL_FN", "ABS_FN", "LOG_FN", "SIN_FN", "COS_FN",
  "TAN_FN", "ASIN_FN", "ACOS_FN", "ATAN_FN", "AMBROSIA_FN", "LPAREN",
  "RPAREN", "LBRACE", "RBRACE", "DOT", "COLON", "COMMA", "INVALID",
  "INT_LITERAL", "BOOL_LITERAL", "FLOAT_LITERAL", "CHAR_LITERAL",
  "IDENTIFIER", "STRING_LITERAL", "$accept", "program", "main_function",
  "statement_list", "statement", "declaration", "assignment", "print_stmt",
  "if_stmt", "else_if_list", "else_part", "while_stmt", "for_stmt",
  "do_while_stmt", "type_spec", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-53)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -21,   -52,    10,   -53,   -39,   -53,   -37,   -53,    42,   -53,
     -53,   -53,   -53,   -53,   -53,   -33,   -30,   -16,   -14,   -38,
     -35,   -13,   -53,    25,   -53,    -7,    -6,    -1,   -53,   -53,
     -53,   -53,    -4,     7,    -3,     7,   -53,   -53,   -53,     7,
       7,   -53,   -53,   -53,    43,     7,     7,   -53,   -53,   -53,
     -53,   -53,   225,     9,   245,    84,   265,   345,     7,   377,
     285,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,    19,     7,    20,    67,   -53,   345,
     -53,   -23,   -23,   -53,   -53,   -53,   377,   361,   -15,   -15,
     -15,   -15,   -15,   -15,   -53,   201,   -53,    26,   108,    -3,
     131,     7,   -53,    27,   -53,   305,     8,    35,    23,    29,
      37,   -53,   -53,   -53,     7,   -53,   155,   325,   178,   -53,
      38,   -53,   -53,   202,   -53
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     0,     1,     0,     5,     0,    27,
      28,    29,    30,    31,    32,     0,     0,     0,     0,     0,
       0,     0,     3,     0,     4,     0,     0,     0,     9,    10,
      11,    12,     0,     0,     0,     0,     5,    13,    14,     0,
       0,     6,     7,     8,    15,     0,     0,    48,    51,    49,
      50,    52,     0,     0,     0,     0,     0,    17,     0,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    18,    16,
      47,    33,    34,    35,    36,    37,    44,    45,    38,    39,
      40,    41,    42,    43,     5,     0,     5,     0,     0,     0,
       0,     0,    21,     0,    24,     0,    23,     0,     0,     0,
       0,    19,     5,    26,     0,     5,     0,     0,     0,    25,
       0,    22,     5,     0,    20
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -53,   -53,   -53,   -36,   -53,   -53,   -31,   -53,   -53,   -53,
     -53,   -53,   -53,   -53,   -53,   -34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     8,    24,    25,    26,    27,    28,   106,
     111,    29,    30,    31,    32,    52
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      55,    54,     1,    53,     4,    56,    57,    63,    64,    65,
       5,    59,    60,    61,    62,    63,    64,    65,     6,   109,
     110,     7,    37,    33,    79,    38,    34,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      35,    95,    45,    39,    36,     9,    10,    11,    12,    13,
      14,    40,    15,    41,    42,    16,    17,    18,    98,    43,
     100,    19,    20,    46,    44,    23,    21,   105,   103,    58,
      75,    47,    48,    49,    50,    51,   116,    94,    96,   118,
     117,    97,   101,   113,   107,   114,   123,     9,    10,    11,
      12,    13,    14,   112,    15,   115,   122,    16,    17,    18,
       0,    22,     0,    19,    20,     0,     0,     0,    21,     0,
      23,     9,    10,    11,    12,    13,    14,     0,    15,     0,
       0,    16,    17,    18,     0,     0,     0,    19,    20,     0,
       0,     0,    21,     0,     9,    10,    11,    12,    13,    14,
       0,    15,     0,    77,    16,    17,    18,     0,     0,     0,
      19,    20,    23,     0,     0,    21,     0,     0,     9,    10,
      11,    12,    13,    14,     0,    15,     0,   102,    16,    17,
      18,     0,     0,     0,    19,    20,    23,     0,     0,    21,
       0,     9,    10,    11,    12,    13,    14,     0,    15,     0,
     104,    16,    17,    18,     0,     0,     0,    19,    20,    23,
       0,     0,    21,     0,     0,     9,    10,    11,    12,    13,
      14,     0,    15,     0,   119,    16,    17,    18,     0,     0,
       0,    19,    20,    23,     0,     0,    21,     0,     0,    61,
      62,    63,    64,    65,    66,    67,     0,   121,     0,    68,
      69,    70,    71,    72,    73,     0,    23,     0,     0,     0,
       0,     0,     0,    61,    62,    63,    64,    65,    66,    67,
       0,   124,    99,    68,    69,    70,    71,    72,    73,     0,
      23,     0,     0,    61,    62,    63,    64,    65,    66,    67,
       0,     0,    74,    68,    69,    70,    71,    72,    73,     0,
       0,     0,     0,    61,    62,    63,    64,    65,    66,    67,
       0,     0,    76,    68,    69,    70,    71,    72,    73,     0,
       0,     0,     0,    61,    62,    63,    64,    65,    66,    67,
       0,     0,    78,    68,    69,    70,    71,    72,    73,     0,
       0,     0,     0,    61,    62,    63,    64,    65,    66,    67,
       0,     0,    80,    68,    69,    70,    71,    72,    73,     0,
       0,     0,     0,    61,    62,    63,    64,    65,    66,    67,
       0,     0,   108,    68,    69,    70,    71,    72,    73,     0,
       0,     0,     0,    61,    62,    63,    64,    65,    66,    67,
       0,     0,   120,    68,    69,    70,    71,    72,    73,    61,
      62,    63,    64,    65,    66,     0,     0,     0,     0,    68,
      69,    70,    71,    72,    73,    61,    62,    63,    64,    65,
       0,     0,     0,     0,     0,    68,    69,    70,    71,    72,
      73
};

static const yytype_int8 yycheck[] =
{
      36,    35,    23,    34,    56,    39,    40,    30,    31,    32,
       0,    45,    46,    28,    29,    30,    31,    32,    57,    11,
      12,    58,    60,    56,    58,    60,    56,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      56,    75,    35,    56,    58,     3,     4,     5,     6,     7,
       8,    26,    10,    60,    60,    13,    14,    15,    94,    60,
      96,    19,    20,    56,    68,    68,    24,   101,    99,    26,
      61,    64,    65,    66,    67,    68,   112,    58,    58,   115,
     114,    14,    56,    60,    57,    56,   122,     3,     4,     5,
       6,     7,     8,    58,    10,    58,    58,    13,    14,    15,
      -1,    59,    -1,    19,    20,    -1,    -1,    -1,    24,    -1,
      68,     3,     4,     5,     6,     7,     8,    -1,    10,    -1,
      -1,    13,    14,    15,    -1,    -1,    -1,    19,    20,    -1,
      -1,    -1,    24,    -1,     3,     4,     5,     6,     7,     8,
      -1,    10,    -1,    59,    13,    14,    15,    -1,    -1,    -1,
      19,    20,    68,    -1,    -1,    24,    -1,    -1,     3,     4,
       5,     6,     7,     8,    -1,    10,    -1,    59,    13,    14,
      15,    -1,    -1,    -1,    19,    20,    68,    -1,    -1,    24,
      -1,     3,     4,     5,     6,     7,     8,    -1,    10,    -1,
      59,    13,    14,    15,    -1,    -1,    -1,    19,    20,    68,
      -1,    -1,    24,    -1,    -1,     3,     4,     5,     6,     7,
       8,    -1,    10,    -1,    59,    13,    14,    15,    -1,    -1,
      -1,    19,    20,    68,    -1,    -1,    24,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,    -1,    59,    -1,    38,
      39,    40,    41,    42,    43,    -1,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      -1,    59,    61,    38,    39,    40,    41,    42,    43,    -1,
      68,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    57,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    57,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    57,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    57,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    57,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    57,    38,    39,    40,    41,    42,    43,    28,
      29,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    28,    29,    30,    31,    32,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,
      43
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    23,    71,    72,    56,     0,    57,    58,    73,     3,
       4,     5,     6,     7,     8,    10,    13,    14,    15,    19,
      20,    24,    59,    68,    74,    75,    76,    77,    78,    81,
      82,    83,    84,    56,    56,    56,    58,    60,    60,    56,
      26,    60,    60,    60,    68,    35,    56,    64,    65,    66,
      67,    68,    85,    76,    85,    73,    85,    85,    26,    85,
      85,    28,    29,    30,    31,    32,    33,    34,    38,    39,
      40,    41,    42,    43,    57,    61,    57,    59,    57,    85,
      57,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    58,    85,    58,    14,    73,    61,
      73,    56,    59,    76,    59,    85,    79,    57,    57,    11,
      12,    80,    58,    60,    56,    58,    73,    85,    73,    59,
      57,    59,    58,    73,    59
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    70,    71,    72,    73,    73,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    75,    75,    76,    77,    78,
      79,    79,    80,    80,    81,    82,    83,    84,    84,    84,
      84,    84,    84,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     6,     2,     0,     2,     2,     2,     1,
       1,     1,     1,     2,     2,     2,     4,     3,     4,     9,
       8,     0,     4,     0,     7,    11,     9,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     3,     1,     1,
       1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: main_function  */
#line 81 "mytho.y"
      {
          fprintf(outputFile, "Parsing Successful\n");
      }
#line 1326 "mytho.tab.c"
    break;

  case 15: /* declaration: type_spec IDENTIFIER  */
#line 109 "mytho.y"
      {
          insertSymbol((yyvsp[0].sval), (yyvsp[-1].dtype));
      }
#line 1334 "mytho.tab.c"
    break;

  case 16: /* declaration: type_spec IDENTIFIER ASSIGN expression  */
#line 113 "mytho.y"
      {
          insertSymbol((yyvsp[-2].sval), (yyvsp[-3].dtype));
          updateSymbol((yyvsp[-2].sval), (yyvsp[0].expr));
      }
#line 1343 "mytho.tab.c"
    break;

  case 17: /* assignment: IDENTIFIER ASSIGN expression  */
#line 121 "mytho.y"
      {
          updateSymbol((yyvsp[-2].sval), (yyvsp[0].expr));
      }
#line 1351 "mytho.tab.c"
    break;

  case 18: /* print_stmt: PRINT LPAREN expression RPAREN  */
#line 128 "mytho.y"
      {
          if ((yyvsp[-1].expr).type == TYPE_INT)
              fprintf(outputFile, "%d\n", (yyvsp[-1].expr).val.iVal);
          else if ((yyvsp[-1].expr).type == TYPE_FLOAT)
              fprintf(outputFile, "%f\n", (yyvsp[-1].expr).val.fVal);
          else if ((yyvsp[-1].expr).type == TYPE_DOUBLE)
              fprintf(outputFile, "%lf\n", (yyvsp[-1].expr).val.dVal);
          else if ((yyvsp[-1].expr).type == TYPE_CHAR)
              fprintf(outputFile, "%c\n", (yyvsp[-1].expr).val.cVal);
          else if ((yyvsp[-1].expr).type == TYPE_BOOL)
              fprintf(outputFile, "%s\n", (yyvsp[-1].expr).val.bVal ? "true" : "false");
      }
#line 1368 "mytho.tab.c"
    break;

  case 19: /* if_stmt: IF LPAREN expression RPAREN LBRACE statement_list RBRACE else_if_list else_part  */
#line 146 "mytho.y"
      {
          ensureBooleanCondition((yyvsp[-6].expr), "if");
      }
#line 1376 "mytho.tab.c"
    break;

  case 20: /* else_if_list: else_if_list ELSE_IF LPAREN expression RPAREN LBRACE statement_list RBRACE  */
#line 153 "mytho.y"
      {
          ensureBooleanCondition((yyvsp[-4].expr), "else if");
      }
#line 1384 "mytho.tab.c"
    break;

  case 24: /* while_stmt: WHILE LPAREN expression RPAREN LBRACE statement_list RBRACE  */
#line 166 "mytho.y"
      {
          ensureBooleanCondition((yyvsp[-4].expr), "while");
      }
#line 1392 "mytho.tab.c"
    break;

  case 25: /* for_stmt: FOR LPAREN assignment COLON expression COLON assignment RPAREN LBRACE statement_list RBRACE  */
#line 173 "mytho.y"
      {
          ensureBooleanCondition((yyvsp[-6].expr), "for");
      }
#line 1400 "mytho.tab.c"
    break;

  case 26: /* do_while_stmt: DO LBRACE statement_list RBRACE WHILE LPAREN expression RPAREN DOT  */
#line 180 "mytho.y"
      {
          ensureBooleanCondition((yyvsp[-2].expr), "do-while");
      }
#line 1408 "mytho.tab.c"
    break;

  case 27: /* type_spec: KEYWORD_INT  */
#line 186 "mytho.y"
                       { (yyval.dtype) = TYPE_INT; }
#line 1414 "mytho.tab.c"
    break;

  case 28: /* type_spec: KEYWORD_FLOAT  */
#line 187 "mytho.y"
                       { (yyval.dtype) = TYPE_FLOAT; }
#line 1420 "mytho.tab.c"
    break;

  case 29: /* type_spec: KEYWORD_DOUBLE  */
#line 188 "mytho.y"
                       { (yyval.dtype) = TYPE_DOUBLE; }
#line 1426 "mytho.tab.c"
    break;

  case 30: /* type_spec: KEYWORD_LONG  */
#line 189 "mytho.y"
                       { (yyval.dtype) = TYPE_INT; }
#line 1432 "mytho.tab.c"
    break;

  case 31: /* type_spec: KEYWORD_CHAR  */
#line 190 "mytho.y"
                       { (yyval.dtype) = TYPE_CHAR; }
#line 1438 "mytho.tab.c"
    break;

  case 32: /* type_spec: KEYWORD_BOOL  */
#line 191 "mytho.y"
                       { (yyval.dtype) = TYPE_BOOL; }
#line 1444 "mytho.tab.c"
    break;

  case 33: /* expression: expression OP_ADD expression  */
#line 195 "mytho.y"
                                     { (yyval.expr) = evaluateArithmetic((yyvsp[-2].expr), (yyvsp[0].expr), 1); }
#line 1450 "mytho.tab.c"
    break;

  case 34: /* expression: expression OP_SUB expression  */
#line 196 "mytho.y"
                                     { (yyval.expr) = evaluateArithmetic((yyvsp[-2].expr), (yyvsp[0].expr), 2); }
#line 1456 "mytho.tab.c"
    break;

  case 35: /* expression: expression OP_MUL expression  */
#line 197 "mytho.y"
                                     { (yyval.expr) = evaluateArithmetic((yyvsp[-2].expr), (yyvsp[0].expr), 3); }
#line 1462 "mytho.tab.c"
    break;

  case 36: /* expression: expression OP_DIV expression  */
#line 198 "mytho.y"
                                     { (yyval.expr) = evaluateArithmetic((yyvsp[-2].expr), (yyvsp[0].expr), 4); }
#line 1468 "mytho.tab.c"
    break;

  case 37: /* expression: expression OP_MOD expression  */
#line 200 "mytho.y"
                                     {
                                        if ((yyvsp[-2].expr).type != TYPE_INT || (yyvsp[0].expr).type != TYPE_INT) {
                                            fprintf(outputFile, "Type Error: modulus only allowed for int\n");
                                            exit(1);
                                        }
                                        (yyval.expr).type = TYPE_INT;
                                        (yyval.expr).val.iVal = (yyvsp[-2].expr).val.iVal % (yyvsp[0].expr).val.iVal;
                                      }
#line 1481 "mytho.tab.c"
    break;

  case 38: /* expression: expression OP_LT expression  */
#line 210 "mytho.y"
                                     { (yyval.expr) = evaluateRelational((yyvsp[-2].expr), (yyvsp[0].expr), 1); }
#line 1487 "mytho.tab.c"
    break;

  case 39: /* expression: expression OP_GT expression  */
#line 211 "mytho.y"
                                     { (yyval.expr) = evaluateRelational((yyvsp[-2].expr), (yyvsp[0].expr), 2); }
#line 1493 "mytho.tab.c"
    break;

  case 40: /* expression: expression OP_LE expression  */
#line 212 "mytho.y"
                                     { (yyval.expr) = evaluateRelational((yyvsp[-2].expr), (yyvsp[0].expr), 3); }
#line 1499 "mytho.tab.c"
    break;

  case 41: /* expression: expression OP_GE expression  */
#line 213 "mytho.y"
                                     { (yyval.expr) = evaluateRelational((yyvsp[-2].expr), (yyvsp[0].expr), 4); }
#line 1505 "mytho.tab.c"
    break;

  case 42: /* expression: expression OP_EQ expression  */
#line 214 "mytho.y"
                                     { (yyval.expr) = evaluateRelational((yyvsp[-2].expr), (yyvsp[0].expr), 5); }
#line 1511 "mytho.tab.c"
    break;

  case 43: /* expression: expression OP_NE expression  */
#line 215 "mytho.y"
                                     { (yyval.expr) = evaluateRelational((yyvsp[-2].expr), (yyvsp[0].expr), 6); }
#line 1517 "mytho.tab.c"
    break;

  case 44: /* expression: expression OP_AND expression  */
#line 218 "mytho.y"
                                     { (yyval.expr) = evaluateLogical((yyvsp[-2].expr), (yyvsp[0].expr), 1); }
#line 1523 "mytho.tab.c"
    break;

  case 45: /* expression: expression OP_OR expression  */
#line 219 "mytho.y"
                                     { (yyval.expr) = evaluateLogical((yyvsp[-2].expr), (yyvsp[0].expr), 2); }
#line 1529 "mytho.tab.c"
    break;

  case 46: /* expression: OP_NOT expression  */
#line 220 "mytho.y"
                                     { (yyval.expr) = evaluateNot((yyvsp[0].expr)); }
#line 1535 "mytho.tab.c"
    break;

  case 47: /* expression: LPAREN expression RPAREN  */
#line 222 "mytho.y"
                                     { (yyval.expr) = (yyvsp[-1].expr); }
#line 1541 "mytho.tab.c"
    break;

  case 48: /* expression: INT_LITERAL  */
#line 224 "mytho.y"
                                     {
                                        (yyval.expr).type = TYPE_INT;
                                        (yyval.expr).val.iVal = (yyvsp[0].ival);
                                      }
#line 1550 "mytho.tab.c"
    break;

  case 49: /* expression: FLOAT_LITERAL  */
#line 228 "mytho.y"
                                     {
                                        (yyval.expr).type = TYPE_DOUBLE;
                                        (yyval.expr).val.dVal = (yyvsp[0].fval);
                                      }
#line 1559 "mytho.tab.c"
    break;

  case 50: /* expression: CHAR_LITERAL  */
#line 232 "mytho.y"
                                     {
                                        (yyval.expr).type = TYPE_CHAR;
                                        (yyval.expr).val.cVal = (yyvsp[0].cval);
                                      }
#line 1568 "mytho.tab.c"
    break;

  case 51: /* expression: BOOL_LITERAL  */
#line 236 "mytho.y"
                                     {
                                        (yyval.expr).type = TYPE_BOOL;
                                        (yyval.expr).val.bVal = (yyvsp[0].ival);
                                      }
#line 1577 "mytho.tab.c"
    break;

  case 52: /* expression: IDENTIFIER  */
#line 240 "mytho.y"
                                     {
                                        (yyval.expr) = getSymbolValue((yyvsp[0].sval));
                                      }
#line 1585 "mytho.tab.c"
    break;


#line 1589 "mytho.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 245 "mytho.y"


void ensureBooleanCondition(ExprValue expr, const char *context) {
    if (expr.type != TYPE_BOOL) {
        fprintf(outputFile, "Type Error: %s condition must be boolean\n", context);
        exit(1);
    }
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
    for(int i = 0; i < symbolCount; i++) {
        if(strcmp(symbolTable[i].name, name) == 0) {
            fprintf(outputFile, "Semantic Error: Variable '%s' already declared\n", name);
            exit(1);
        }
    }

    strcpy(symbolTable[symbolCount].name, name);
    symbolTable[symbolCount].type = type;

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

    if (a.type == TYPE_CHAR || a.type == TYPE_BOOL ||
        b.type == TYPE_CHAR || b.type == TYPE_BOOL) {
        fprintf(outputFile, "Type Error: invalid arithmetic operation\n");
        exit(1);
    }

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

    if (a.type == TYPE_CHAR || b.type == TYPE_CHAR) {
        fprintf(outputFile, "Type Error: cannot compare char with non-char\n");
        exit(1);
    }

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
