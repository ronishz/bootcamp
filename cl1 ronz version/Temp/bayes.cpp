#include<iostream>
using namespace std;

typedef struct table
{
	int id;
	int age;
	int income;
	bool student;
	int credit;
	bool buycomp;
}t1;

int main() 
{
	int rno;
	char ch;
	cout<<"\n Enter number of records in the table : ";     
	cin>>rno;				
	t1 *X=new t1[rno];
	for(int i=0;i<rno;i++)
	{
		cout<<"\n Enter record for id "<<i+1<<" of table : \n";
		X[i].id=i+1;
		do
		{
			cout<<"\n Age : 1.Infant  2.Young  3.Old\n Enter : ";	
			cin>>X[i].age;
			if(X[i].age>3 || X[i].age<1)
			{
				cout<<"\n Please enter correct age..\n";
			}
		}while(X[i].age>3 || X[i].age<1);
		
		do
		{
			cout<<"\n Income: 1.High  2.Medium  3.Low\n Enter : ";	
			cin>>X[i].income;
			if(X[i].income>3 || X[i].income<1)
			{
				cout<<"\n Please enter corect income..\n";			
			}

		}while(X[i].income>3 || X[i].income<1);
		
		cout<<"\n Whether the person is student?  1.Yes  0.No\n Enter : ";	
		cin>>X[i].student;

		do
		{
			cout<<"\n Credit Ratings:1.Low  2.Fair  3.High\n Enter : ";	
			cin>>X[i].credit;
			if(X[i].credit>3 || X[i].credit<1)
			{
				cout<<"\n Please enter correct credit ratings..";			
			}

		}while(X[i].credit>3 || X[i].credit<1);

		cout<<"\n Whether the person buys the computer?  1.Yes  0.No\n Enter : ";	
		cin>>X[i].buycomp;
	}

	cout<<"| ID\t| Age\t| Income|Student| Credit Rating | Buy\t|\n";
	cout<<"----------------------------------------------------------";	
	for(int i=0;i<rno;i++)
	{
		cout<<"\n| "<<X[i].id<<"\t| ";
		
		switch(X[i].age)
		{
		case 1:cout<<"Infant| ";break;
		case 2:cout<<"Young\t| ";break;
		case 3:cout<<"Old\t| ";break;
		}
		
		switch(X[i].income)
		{
		case 1:cout<<"Low\t| ";break;
		case 2:cout<<"Medium| ";break;
		case 3:cout<<"High\t| ";break;
		}

		if(X[i].student)
		{
			cout<<"Yes\t| ";	
		}
		else
		{	
			cout<<"No\t| ";	
		}
		
		switch(X[i].credit)
		{
		case 1:cout<<"Low\t\t| ";break;
		case 2:cout<<"Fair\t\t| ";break;
		case 3:cout<<"High\t\t| ";break;
		}

		if(X[i].buycomp)
		{
			cout<<"Yes\t| ";
		}
		else
		{	
			cout<<"No\t| ";	
		}
	}
	int yes=0,no=0;			
	for(int i=0;i<rno;i++)
	{
		if(X[i].buycomp)
		{
			yes++;
		}
		else
		{
			no++;
		}
	}

	float pbyes=(float)yes/rno,pbno=(float)no/rno;	
	cout<<"\n\n P(buy Computer =  Yes) = "<<pbyes<<endl;
	cout<<" P(buy Computer = No) = "<<pbno<<endl;
	
	int c,f,t,tf,pn=0,pno=0;
	float py[20],pn1[20],s;
	
	do
	{
		t=0;
		cout<<"\n Enter selection critera for conditional probability : \n";
		cout<<"\n 1.Buy Computer \n 0.Not Buy Computer : ";
		cin>>tf;
		cout<<"\n 1.Age  2.Income  3.Student  4.Credit Rating : ";
		cin>>c;
		switch (c)
		{
		case 1:
			do
			{
			cout<<"\n Enter Field of Age: 1.Infant  2.Young  3.Old : ";
			cin>>f;
			}while(f>3 || f<1);
			
			for(int i=0;i<rno;i++)
			{
				if(X[i].age==f && X[i].buycomp==tf)
				{
					t++;
				}
			}
			(tf==1)?s=py[pn++]=(float)t/yes:s=pn1[pno++]=(float)t/no;
			switch(f)
			{
			case 1:cout<<" P(Age = Infant | buys Computer = ";
				(tf==1)?cout<<"Yes":cout<<"No";
				cout<<") = "<<s<<endl;
				break;
			case 2:cout<<" P(Age = Young | buys Computer = ";
				(tf==1)?cout<<"Yes":cout<<"No";
				cout<<") = "<<s<<endl;
				break;
			case 3:cout<<" P(Age = Old | buys Computer = ";
				(tf==1)?cout<<"Yes":cout<<"No";
				cout<<") = "<<s<<endl;
				break;
			}
			break;

		case 2:
			do
			{
			cout<<"\n Enter Field of Income: 1.High  2.Medium  3.Low : ";
			cin>>f;
			}while(f>3 || f<1);
			
			for(int i=0;i<rno;i++)
			{
				if(X[i].income==f && X[i].buycomp==tf)
				{
					t++;
				}
			}
			(tf==1)?s=py[pn++]=(float)t/yes:s=pn1[pno++]=(float)t/no;
			switch(f)
			{
			case 1:cout<<" P(Income = High | buys Computer = ";
				(tf==1)?cout<<"Yes":cout<<"No";
				cout<<") = "<<s<<endl;
				break;
			case 2:cout<<" P(Income = Medium | buys Computer = ";
				(tf==1)?cout<<"Yes":cout<<"No";
				cout<<") = "<<s<<endl;
				break;
			case 3:cout<<" P(Income = Low | buys Computer = ";
				(tf==1)?cout<<"Yes":cout<<"No";
				cout<<") = "<<s<<endl;
				break;
			}
			break;

		case 3:
			do{
			cout<<"\n Enter field of Student: 1.Yes  0.No : ";
			cin>>f;
			}while(f>=1 && f<=0);
			for(int i=0;i<rno;i++)
			{
				if(X[i].student==f && X[i].buycomp==tf)
				{
					t++;
				}
			}
			(tf==1)?s=py[pn++]=(float)t/yes:s=pn1[pno++]=(float)t/no;
			switch(f){
			case 1:cout<<" P(Student = Yes | buys Computer = ";
				(tf==1)?cout<<"Yes":cout<<"No";
				cout<<") = "<<s<<endl;
				break;
			case 0:cout<<" P(Student = No | buys Computer = ";
				(tf==1)?cout<<"Yes":cout<<"No";
				cout<<") = "<<s<<endl;
				break;
			}
			break;

		case 4:
			do
			{
			cout<<"\n Enter Field of Credit Ratings: 1.Low  2.Fair  3.High : ";
			cin>>f;
			}while(f>3 || f<1);
			
			for(int i=0;i<rno;i++)
			{
				if(X[i].credit==f && X[i].buycomp==tf)
				{
					t++;
				}
			}
			(tf==1)?s=py[pn++]=(float)t/yes:s=pn1[pno++]=(float)t/no;
			switch(f)
			{
			case 1:cout<<" P(Credit Ratings = Low | buys Computer = ";
				(tf==1)?cout<<"Yes":cout<<"No";
				cout<<") = "<<s<<endl;
				break;
			case 2:cout<<" P(Credit Ratings = Fair | buys Computer = ";
				(tf==1)?cout<<"Yes":cout<<"No";
				cout<<") = "<<s<<endl;
				break;
			case 3:cout<<" P(Credit Ratings = High | buys Computer = ";
				(tf==1)?cout<<"Yes":cout<<"No";
				cout<<") = "<<s<<endl;
				break;
			}
			break;
		
		default:
			break;
		}
	
	t=0;
	cout<<"\n Press Y for more conditional probabilities : ";
	cin>>ch;
	
	}while(ch=='y'||ch=='Y');

	float fproy=1,fpron=1;
	for(int i=0;i<pn;i++){
		fproy=fproy*py[i];
	}
	cout<<"\n P(X | buys Computer = Yes) = "<<fproy<<endl;
	fproy=fproy*pbyes;
	for(int i=0;i<pno;i++){
		fpron=fpron*pn1[i];
	}
	cout<<" P(X | buys Computer = No) = "<<fpron<<endl;
	fpron=fpron*pbno;
	cout<<"\n P(buys Computer = Yes) = "<<fproy<<endl;
	cout<<" P(buys Computer = No) = "<<fpron<<endl;
	return 0;	
}
