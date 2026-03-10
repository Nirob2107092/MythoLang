%option noyywrap yylineno

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mytho_shared.h"
#include "mytho.tab.h"

extern YYSTYPE yylval;
FILE *yyin;
%}

DIGIT       [0-9]
ID          [A-Za-z_][A-Za-z0-9_]*
INTNUM      {DIGIT}+
FLOATNUM    {DIGIT}+"."{DIGIT}+

%%

"//myth".*              { }

"zeus"                  { return KEYWORD_INT; }
"apollo"                { return KEYWORD_FLOAT; }
"hera"                  { return KEYWORD_DOUBLE; }
"titan"                 { return KEYWORD_LONG; }
"charizard"             { return KEYWORD_CHAR; }
"truth"                 { return KEYWORD_BOOL; }
"Abyss"                 { return KEYWORD_VOID; }

"omen"                  { return IF; }
"fate"                  { return ELSE_IF; }
"destiny"               { return ELSE; }
"cycle"                 { return FOR; }
"eternal"               { return WHILE; }
"invoke"                { return DO; }
"judgement"             { return SWITCH; }
"verdict"               { return CASE; }
"otherwise"             { return DEFAULT; }
"halt"                  { return BREAK; }
"persist"               { return CONTINUE; }
"back"                  { return RETURN; }

"ritual"                { return FUNCTION; }
"Prometheus"            { return MAIN; }

"proclaim"              { return PRINT; }
"listen"                { return INPUT; }

":="                    { return ASSIGN; }
":->"                   { return RETTYPE; }

"add"                   { return OP_ADD; }
"minus"                 { return OP_SUB; }
"forge"                 { return OP_MUL; }
"divide"                { return OP_DIV; }
"rem"                   { return OP_MOD; }

"AND"                   { return OP_AND; }
"OR"                    { return OP_OR; }
"NOT"                   { return OP_NOT; }
"XOR"                   { return OP_XOR; }

"**"                    { return OP_POW; }

"<="                    { return OP_LE; }
">="                    { return OP_GE; }
"=!"                    { return OP_NE; }
"="                     { return OP_EQ; }
"<"                     { return OP_LT; }
">"                     { return OP_GT; }

"root"                  { return ROOT; }
"flr"                   { return FLOOR_FN; }
"ceil"                  { return CEIL_FN; }
"abs"                   { return ABS_FN; }
"logarithm"             { return LOG_FN; }
"sine"                  { return SIN_FN; }
"cosine"                { return COS_FN; }
"tan"                   { return TAN_FN; }
"asine"                 { return ASIN_FN; }
"acosine"               { return ACOS_FN; }
"atan"                  { return ATAN_FN; }
"ambrosia"              { return AMBROSIA_FN; }

"true"                  { yylval.ival = 1; return BOOL_LITERAL; }
"false"                 { yylval.ival = 0; return BOOL_LITERAL; }

"("                     { return LPAREN; }
")"                     { return RPAREN; }
"{"                     { return LBRACE; }
"}"                     { return RBRACE; }
"."                     { return DOT; }
":"                     { return COLON; }
","                     { return COMMA; }

{FLOATNUM}              { yylval.fval = atof(yytext); return FLOAT_LITERAL; }
{INTNUM}                { yylval.ival = atoi(yytext); return INT_LITERAL; }

\'([^\\\n]|(\\.))\'     { yylval.cval = yytext[1]; return CHAR_LITERAL; }
\"([^\\\n]|(\\.))*\"    { yylval.sval = strdup(yytext); return STRING_LITERAL; }

{ID}                    { yylval.sval = strdup(yytext); return IDENTIFIER; }

[ \t\r]+                { }
\n                      { }

.                       {
                            fprintf(stderr, "Lexical Error: invalid token '%s' at line %d\n", yytext, yylineno);
                            return INVALID;
                        }

%%