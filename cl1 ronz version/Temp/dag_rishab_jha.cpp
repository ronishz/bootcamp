//============================================================================
// Name        : dag.cpp
// Author      : rishabh
// Version     :
// Copyright   : Do whatever you want to do
// Description : Hello World in C++, Ansi-style
//============================================================================

/* Flow of the code
Sun bro using nodes jaruri nai Hai na DAG karna like I did it without using the tree.
From quadraples itself. Like for example

Given

+ a b A
+ a b B
* A B C

I found that the triples of first 2 are equal so I know A = B so I got following

+ a b A
+ a b A
* A B C

there would be another loop which will make above as 

+ a b A
+ a b A
* A A C
Now I started adding quadraples one by one to the DAG quad if there results parameter is not equal to any one added to the DAG quad so I get

+ a b A
* A A C

*/


#include <iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

int no_of_quads = -1;
struct quad{
	char op[10],arg1[10],arg2[10],result[10];
}*quads,*opt_quads;


void quadInp(){
	cout<<"enter no of quadraples : ";
	cin>>no_of_quads;
	quads = new quad[no_of_quads];		//using dynamin mem allo, cute ryt ;)
	opt_quads = new quad[no_of_quads];
	for(int i=0; i<no_of_quads; i++){
		cout<<"\nenter data : ";
		cin>>quads[i].op>>quads[i].arg1>>quads[i].arg2>>quads[i].result;
	}
}

void quadDisp(){
	for(int i=0; i<no_of_quads; i++){
		printf("\n%s\t%s\t%s\t%s\n",quads[i].op,quads[i].arg1,quads[i].arg2,quads[i].result);
	}
}

void dag(){
	for(int i = 0; i<no_of_quads; i++){
		char temp_mem[10];
		for(int j=i+1; j<no_of_quads; j++){
			if((!strcmp(quads[i].op,quads[j].op)) and (!strcmp(quads[i].arg1,quads[j].arg1)) and (!strcmp(quads[i].arg2,quads[j].arg2))){
				cout<<"match"<<endl;
				strcpy(temp_mem,quads[j].result);
				strcpy(quads[j].result,quads[i].result);
				
				/*
				the above for loop makes sure that 
				+ a b A         + a b A
				+ a b B     ->  + a b A
				* A B C         * A B A     now the lower b has to be made A to make any sense that is done by the for loop below
				*/
				
				for(int k=0; k<no_of_quads; k++){                   
					if(!strcmp(quads[k].arg1,temp_mem)){
						strcpy(quads[k].arg1,quads[i].result);
					}
					if(!strcmp(quads[k].arg2,temp_mem)){
						strcpy(quads[k].arg2,quads[i].result);
					}
				}
			}
		}
	}
}
int no_opt_quads = -1;
void optimizeQuad(){                    // the loop below adds only thow quads whose lable is not already present in optimized code.
	for(int i=0; i<no_of_quads; i++){
		int present_flag = 0;
		for(int j=0; j<=no_opt_quads; j++){
			if(!strcmp(opt_quads[j].result,quads[i].result)){
				present_flag=1;
				cout<<"match1"<<endl;
			}
		}
		if(present_flag==0){
			no_opt_quads++;
			opt_quads[no_opt_quads] = quads[i];
		}
	}
}

void optimizedQuadDisp(){
	cout<<"\nOPTIMIZED QUADS\n";
	for(int i=0; i<=no_opt_quads; i++){
		printf("\n%s\t%s\t%s\t%s\n",opt_quads[i].op,opt_quads[i].arg1,opt_quads[i].arg2,opt_quads[i].result);
	}
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	quadInp();
	quadDisp();
	dag();
	quadDisp();
	optimizeQuad();
	optimizedQuadDisp();
	return 0;
}
