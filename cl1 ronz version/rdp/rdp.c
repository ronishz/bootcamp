#include <stdio.h>
#include <stdlib.h>

char *input;
void E();
void E_();
void T();
void T_();
void F();
void error();

int main()
{
	input=(char *)malloc(25);
	scanf("%s",input);
	E();
	printf("String matched");
}

void E()
{
	T();
	E_();

}

void T()
{
	F();
	T_();

}

void E_()
{

	if(*input=='+')
	{
		input++;
		T();
		E_();
	}
		
}

void T_()
{
	if(*input=='*')
	{
		input++;
		F();
		T_();
	}
		
}

void F()
{
	if(*input=='i')
	{
		input++;
	}
	else if(*input=='(')
	{
		input++;
		E();
		if(*input==')')
		{
			input++;
		}

	}
	else
	{
		error();
	}

}

void error()
{
	printf("\nString not matched");
	exit(0);

}
