%{
	#include<stdio.h>
	#include<stdlib.h>
        #include<string.h>
	extern int yylex();
	extern int yyparse();
	struct tn{
		char val[20];
		struct tn *lt, *rt;
	};
	struct tn *tmp1,*root;
	struct tn *crnode(char val[20], struct tn *lt,struct tn*rt);
	void postfix(struct tn *root);
%}
%union{
	struct tn *node;
	char dname[20];
}
%token<dname> id
%token<dname> plus
%token<dname> minus
%token<dname> div
%token<dname> mul
%token<dname> eq
%type<node> E
%start s
%left plus minus
%left mul div

%%
s: id eq E { tmp1=crnode($1, NULL, NULL); root=crnode($2, tmp1, $3); printf("Postfix Traversal: "); postfix(root); printf("\n"); }
 ;

E: E plus E { $$ = crnode($2, $1, $3); }
 | E minus E { $$ = crnode($2, $1, $3); }
 | E mul E { $$ = crnode($2, $1, $3); }
 | E div E { $$ = crnode($2, $1, $3); } 
 | id { $$ = crnode($1, NULL, NULL);}
 ;

%%

int main(){
	yyparse();
	return 0;
}

struct tn *crnode(char val[20],struct tn *lt, struct tn *rt){
	struct tn *tmp;
	tmp=(struct tn *)malloc(sizeof(struct tn));
	strcpy(tmp->val,val);
	tmp->lt=lt;
	tmp->rt=rt;
	return tmp;
}

void postfix(struct tn *root){
	if(root!=NULL){
		postfix(root->lt);
		postfix(root->rt);
		printf("%s ",root->val);
	}
}

int yyerror(char *e){
	printf(" : %s\n",e);
	exit(1);
}
