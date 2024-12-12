%{
#include <stdio.h>
%}

%%
abc     { printf("ABC"); }  /* Convert 'abc' to 'ABC' */
.|\n    { printf("%s", yytext); } /* Print any other character as is */
%%

int main() {
    yylex();  /* Start the lexical analysis */
    return 0;
}

int yywrap() {
    return 1;
}