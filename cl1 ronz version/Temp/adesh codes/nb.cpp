#include<iostream>
#include<math.h>
#include<string>
using namespace std;

class Naive{
	typedef struct entry{
		
		string age;
		string income;
		string student;
		string credit;
		string buycomp;
	}t1;
	public:
		

		t1 *e=new t1[11];
		float ypro,npro;
		void create();
		float yprob(string age, string income, char student, string credit);
		float nprob(string age, string income, char student, string credit);
		void res(float ypro, float npro);
};
void Naive::create(){

		e[0].age="senior";
		e[0].income="low";
		e[0].student="n";
		e[0].credit="excell";
		e[0].buycomp="n";
		e[1].age="youth";
		e[1].income="low";
		e[1].student="y";
		e[1].credit="fair";
		e[1].buycomp="y";
		e[2].age="senior";
		e[2].income="medium";
		e[2].student="n";
		e[2].credit="excell";
		e[2].buycomp="y";
		e[3].age="senior";
		e[3].income="low";
		e[3].student="n";
		e[3].credit="fair";
		e[3].buycomp="n";
		e[4].age="medium";
		e[4].income="low";
		e[4].student="n";
		e[4].credit="fair";
		e[4].buycomp="n";
		e[5].age="medium";
		e[5].income="low";
		e[5].student="n";
		e[5].credit="fair";
		e[5].buycomp="y";
		e[6].age="medium";
		e[6].income="medium";
		e[6].student="n";
		e[6].credit="fair";
		e[6].buycomp="n";
		e[7].age="medium";
		e[7].income="low";
		e[7].student="n";
		e[7].credit="fair";
		e[7].buycomp="n";
		e[8].age="youth";
		e[8].income="medium";
		e[8].student="y";
		e[8].credit="fair";
		e[8].buycomp="y";
		e[9].age="youth";
		e[9].income="high";
		e[9].student="y";
		e[9].credit="fair";
		e[9].buycomp="y";
		e[10].age="medium";
		e[10].income="high";
		e[10].student="n";
		e[10].credit="excell";
		e[10].buycomp="y";
}
float Naive::yprob(string age, string income, char student, string credit){
	int i;	
	float agec=0,incomec=0,stuc=0,crec=0,bc=0,yc=0,nc=0;
	float prob;
	for(i=0;i<11;i++){
		if(e[i].age==age){
			agec++;
		}
		if(e[i].income==income){
			incomec++;
		}
		if(e[i].student=="y"){
			stuc++;
		}
		if(e[i].credit==credit){
			crec++;
		}
		if(e[i].buycomp=="y"){
			yc++;
		}
		
	}
	agec=agec/yc;
	incomec=incomec/yc;
	stuc=stuc/yc;
	crec=crec/yc;
	prob=(yc/11);
	prob=prob*agec*incomec*stuc*crec;
	cout<<"\nProbability of Buying Computer: "<<prob<<"\n";
	return prob;
}
float Naive::nprob(string age, string income, char student, string credit){
	int i;	
	float agec=0,incomec=0,stuc=0,crec=0,nc=0;
	float prob;
	for(i=0;i<11;i++){
		if(e[i].age==age){
			agec++;
		}
		if(e[i].income==income){
			incomec++;
		}
		if(e[i].student=="y"){
			stuc++;
		}
		if(e[i].credit==credit){
			crec++;
		}
		if(e[i].buycomp=="n"){
			nc++;
		}	
	}
	agec=agec/nc;
	incomec=incomec/nc;
	stuc=stuc/nc;
	crec=crec/nc;
	prob=(nc/11);
	prob=prob*agec*incomec*stuc*crec;
	cout<<"\nProbability of Not Buying Computer: "<<prob<<"\n";
	return prob;
}

void Naive::res(float yprob, float nprob){
	cout<<"\nProbability of Buying Computer: "<<yprob<<"\n";
	cout<<"\nProbability of Not Buying Computer: "<<nprob<<"\n";
	if(yprob>=nprob){
		cout<<"\n\n>>>>>>>>>>>>>buy computer......";
	}
	else{
		cout<<"\n\n>>>>>>>>>>>>>Will Not buy Computer......";
	}
}
int main(){
	string age;
	string income;
	char student;
	string credit;
	string buycomp;
	Naive N;
	float ypro,npro;
	cout<<"\nEnter age(youth/medium/senior): ";
	cin>>age;
	cout<<"\nEnter income(high/medium/low): ";
	cin>>income;	
	cout<<"\nIs student(yes/no): ";
	cin>>student;
	cout<<"\nEnter credit(fair/excell): ";
	cin>>credit;
	N.create();
	ypro=N.yprob(age, income, student, credit);
	npro=N.nprob(age, income, student, credit);
	N.res(ypro,npro);
	return 0;
}

			
