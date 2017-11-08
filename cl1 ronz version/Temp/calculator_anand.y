%{
	#include <stdio.h>
	#include <stdlib.h>
	extern int yylex();
	extern int yyparse();
%}

%start S
%left plus minus
%left mul div
%token num
%token plus
%token minus
%token mul
%token div

%%

S	:	E	{ printf("Result is : %d\n",$1);  }
	;

E	:	E plus E	{ $$ = $1 + $3;  }
	|	E minus E	{ $$ = $1 - $3;  }
	|	E mul E	{ $$ = $1 * $3;  }
	|	E div E	{ $$ = $1 / $3;  }
	|	num		{ $$ = $1; }
	;	 

		
	
%%

int main(){
	yyparse();
	return 0;
}

int yyerror(char *r){
	printf(" : %s ",r);
	exit(1);
}

	
