#include<stdio.h>
#include<string.h>

char input[10];
int i=0,e=0;
void E();
void T();
void F();
void Eprime();
void Tprime();

void main()
{
	printf("\nGrammar without recursion:");
	printf("\nE-->TE'");
	printf("\nT-->FT'");
	printf("\nE'-->+TE'|e");
	printf("\nT'-->*FT'|e");
	printf("\nF-->id|(E)");
	printf("\nEnter an arithmetic expression:\n");
	//scanf("%[^\n]",&input);
	fgets(input,10,stdin);  // fgets ( str, num, FILE * stream );
	/*
	Reads characters from stream and stores them as a C string into str until (num-1) characters 
	have been read or either a newline or the end-of-file is reached, whichever happens first.
	
	
	*/
	input[strlen(input)-1]='\0';
	E();

	if(strlen(input)==i && e==0)
		printf("\nACCEPTED\n");
	else
		printf("\n REJECTED\n");
}

void E()
{
	printf("\n E-->TE'");
	T();
	Eprime();
}

void Eprime()
{
	if(input[i]=='+')
	{
		printf("\n E'-->+TE'");
		i++;
		T();
		Eprime();
	}
	else
	printf("\n Backtrack from E' \t E'-->e");
}

void T()
{
	printf("\n T-->FT'");
	F();
	Tprime();
}

void Tprime()
{
	if(input[i]=='*')
	{
		printf("\n T'-->*FT'");
		i++;
		F();
		Tprime();
	}
	else
	printf("\n Backtrack from T' \t T'-->e");
}

void F()
{
	if(input[i]=='a')
	{
		printf("\n F-->a");
		i++;
	}
	else
	{
		if(input[i]=='(')
		{
			printf("F-->(E)");
			i++;
			E();
			if(input[i]==')')
			{
			i++;
			}
			else
			{
				printf("\nSyntax error");
				e=1;
			}
		}
		else
			e=1;
	}
}

/*output
[exam@localhost ~]$ gcc rdp.c
[exam@localhost ~]$ ./a.out

Grammar without recursion:
E-->TE'
T-->FT'
E'-->+TE'
T'-->+FT'
F-->id
Enter an arithmetic expression:
a*a+a

 E-->TE'
 T-->FT'
 F-->a
 T'-->*FT'
 F-->a
 Backtrack from T' 	 T'-->e
 E'-->+TE'
 T-->FT'
 F-->a
 Backtrack from T' 	 T'-->e
 Backtrack from E' 	 E'-->e
ACCEPTED
*/
