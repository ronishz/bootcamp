%{
    #include <stdio.h>
    #include <stdlib.h>
    extern int yylex();
    extern int yyparse();
    int i=0;
    
    struct quad{
        char op;
        char a1;
        char a2;
        char result;
    }q[20];
    int count=0;
    char temp='A';

%}

%union{
    char dname;
}

%token<dname> name
%token<dname> num
%token<dname> plus
%token<dname> minus
%token<dname> mul
%token<dname> div
%token<dname> eq
%token ob
%token cb
%start s
%type<dname> E
%left plus minus
%left mul div
%left ob cb

%%

s : name eq E {addQF($2,$3,'-',$1);}
  ;
 
E : E plus E {$$=addQ($2,$1,$3,temp);temp++;}
  | E minus E {$$=addQ($2,$1,$3,temp);temp++;}
  | E mul E {$$=addQ($2,$1,$3,temp);temp++;}
  | E div E {$$=addQ($2,$1,$3,temp);temp++;}
  | ob E cb {$$=$2;}
  | num {$$=$1;}
  | name {$$=$1;}
  ;
  
%%

int main()
{
    yyparse();
    display();
    return 0;
    
}

int yyerror(char *e)
{
    printf("%s",e);
    exit(1);

}

char addQ(char op,char a1,char a2,char result)
{
    q[count].op=op;
    q[count].a1=a1;
    q[count].a2=a2;
    q[count].result=result;
    count++;
    return temp;
}

void addQF(char op,char a1,char a2,char result)
{
    q[count].op=op;
    q[count].a1=a1;
    q[count].a2=a2;
    q[count].result=result;
    count++;
    //return temp;
}

void display()
{
    printf("op\targ1\targ2\tresult\t\n");
    for(i=0;i<count;i++)
    {
        printf("%c\t%c\t%c\t%c\t\n",q[i].op,q[i].a1,q[i].a2,q[i].result);
    }
}

  
