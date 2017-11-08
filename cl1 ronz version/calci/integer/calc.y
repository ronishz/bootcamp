 %{
    #include <stdio.h>
    #include <stdlib.h>
    extern int yylex();
	extern int yyparse();
 %}

%start s
%left plus minus
%left mul div
%token num
%token plus
%token minus
%token mul
%token div
%token ob
%token cb

%%

s : E {printf("ans: %d\n",$1);}
  ;
  
E : E plus E {$$=$1+$3;}
  | E minus E {$$=$1-$3;}
  | E mul E {$$=$1*$3;}
  | E div E {$$=$1/$3;}
  | num {$$=$1;}
  | ob E cb {$$=$2;}
  ;
  
%%

int main()
{
    yyparse();
    return 0;
}

int yyerror(char *e)
{
    printf("%s",e);
    exit(1);
}
