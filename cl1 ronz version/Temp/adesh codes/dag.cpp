#include<iostream>
using namespace std;
#include<string.h>
#include<stdlib.h>

struct quadruple{
	char op[10];
	char arg1[10];
	char arg2[10];
	char result[10];
} q[10];

struct node{
	char label[10][10];
	char value[10];
	char count, num, opStatus;
	struct node *left, *right;
} *nodes[10], *temp1, *temp2, *temp3;
	
struct recentList{
	char name[10];
	int node;
} reg[10];

int noNodes = 0;
int noReg = 0;
int nq = 0;

void input();
void display();
void dag();
int recentUsed(char name[10]);
void updateRecentUsed(char name[10], int pos);
struct node *createNode();
void antiDag();

int main(){
	//input quadruple
	cout<<"Enter number of quadruples: ";
	cin>>nq;
	
	input();
	dag();
	antiDag();
	display();
	
	return 0;
}

void input(){
	for(int i=0; i<nq; i++){
		cout<<"Quadruple "<<i<<" :";
		cin>>q[i].op>>q[i].arg1>>q[i].arg2>>q[i].result;
	}
}

void display(){
//display quadruple
	cout<<"\n\nOptimized Quadruple:\n";
	cout<<"Quadruple(i) :\tOP\tARG1\tARG2\tRESULT\n";
	int count = 0;
	for(int i=0; i<nq; i++){
		cout<<"Quadruple("<<count++<<") :";
		cout<<"\t"<<q[i].op<<"\t"<<q[i].arg1<<"\t"<<q[i].arg2<<"\t"<<q[i].result<<endl;
	}
}

void dag(){
	int flag = 0, n1, n2;
	for(int i = 0; i < nq; i++){
		n1 = recentUsed(q[i].arg1);
		n2 = recentUsed(q[i].arg2);
		if(n1 != -1 && n2 != -1){
			for(int j = 0; j < noNodes; j++){
				if(!strcmp(q[i].op, nodes[j]->value)){
					if(nodes[j]->left->num == n1 && nodes[j]->right->num == n2){
						strcpy(nodes[j]->label[nodes[j]->count++],q[i].result);
						
						updateRecentUsed(q[i].result, j);
						flag = 1;
						break;
					}
				}
			}
		}	
		if(flag == 1){
			flag = 0;
			continue;
		}
			
		if(n1 == -1){
			temp1 = createNode();
			temp1->opStatus = 0;
			strcpy(temp1->value, q[i].arg1);
			nodes[noNodes++] = temp1;
			n1 = temp1->num;
			updateRecentUsed(q[i].arg1, n1);
		}
		else
			temp1 = nodes[n1];
			
		if(!strcmp(q[i].arg2,"#")){
			strcpy(temp1->label[temp1->count++], q[i].result);
			updateRecentUsed(q[i].result, temp1->num);
			continue;
		}
		
		if(n2 == -1){
			temp2 = createNode();
			temp2->opStatus = 0;
			strcpy(temp2->value, q[i].arg2);
			nodes[noNodes++] = temp2;
			n2 = temp2->num;
			updateRecentUsed(q[i].arg2, n2);
		}
		else
			temp2 = nodes[n2];
			
		temp3 = createNode();
		temp3->opStatus = 1;
		strcpy(temp3->value, q[i].op);
		strcpy(temp3->label[temp3->count++], q[i].result);
		nodes[noNodes++] = temp3;
		temp3->left = temp1;
		temp3->right = temp2;
		updateRecentUsed(q[i].result, temp3->num);
		
	}
}

int recentUsed(char name[10]){
	for(int i = 0; i < noReg; i++){
		if(!strcmp(reg[i].name, name))
			return reg[i].node;
	}
	return -1;
}

void updateRecentUsed(char name[10], int pos){
	int i;
	for(i = 0; i < noReg; i++){
		if(!strcmp(reg[i].name, name)){
			reg[i].node = pos;
			return;
		}
	}
	strcpy(reg[i].name,name);
	reg[i].node = pos;
	noReg++;
}

struct node *createNode(){
	struct node *temp;
	temp = (struct node *) malloc(sizeof(struct node));
	temp->left = NULL;
	temp->right = NULL;
	temp->count = 0;
	temp->num = noNodes;
	return temp;
}

void antiDag(){
	struct node *temp;
	nq = 0;
	for(int i = 0; i < noNodes; i++){
		temp = nodes[i];
		if(temp->opStatus == 0)
			continue;
		strcpy(q[nq].op, temp->value);
		
		if(temp->left->opStatus == 0)
			strcpy(q[nq].arg1, temp->left->value);
		else
			strcpy(q[nq].arg1, temp->left->label[temp->left->count]);
		
		if(temp->right->opStatus == 0)
			strcpy(q[nq].arg2, temp->right->value);
		else
			strcpy(q[nq].arg2, temp->right->label[temp->right->count]);
		
		strcpy(q[nq++].result, temp->label[--temp->count]);
	}
}

/* OUTPUT

student@student:~$ g++ -o dag dag.cpp
student@student:~$ ./dag
Enter number of quadruples: 5
Quadruple 0 :* b c t1
Quadruple 1 :* b c t2
Quadruple 2 :- a t1 t3
Quadruple 3 :+ t3 t2 t4
Quadruple 4 := t4 # a

Optimized Quadruple:
Quadruple(i) :	OP	ARG1	ARG2	RESULT
Quadruple(0) :	*	b	c	t2
Quadruple(1) :	-	a	t2	t3
Quadruple(2) :	+	t3	t2	a
student@student:~$ 

*/
