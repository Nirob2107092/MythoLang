%{
#include <stdio.h>

%}

%%
"zeus"          { printf("KEYWORD: zeus\n"); }
"apollo"        { printf("KEYWORD: apollo\n"); }
"omen"          { printf("IF STATEMENT\n"); }
"destiny"       { printf("ELSE STATEMENT\n"); }
":="            { printf("ASSIGNMENT\n"); }
[0-9]+          { printf("NUMBER: %s\n", yytext); }
[A-Za-z_][A-Za-z0-9_]* { printf("IDENTIFIER: %s\n", yytext); }
\n              { yylineno++; }
[ \t]           ;   // ignore spaces
.               { printf("UNKNOWN TOKEN: %s\n", yytext); }
%%

int main() {
    FILE *fin = fopen("input_mytho.txt", "r");   // Input file
    if (!fin) {
        perror("Failed to open input file");
        return 1;
    }

    // Redirect stdin and stdout
    yyin = fin;
    freopen("output.txt", "w", stdout);  // redirect printf to output.txt

    printf("=== Mytholang Compiler: Token Stream ===\n");
    printf("%-35s | %s\n", "TOKEN TYPE", "ACTUAL CODE");
    printf("--------------------------------------------------\n");

    yylex();

    fclose(fin);
    return 0;
}
int yywrap() {
    return 1; // 1 = no more input
}