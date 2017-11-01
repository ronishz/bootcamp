lex File:

%{
#include<stdio.h>
#include<string.h>         // c programs block in this you can include libraries and define functions.
#include "y.tab.h"
%}


/*

... definitions ...
%%
... rules ...
%%
... subroutines ...


*/


%%
[a-z][a-z0-9]* {strcpy(yylval.var,yytext);return NAME;}
[+]  {strcpy(yylval.var,yytext);return PLUS;}
[=]  {strcpy(yylval.var,yytext);return EQUAL;}
[-] {strcpy(yylval.var,yytext);return SUBT;}
[*] {strcpy(yylval.var,yytext);return MULT;}
[/]	{strcpy(yylval.var,yytext);return DIVI;}
[\n\t] {return yytext[0];}  //yytext holds the text matched by the current token. So yytext[0] holds the first character of the text matched by the current token. Sometimes you have a rule which can match different texts so you need to get the real text matched like for variable names or you have a rule to match all arithmetic operations.
%%


yacc file:

%{
#include<stdio.h>			// c programs block in this you can include libraries and define functions and .
#include<ctype.h>			
#include<string.h>
FILE *fout;					//extern tells the compiler that the variable is defined somewhere else, so it doesn't complain about it being undefined.
%}
								// %tokens -> Identifies the token names that the yacc command accepts. Declares all token names in the declarations section.
%token<var> NAME PLUS EQUAL MULT DIVI SUBT    // tokens from lex file.
%type<var> exp     				//%type -> Identifies the type of nonterminals. Type-checking is performed when this construct is present.
%union							//%union -> Identifies the yacc value stack as the union of the various type of values desired. By default, the values returned are integers. The effect of this construct is to provide the declaration of YYSTYPE directly from the input.

{
	char var[10];
}
%right EQUAL			  //%right-> Identifies tokens that are right-associative with other tokens.
%left PLUS SUBT           //%left -> Identifies tokens that are left-associative with other tokens.
%left MULT DIVI			  // All of the tokens on the same line have the same precedence level and associativity. 



%%	
	
input:line'\n'input
     |'\n'input
     |/*empty*/
     ;
line:NAME EQUAL exp {fprintf(fout,"MOV %s,AX\n",$1);}
    ;
exp:NAME PLUS NAME {fprintf(fout,"MOV AX,%s \n ADD AX,%s\n",$1,$3);}
    |NAME SUBT NAME {fprintf(fout,"MOV AX,%s \n SUB AX,%s\n",$1,$3);}
    |NAME MULT NAME {fprintf(fout,"MOV AX,%s \n MUL AX,%s\n",$1,$3);}
    |NAME DIVI NAME {fprintf(fout,"MOV AX,%s \n DIV AX,%s\n",$1,$3);}
    |NAME  	 {strcpy($$,$1);}    //strcpy(dest,src)
    ;
%%

extern yylineno;    //extern tells the compiler that the variable is defined somewhere else, so it doesn't complain about it being undefined.

yyerror()  			// In the event of syntax errors yacc calls the user-supplied function yyerror.
{
	printf("\nerror %d",yylineno);	
}
yywrap() 			// Function yywrap is called by lex when input is exhausted. 
{
	return 1;			// Return 1 if you are done or 0 if more processing is required.
}
extern FILE *yyin;	//extern tells the compiler that the variable is defined somewhere else, so it doesn't complain about it being undefined.

int main()
{
	FILE *fin;
	fin=fopen("input.txt","r");
	fout=fopen("out.txt","w");

	yyin=fin;        // input file for yacc in yyin.

	yyparse();    	// yyparse() reads a stream of token/value pairs from yylex(), which needs to be supplied.
	fcloseall();	
	return 0;
}



input file:

t1=a/b
t2=b+t1
t3=t2-c
t4=t3/d
e=t4

