%{
    #include "y.tab.h"
    extern YYSTYPE yylval;
%}

%%
[a-zA-Z] {yylval.dname=(char)yytext[0];return name;}
[0-9]+ {yylval.dname=(char)yytext[0];return num;}
"+" {yylval.dname=(char)yytext[0];return plus;}
"-" {yylval.dname=(char)yytext[0];return minus;}
\* {yylval.dname=(char)yytext[0];return mul;}
"/" {yylval.dname=(char)yytext[0];return div;}
"=" {yylval.dname=(char)yytext[0];return eq;}
"(" {return ob;}
")" {return cb;}
"\n" {return 0;}

%%

int yywrap(){return 1;}
