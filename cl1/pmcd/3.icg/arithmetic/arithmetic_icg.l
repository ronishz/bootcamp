%{
#include "y.tab.h"
#include<stdio.h>
%}

%%
[0-9]+|[0-9]+\.[0-9]+ {yylval.dval=atof(yytext); return num;}
[a-zA-Z] {yylval.dname=yytext[0]; return name;}
[\t];
\n return 0;
. return yytext[0];
%%

int yywrap()
{
return 1;
}

