%{
#include <stdio.h>

int lines = 0;
int words = 0;
int characters = 0;
%}

%%
\n          { lines++; characters++; }      
[ \t]+      { characters += yyleng; }       
[^ \t\n]+   { words++; characters += yyleng; } 

%%
int main() {
    yylex(); 

    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", characters);

    return 0;}
int yywrap() {
    return 1;
}
