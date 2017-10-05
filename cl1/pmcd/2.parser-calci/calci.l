%{
#include "y.tab.h"
extern int yyerror(char *);
%}
%%
[0-9]+|[0-9]+\.[0-9]+ {yylval.dval=atof(yytext);return NUM;}
[a-z] {yylval.dname=yytext[0];return name;}
"sin" { return SIN;}
"cos" { return COS;}
"log" { return LOG;}
"sqrt" { return SQRT;}
"tan" { return TAN;}
[ \t] ;
\n return 0;
. return yytext[0];
%%
int yywrap()
{
return (1);
}

