%{
#include <stdio.h>

int vowels = 0;      
int consonants = 0; 
%}

%%
[aeiouAEIOU]    { vowels++; }      
[a-zA-Z]        { consonants++; }     
.|\n            { /* Ignore any other characters (digits, spaces, punctuation, etc.) */ }
%%

int main() {
    yylex();  /* Start the lexical analysis */
    printf("\nTotal number of vowels: %d\n", vowels);
    printf("Total number of consonants: %d\n", consonants);
    return 0;
}

int yywrap() {
    return 1;
}
