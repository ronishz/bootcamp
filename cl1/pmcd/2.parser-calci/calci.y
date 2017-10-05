%{
#include<math.h>
#include<stdio.h>
extern int yylex();
extern int yyparse();
extern int yyerror(char *e);
%}
%union
{
	double dval;
	char dname;
}
%token<dval> NUM 
%token<dnum> SIN
%token<dnum> COS
%token<dnum> SQRT
%token<dnum> TAN
%token<dnum> LOG
%type<dval> exp
%token<dname> name
%left '+' '-'
%left '*' '/'
%%

s   : 	name '=' exp { printf ("%c = %f",$1,$3);}

exp : 	exp '+' exp { $$ = $1 + $3 ;}
	|exp '-' exp { $$ = $1 - $3 ;}
	|exp '*' exp { $$ = $1 * $3 ;}
	|exp '/' exp { $$ = $1 / $3 ;}
	|SIN'('exp')' {$$=sin(($3*(3.14/180)));}
	|COS'('exp')' {$$=cos(($3*(3.14/180)));}
        |TAN'('exp')' {$$=tan(($3*(3.14/180)));}
	|LOG'('exp')'  {$$=log($3);}
	|SQRT'('exp')'  {$$=sqrt($3);}
	|NUM {$$=$1;}
        ;
%%

int main()
{
	printf("\nEnter the expression:  ");
	yyparse();
	printf("\n");
	yylex();
}
extern int yyerror(char * e)
{
	printf("\nString is rejected.\n");
}


