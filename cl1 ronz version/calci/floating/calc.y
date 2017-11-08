%{
    #include <stdio.h>
    #include <stdlib.h>
    extern int yylex();
	extern int yyparse();
%}

 %union{
    double dval;
    char dname[10];
 }
 
%start s
%left plus minus
%left mul div
%token<dval> num
%token<dname> name
%type<dval> E
%token plus
%token minus
%token mul
%token div
%token ob
%token cb
%token eq

%%

s : name eq E {printf("ans: %s=%lf\n",$1,$3);}
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
