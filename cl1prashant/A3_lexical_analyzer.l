
%{
#include<stdio.h> // c programs block in this you can include libraries and define functions.
%}


/*

... definitions ...
%%
... rules ...
%%
... subroutines ...


main"()"																	{printf("%s is a function\n",yytext);}

*/

/*

input file (Input.c)

#include<conio.h>
#include<stdio.h>
int main()
{
int a,b,c;
printf("enter the 2 numbers");
scanf("%d",&a);
scanf("%d",&b);
c=a*b;
printf("multiplication = %d",c);
}

*/

HeaderFile <stdio.h>|<conio.h>

letter	[A-Za-z]
digit	[0-9]
underscore	[_]
uop      [++|size of|~]
Arithmatic[+|-|*|/]
relop	[<|>|<=|>=|<>]
b	[{|}|;|:|,|(|)]
lop["&&"|"||"]
cond    [?:]
equal   [==|!=]
ws	[ \t\n]
preprocessor #include|#pragma

doublequote["]

%%

 
{HeaderFile}                                                          		{printf ("%s is HeaderFile\n",yytext);}

int|string|float|long	                                       		        { printf("%s is datatype\n",yytext);}// Variable yytext is a pointer to the matched string.
void|if|else|do|while|switch|case|break|return|printf|scanf|main                {printf("%s is keyword\n",yytext);}
"%c"|"%d"|"%e"|"%s"                                                             {printf ("%s is format specifier\n",yytext);}
"="                                                                             {printf ("%s is assignment operator\n",yytext);}
{letter}({letter}|{digit}|{underscore})*	                    	        {printf("%s is identifer\n",yytext);}
&{letter}({letter}|{digit}|{underscore})*	                                {printf("%s is referance address\n",yytext);}
{digit}+	                                                    		{printf("%s is digit\n",yytext);}

{ws}	                                                        		{ } //The return value of YYText() is the single token that was just recognized.

{preprocessor}                                                  		{printf ("%s is preprocessor\n",yytext);}
{uop}                                                                           {printf ("%s is unary operator\n",yytext);}
{Arithmatic}                                                                    {printf ("%s is Arithmatic operator\n",yytext);}
{relop}                                                         	        {printf ("%s is relational operator\n",yytext);}
{b}                                              	            		{printf("%s is a delimiter\n",yytext);}
{lop}                                                                           {printf ("%s is logical operator\n",yytext);}
{cond}                                                                          {printf ("%s is conditional operator\n",yytext);}
{equal}                                                                         {printf ("%s is equality operator\n",yytext);}

{doublequote}({letter}|{ws}|{digit})*{doublequote}                              {printf ("%s is literal\n",yytext);} //eg:->  "text" | "67" | " "
%%

int yywrap() // Function yywrap is called by lex when input is exhausted. 
{
	return 1; //Return 1 if you are done or 0 if more processing is required.
}
int main()
{
	FILE *fp;
	fp=fopen("Input.c","r");
	yyin=fp; // The input file for lex is yyin.
	yylex();  // To obtain tokens yacc calls yylex. Function yylex has a return type of int that returns a token.
	// Every C program requires a main function. In this case we simply call yylex that is the main entry-point for lex.
	return 0;
}




