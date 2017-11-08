#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct icode
{
char opr,op1[33],op2[33],res[33];
}ic[50];

int temp=0;

void disp(int );
void dispc(int );
void codeopt(int );
void emit(char [] ,char [], char [], char [],int);
int main()
{
	int nq,i;
	scanf("%d",&nq);
	for(i=0;i<nq;i++)
	{
	    char a[33],b[33],c[33],d[33]; 
		scanf("%s %s %s %s",&a,&b,&c,&d);
		emit(a,b,c,d,i);
		
	}
	printf("\n\t\t Intermediate Code \n");
	printf("------------------------------------------------------------------");
	disp(nq);
	codeopt(nq);
	printf("\n\t\t Optimized Intermediate Code \n");
	printf("------------------------------------------------------------------");
	dispc(nq);
	return 0;
}
void emit(char opr[33],char op1[33],char op2[33],char res[33],int icnt)
{
	ic[icnt].opr = opr[0];
	strcpy(ic[icnt].op1,op1);
	if(ic[icnt].opr!='='){
	strcpy(ic[icnt].op2,op2);
	strcpy(ic[icnt++].res,res);}
	else{
	strcpy(ic[icnt].op2," ");
	strcpy(ic[icnt++].res,op2);
	}
}	
void disp(int icnt)
{
	int i;
	printf("\n\nOperator \tOperand 1 \tOperand 2\tResult\n");
	for(i=0;i<icnt;i++)
		printf("%c \t\t%s \t\t%s \t\t%s\n",ic[i].opr,ic[i].op1,ic[i].op2,ic[i].res);
}
void dispc(int icnt)
{
	int i;
	printf("\n\nOperator \tOperand 1 \tOperand 2\tResult\n");
	for(i=0;i<icnt;i++)
	{
		if(ic[i].opr!='='){
		printf("%c \t\t%s \t\t%s \t\t%s\n",ic[i].opr,ic[i].op1,ic[i].op2,ic[i].res);}
		
		if(ic[i].opr==ic[i+1].opr && !strcmp(ic[i].op1,ic[i+1].op1) && !strcmp(ic[i].op2,ic[i+1].op2) && !strcmp(ic[i].res,ic[i+1].res))
		{
				break;
		}

	    
	}
}
void codeopt(int icnt)
{
	int i,j,k;
	char tres1[33],tres2[33];
	for(i=0;i<icnt-1;i++)
	{
		for(j=i+1;j<icnt;j++)
		{
			if(ic[i].opr==ic[j].opr && !strcmp(ic[i].op1,ic[j].op1) && !strcmp(ic[i].op2,ic[j].op2))
			{		
				strcpy(tres1,ic[i].res);				
				strcpy(tres2,ic[j].res);
				for(k=j+1;k<icnt;k++)
				{
					ic[k-1].opr=ic[k].opr;
					if(strcmp(ic[k].op1,tres2)==0)
						strcpy(ic[k-1].op1,tres1);
					else
						strcpy(ic[k-1].op1,ic[k].op1);								
					if(strcmp(ic[k].op2,tres2)==0)
						strcpy(ic[k-1].op2,tres1);
					else
						strcpy(ic[k-1].op2,ic[k].op2);								
					strcpy(ic[k-1].res,ic[k].res);								
				}
				icnt--;
				j--;
				break;
		
			}
				
		}
	}


	for(i = 1;i<icnt;i++)
	{
		if(ic[i].opr == '=' && (!strcmp(ic[i].op1,ic[i-1].res) || !strcmp(ic[i].op2,ic[i-1].res)))
		{
			strcpy(ic[i-1].res,ic[i].res);
			for(j=i;j<icnt-1;j++)
			{
				ic[j].opr = ic[j+1].opr;
				strcpy(ic[j].op1,ic[j+1].op1);
				strcpy(ic[j].op2,ic[j+1].op2);
				strcpy(ic[j].res,ic[j+1].res);
			}	
			i--;
			icnt--;
		}
	}
}