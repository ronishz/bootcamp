%{
    #include <stdio.h>
    #include <stdlib.h>
    
    void display();
    void insert(char *,char *);
    
struct symtab
{
    char name[100];
    char type[100];
}s[20];
int i=0;
    
%}

%%
"#include" {printf("%s is pre-processor directive\n",yytext);}
"main()"|"scanf"|"printf" {printf("%s is in built function\n",yytext);}
"<stdio.h>"|"<conio.h>"|"<string.h>"|"<stdlib.h>" {printf("%s is header file\n",yytext);}
"int"|"char"|"float"|"double"|"long" {printf("%s is datatype\n",yytext);insert(yytext,"datatype");}
[a-zA-Z]+ {printf("%s is variable\n",yytext);insert(yytext,"id");}
";" {printf("%s is semicolon\n",yytext);}
"{"|"}" {printf("%s is curly brace\n",yytext);}

%%

int yywrap()
{return 1;}

void insert(char *n,char *t)
{
    strcpy(s[i].name,n);
    strcpy(s[i].type,t);
    i++;

}

void display()
{
    printf("Name\tType\n");
    for(int j=0;j<i;j++)
    {
        printf("%s\t|%s\n",s[j].name,s[j].type);
    }
}

int main()
{
    yyin=fopen("scanner_test.c","r");
    yylex();
    display();
    return 0;
}
