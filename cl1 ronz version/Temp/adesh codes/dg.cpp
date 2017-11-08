#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

struct quad{
	char op[10];
	char arg1[10];
	char arg2[10];
	char res[10];
}q[10];

struct node{
	char label[10][10];
	char value[10];
	char count, num, opstat;
	struct node *left, *right;
} *nodes[10], *temp1, *temp2, *temp3;

struct reclist{
	char name[20];
	int node;
}reg[10];

int noNodes=0;
int noreg=0;
int nq=0;

void inp();
void disp();
void dag();
void antidag();

int recused(char name[10]);
void upres(char name[10],int pos);
struct node *crnode();

int main(){
	cout<<"\n Enter the no. of Quadraples";
	cin>>nq;
	
	inp();
	dag();
	antidag();
	disp();
	return 0;
}

void inp(){
	for(int i=0;i<nq;i++){
		cout<<"\nQuadraple "<<i<<" : ";
		cin>>q[i].op>>q[i].arg1>>q[i].arg2>>q[i].res;
	}
}

void disp(){
	cout<<"\n>>>>>>>>Optimized Quadraple: \n";
	for(int i=0;i<nq;i++){
		cout<<"\n Quadraple "<<i<<" : ";
		cout<<q[i].op<<"\t"<<q[i].arg1<<"\t"<<q[i].arg2<<"\t"<<q[i].res;
	}
	cout<<"\n";
}

int recused(char name[10]){
	for(int i=0;i<noreg;i++){
		if(!strcmp(reg[i].name, name)){
			return reg[i].node;
		}
	
	}
	return -1;
}

void upres(char name[10], int pos){
	int i;
	for(i = 0; i < noreg; i++){
		if(!strcmp(reg[i].name, name)){
			reg[i].node = pos;
			return;
		}
	}
	strcpy(reg[i].name,name);
	reg[i].node = pos;
	noreg++;
}

struct node *crnode(){
	struct node *temp;
	temp=(struct node *) malloc(sizeof(struct node));
	temp->left=NULL;
	temp->right=NULL;
	temp->count=0;
	temp->num=noNodes;
	return temp;
}

void dag(){
	int flag=0,n1,n2;
	for(int i=0;i<nq;i++){
		n1=recused(q[i].arg1);
		n2=recused(q[i].arg2);
		if(n1 != -1 && n2 != -1){
			for(int j = 0; j < noNodes; j++){
				if(!strcmp(q[i].op, nodes[j]->value)){
					if(nodes[j]->left->num == n1 && nodes[j]->right->num == n2){
						strcpy(nodes[j]->label[nodes[j]->count++],q[i].res);
						
						upres(q[i].res, j);
						flag = 1;
						break;
					}
				}
			}
		}	
		if(flag==1){
			flag=0;
			continue;
		}
		if(n1 == -1){
			temp1=crnode();
			temp1->opstat =0;
			strcpy(temp1->value,q[i].arg1);
			nodes[noNodes++] =temp1;
			n1=temp1->num;
			upres(q[i].arg1,n1);
		}
		else{
			temp1=nodes[n1];
		}
		if(!strcmp(q[i].arg2,"#")){
			strcpy(temp1->label[temp1->count++],q[i].res);
			upres(q[i].res,temp1->num);
			continue;
		}
		if(n2 == -1){
			temp2=crnode();
			temp2->opstat =0;
			strcpy(temp2->value,q[i].arg2);
			nodes[noNodes++] =temp2;
			n1=temp2->num;
			upres(q[i].arg2,n2);
		}
		else{
			temp2=nodes[n2];
		}
		temp3= crnode();
		temp3->opstat =1;
		strcpy(temp3->value , q[i].op);
		strcpy(temp3->label[temp3->count++],q[i].res);
		nodes[noNodes++]=temp3;
		temp3->left=temp1;
		temp3->right=temp2;
		upres(q[i].res, temp3->num);
	}
}

void antidag(){
	struct node *temp;
	nq = 0;
	for(int i = 0; i < noNodes; i++){
		temp = nodes[i];
		if(temp->opstat == 0)
			continue;
		strcpy(q[nq].op, temp->value);
		
		if(temp->left->opstat == 0)
			strcpy(q[nq].arg1, temp->left->value);
		else
			strcpy(q[nq].arg1, temp->left->label[temp->left->count]);
		
		if(temp->right->opstat == 0)
			strcpy(q[nq].arg2, temp->right->value);
		else
			strcpy(q[nq].arg2, temp->right->label[temp->right->count]);
		
		strcpy(q[nq++].res, temp->label[--temp->count]);
	}
}

