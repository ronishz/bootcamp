%{
	#include "y.tab.h"
	extern int yylval;
%}

digit [0-9]+

%%

{digit}	{ yylval = atoi(yytext); return num; } 
"\n"	{ return 0; }
"+"	{ return plus; }
"-"	{ return minus; }
\*	{ return mul; }
"/"	{ return div; }


%%

int yywrap(){
	return 1;
}
