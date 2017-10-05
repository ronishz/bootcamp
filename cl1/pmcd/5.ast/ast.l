%{
#include "y.tab.h"
extern int yylval;
%}


%%

[0-9]+    {yylval = atoi(yytext); return NUMBER;}   /* cast pointer to int for compiler warning */
[ \t\n]+  ;
"+"      return(PLUS);
"-"      return(MINUS);
"*"      return(TIMES);
"/"      return(DIVIDE);
";"      return(END);


%%

int yywrap (void) {return 1;}
