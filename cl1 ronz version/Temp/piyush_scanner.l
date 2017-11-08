%{
#include<stdio.h>
#include<stdlib.h>
void display();
void insert(char *,char *);
struct symtab
{
	char name[100];
	char type[100];

}s[20];
int i=0;

%}
prep1 "#include"
hf stdio.h|conio.h|fstream.h|math.h|string.h|stdlib.h
prep2 "#define"
bif "main()"|"scanf"|"gets"|"puts"|"printf"
dt "int"|"float"|"char"|"double"|"long double"|"void"
dig [0-9]+
id [a-zA-Z0-9]+
loop "while"
cndst "if"|"else"
aop "+"|"-"|"*"|"/"|"%"|"++"|"--"
rop "=="|"!="|">"|"<"|">="|"<="
lop "&&"|"||"|"!"
Asop "="|"+="|"-="|"*="|"/="|"%="
spsym ";"|":"|","
rbrc "("|")"
ocb "{"
ccb "}"
str [""]
abrc "["|"]"
array [a-zA-z0-9]"["[0-9]*"]"

%%
{prep1} {printf("%s is preprocessor directive\n",yytext);}
{hf} {printf("%s is header file\n",yytext);}

{bif} {printf("%s is built in function\n",yytext);}
{id}+{dig}*{id}*\(\) {printf("%s is user defined function\n",yytext);insert(yytext,"function");}
{dt} {printf("%s is data type\n",yytext);}
{dig} {printf("%s is digit\n",yytext);}
{str}.+{str} {printf("%s is string literal\n",yytext);}
{array} {printf("%s is Array\n",yytext);insert(yytext,"Array");}
{id} {printf("%s is variable\n",yytext);insert(yytext,"id");}


{cndst} {printf("%s is conditional statement\n",yytext);}
{loop} {printf("%s is loop\n",yytext);}
{aop} {printf("%s is arithmetic operator\n",yytext);}
{rop} {printf("%s is relational operator\n",yytext);}
{lop} {printf("%s is logical operator\n",yytext);}
{Asop} {printf("%s is assignment operator\n",yytext);}
{spsym} {printf("%s is special symbol\n",yytext);}
{rbrc} {printf("%s is rounded bracket\n",yytext);}
{ocb} {printf("%s is open curly bracket\n",yytext);}
{ccb} {printf("%s is close curly bracket\n",yytext);}
{abrc} {printf("%s is squarebrac\n",yytext);}
%%
int yywrap()
{
return(1);
}

void insert(char *c,char *t)
{

	strcpy(s[i].name,c);
	strcpy(s[i].type,t);
	i++;

	
} 
void display()
{
	int j;
	printf("\n-------------------------------------\n\t    Symbol Table\n-------------------------------------\nName of Symbol  \t| Type \t \t \n-------------------------------------\n");
	for(j=0;j<20;j++)
	{
		printf("%s          \t        | %s   \n",s[j].name,s[j].type);
	}
	printf("--------------------------------------\n");
}
int main()
{
	yyin=fopen("xyz.c","r");
	yylex();
	display();
	
	
	
}
