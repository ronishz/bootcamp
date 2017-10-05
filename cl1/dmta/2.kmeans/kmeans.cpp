#include<iostream>
#include<math.h>
using namespace std;
int main()
{
	int l,att,el,cst;
	int i,j;
	cout<<"Enter number of elements:\n";
	cin>>el;
	cout<<"Enter number of attributes:\n";
	cin>>att;
	int a[el][att];
	int cc[el];
	for (i = 0; i < el; i++) 
	{
		cout<<"Enter "<<att<<" Attributes of "<<(char)(65+i)<<":\n";
		for (j = 0; j < att; j++) 
		{
			{
				cin>>a[i][j];
			}
		}
	}
	cout<<"Enter number of clusters:\n";
	cin>>cst;
	double c[cst][att];
	cout<<"\nInput data is:\n";
	cout<<" \t";
	for (j = 1; j <= att; j++) 
	{
		cout<<"att"<<j<<"\t";
	}
	cout<<"\n";
	for (i = 0; i < el; i++) 
	{
		cout<<(char)(65+i)<<"\t";
		for (j = 0; j < att; j++) 
		{
			cout<<" "<<a[i][j]<<"\t";
		}
		cout<<"\n";
	}
	for(i=0;i<el;i++)
	{
		cc[i]=0;
	}
	int oldcc[el];
	double d[el][cst];
	for (j = 0; j < att; j++) 
	{
		for (i = 0; i < cst; i++) 
		{
			c[i][j]=a[i][j];
		}
	}
	do{
		for(i=0;i<el;i++)
		{
			oldcc[i]=cc[i];
		}
		for (i = 0; i < el; i++) 
		{
			for (j = 0; j < cst; j++) 
			{
				d[i][j]=0;
				for(int k=0;k<att;k++)
				{
					d[i][j]=d[i][j]+(c[j][k]-a[i][k])*(c[j][k]-a[i][k]);
				}
				d[i][j]=sqrt(d[i][j]);
			}
		}
		double tmp=999.99;
		for (j = 0; j < el; j++) 
		{
			tmp=999.99;
			for(i=0;i<cst;i++)
			{
				if(d[j][i]<tmp)
				{
					cc[j]=i;
					tmp=d[j][i];
				}
			}
		}
		int m=0;
		cout<<"\n";
		for(int cl=0;cl<cst;cl++)
		{
			m=0;
			for (i = 0; i < att; i++) 
			{
				c[cl][i]=0;
			}
			cout<<"Entries of Cluster "<<(cl+1)<<" : ";
			for (j = 0; j < el; j++) 
			{
				if(cc[j]==cl)
				{
					cout<<(char)(65+j)<<" ";
					for (i = 0; i < att; i++) 
					{
						c[cl][i]=c[cl][i]+a[j][i];
					}
					m++;
				}
			}
			for (i = 0; i < att; i++) 
			{
				c[cl][i]=c[cl][i]/m;
			}
			cout<<"\n";
		}
		for (l = 0; l < el; l++) 
		{
			if(cc[l]!=oldcc[l])
			{
				break;
			}
		}
		if(l!=el)
		{
			cout<<"\nNew values:\n";
			for(int i=0;i<cst;i++)
			{
				cout<<"Cluster "<<(i+1)<<":\t";
				for(j=0;j<att;j++)
				{
						cout<<c[i][j]<<"\t";
				}
				cout<<"\n";
				}
			}
		}while(l!=el);
		
}
