%{
    #include "y.tab.h"
    #include <string.h>
    extern YYSTYPE yylval;
    
%}

%%
[0-9]+|[0-9]+\.[0-9]+ {yylval.dval=atof(yytext);return num;}
[a-zA-Z]+ {strcpy(yylval.dname,yytext);return name;}
"\n" { return 0; }
"+" {return plus;}
"-" {return minus;}
\*  {return mul;}
"/" {return div;}
"(" {return ob;}
")" {return cb;}
"=" {return eq;}

    
%%

int yywrap()
{return 1;}
