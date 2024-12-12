%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
void yyerror();
%}
%token NUMBER ID
%left '+' '-'
%left '*' '/'
%%
expr: expr '+' expr
 |expr '-' expr
 |expr '*' expr
 |expr '/' expr
 |'-'NUMBER
 |'-'ID
 |'('expr')'
 |NUMBER
 |ID
 ;
%%
void main(){
printf("Enter the expression\n");
yyparse();
printf("\nExpression is valid\n");
exit(0);}
void yyerror(){
printf("\nExpression is invalid\n");
exit(0);}
