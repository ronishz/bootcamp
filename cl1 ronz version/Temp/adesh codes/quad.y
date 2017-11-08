%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	extern int yylex();
	extern int yyparse();
	int i, t=0, char buf[5];
	struct Q{
		char op;
		char opr1;
		char opr2;
		char result;
	}q[10];
	int cnt=0;
	char temp='A';
%}
%union{
	char dname;
}
%token<dname> num
%token<dname> name
%token<dname> plus
%token<dname> minus
%token<dname> div
%token<dname> mul
%token<dname> eq
%type<dname> E
%start s
%left plus minus
%left mul div

%%

s: name eq E {addQF{$2, $3, "-", $1);}
 ;

E: E plus E { $$ = addQ{$2,$1,$3, temp); temp++;}
 | E minus E { $$ = addQ{$2,$1,$3, temp); temp++;}
 | E mul E { $$ = addQ{$2,$1,$3, temp); temp++;}
 | E div E { $$ = addQ{$2,$1,$3, temp); temp++;}
 | num { $$ = $1;}
 | name { $$ = $1;}
 ;

%%

int main(){
	printf("Enter Expression:  ");
	yyparse();
	disquad();
	return 0;
}

char addQ(char op, char opr1, char opr2, char result){
	q[cnt].op=op;
	q[cnt].opr1=opr1;
	q[cnt].opr2=opr2;
	q[cnt].result=result;
	cnt++;
	return temp;
}

char addQF(char op, char opr1, char opr2, char result){
	q[cnt].op=op;
	q[cnt].opr1=opr1;
	q[cnt].opr2=opr2;
	q[cnt].result=result;
	cnt++;
}
