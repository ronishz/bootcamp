lex File:

%{
#include "y.tab.h"		// c programs block in this you can include libraries and define functions.
%}

/*

... definitions ...
%%
... rules ...
%%
... subroutines ...


*/

%%

[0-9]+                {yylval = (int)yytext; return NUMBER;} 
                       /* cast pointer to int for compiler warning */
[ \t\n]               ;
"+"      return(PLUS);
"-"      return(MINUS);
"*"      return(TIMES);
"("      return(LEFT_PARENTHESIS);
")"      return(RIGHT_PARENTHESIS);
";"      return(END);


%%

int yywrap (void)   // Function yywrap is called by lex when input is exhausted.
{
	return 1;		// Return 1 if you are done or 0 if more processing is required.
}


yacc File:

%{

#include <stdio.h>		// c programs block in this you can include libraries and define functions and .
#include <stdlib.h>
#include <string.h>

  typedef struct node
  {
    struct node *left;
    struct node *right;
    char *token;
  } node;

  node *mknode(node *left, node *right, char *token);
  void printtree(node *tree);

#define YYSTYPE struct node *

%}

%start lines 		// %start -> 	Identifies a nonterminal name for the start symbol.

%token  NUMBER     // %tokens -> Identifies the token names that the yacc command accepts. Declares all token names in the declarations section.
%token  PLUS    MINUS   TIMES
%token  LEFT_PARENTHESIS    RIGHT_PARENTHESIS
%token  END

%left   PLUS    MINUS  //%left -> Identifies tokens that are left-associative with other tokens.
%left   TIMES		   // All of the tokens on the same line have the same precedence level and associativity. 

%%

lines:  /* empty */
        | lines line /* do nothing */

line:   exp END     { printtree($1); printf("\n");}
    ;

exp    : term             {$$ = $1;}
        | exp PLUS term     {$$ = mknode($1, $3, "+");}
        | exp MINUS term    {$$ = mknode($1, $3, "-");}
        ;

term   : factor           {$$ = $1;}
        | term TIMES factor  {$$ = mknode($1, $3, "*");}
        ;

factor : NUMBER           {$$ = mknode(0,0,(char *)yylval);}
        | LEFT_PARENTHESIS exp RIGHT_PARENTHESIS {$$ = $2;}
        ;
%%

int main (void) 
{
	return yyparse ( ); // yyparse() reads a stream of token/value pairs from yylex(), which needs to be supplied.
}

node *mknode(node *left, node *right, char *token)
{
  /* malloc the node */
  node *newnode = (node *)malloc(sizeof(node));
  char *newstr = (char *)malloc(strlen(token)+1);
  strcpy(newstr, token);
  newnode->left = left;
  newnode->right = right;
  newnode->token = newstr;
  return(newnode);
}

void printtree(node *tree)
{
  int i;


  if (tree->left || tree->right)
    printf("(");

  printf(" %s ", tree->token);   // root

  if (tree->left)
    printtree(tree->left);       // left
  if (tree->right)
    printtree(tree->right);		 // right

  if (tree->left || tree->right)
    printf(")");
}

int yyerror (char *s) // In the event of syntax errors yacc calls the user-supplied function yyerror.
{
	fprintf (stderr, "%s\n", s);
	/*
	Writes the C string pointed by format to the stream. If format includes format 
	specifiers (subsequences beginning with %), the additional arguments following 
	format are formatted and inserted in the resulting string replacing their respective specifiers.
	*/
} 


