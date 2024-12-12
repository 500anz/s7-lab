%{
#include <stdio.h>
#include<stdlib.h>
int yylex();
void yyerror();
int valid=1;
%}
%token digit letter
%%
start: letter s
s: letter s | digit s |;
%%
void yyerror(){
printf("Invalid identifier.\n");
valid = 0;
exit(0);}
void main(){
printf("Enter identifier: ");
yyparse();
if(valid){
printf("Valid identifier.\n");}
}