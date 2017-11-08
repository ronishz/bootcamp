%{
	#include "y.tab.h"
	extern YYSTYPE yylval;
%}
lt [a-zA-Z]

%%
[0-9]+ {yylval.dname=(char)yytext[0]; return num;}
{lt} {yylval.dname=(char)yytext[0]; return name;}
"\n" { return 0;}
"+" {yylval.dname=(char)yytext[0]; return plus;}
"-" {yylval.dname=(char)yytext[0]; return minus;}
"/" {yylval.dname=(char)yytext[0]; return div;}
\* {yylval.dname=(char)yytext[0]; return mul;}
"=" {yylval.dname=(char)yytext[0]; return eq;}
%%
int yywrap(){
	return 1;
}
