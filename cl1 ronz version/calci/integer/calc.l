%{
    #include "y.tab.h"
    extern int yylval;
%}

%%
[0-9]+ {yylval=atoi(yytext);return num;}
"\n" { return 0; }
" " { printf(""); }
"+" {return plus;}
"-" {return minus;}
\*  {return mul;}
"/" {return div;}
"(" {return ob;}
")" {return cb;}

    
%%

int yywrap()
{return 1;}
