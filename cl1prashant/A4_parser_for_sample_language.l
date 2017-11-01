lex file:

%{
	#include<stdio.h>
	#include"y.tab.h"  // c programs block in this you can include libraries and define functions.
	int line=0;
%}

/*

... definitions ...
%%
... rules ...
%%
... subroutines ...


*/



%%
[ \t]+			;
int|float|char		return DT;
main			return MAIN;
return			return RET;
if|for|while|else	return KEYW;
[a-zA-Z][a-zA-Z0-9]*	return ID;
[0-9]+			return NUM;	
[(){},;=]		return yytext[0];  //yytext holds the text matched by the current token. So yytext[0] holds the first character of the text matched by the current token. Sometimes you have a rule which can match different texts so you need to get the real text matched like for variable names or you have a rule to match all arithmetic operations.
\n			line++;
[><>=<===]		return AOP;
%%

yywrap() // Function yywrap is called by lex when input is exhausted. 
{
	return 1; //Return 1 if you are done or 0 if more processing is required.
}


yacc file:

%{
	#include<stdio.h>       // c programs block in this you can include libraries and define functions and .
	extern FILE *yyin;      //extern tells the compiler that the variable is defined somewhere else, so it doesn't complain about it being undefined.
	extern int line;
%}

%token DT NUM ID RET MAIN KEYW AOP  //%tokens -> Identifies the token names that the yacc command accepts. Declares all token names in the declarations section.

%%
Pdash:P		{printf("\n Parsing Done....No Syntax Error\n");}   // grammer used for parsing the file.

P:DT MAIN '(' ')' '{' S R '}'

S:DS S
 |ES S
 |CS S
 |

DS:DT V ';'
V:ID|V','ID

ES:ID'='E';'
E:NUM|ID

CS:KEYW '(' A ')' '{' S '}'
A:ID AOP ID|ID AOP NUM|';'';'

R :RET NUM';'
%%

int main()
{
	yyin=fopen("input.txt","r");
	yyparse(); //yyparse() reads a stream of token/value pairs from yylex(), which needs to be supplied.
}

yyerror()    // this function will generate error at line no when error is generted in parsing 
{
	printf("\n Error at line no:%d \n",line);
}


input file:

int main()
{
	int a,b,c;
	a=b
	if(a>2)
	{
		for(;;)
		{
			c=2;
		}
	}
	return 0;
}  
