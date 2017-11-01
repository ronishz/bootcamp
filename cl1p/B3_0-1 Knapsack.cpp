// A Dynamic Programming based solution for 0-1 Knapsack problem
// Time Complexity: O(nW) where n is the number of items and W is the capacity of knapsack.
// O(b^d)

#include<stdio.h>
#include<iostream>
#define maxi 10
using namespace std;
 
// A utility function that returns maximum of two integers
int max(int a, int b) { return (a > b)? a : b; }
 
// Returns the maximum value that can be put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n)
{
   int i, w;
   int K[n+1][W+1];  // creates that 0-1 knapsack matrix.
 
   // Build table K[][] in bottom up manner
   for (i = 0; i <= n; i++)
   {
       for (w = 0; w <= W; w++)
       {
           if (i==0 || w==0)
               K[i][w] = 0; //making 1st row and col zero.
           else if (wt[i-1] <= w) // if weight of array is less then equal to w then 
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]); // assign max of value to k[i][j].
           else
                 K[i][w] = K[i-1][w]; // else assign this value to k[i][w].
       }
   }
 
   return K[n][W]; // return last row and col of that matrix as a result of 0-1 knapsack. 
}
 
int main()
{
    int val[maxi];
    int wt[maxi];
    int  W,n;
    
    cout<<"Enter the maximum weight of knapsack : ";
    cin>>W;
    cout<<"\n Enter no of items present : ";
    cin>>n;
    cout<<"\n Enter the values(profit) of each item : "<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>val[i];
    }
    cout<<"\n Enter the weight of each item : "<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>wt[i];
    }
    
    cout<<"Answer is-"<<knapSack(W, wt, val, n)<<endl;
    return 0;
}


/*

OUTPUT:

tony@tony-HP-Pavilion-g6-Notebook-PC:$ g++ b3.cpp
tony@tony-HP-Pavilion-g6-Notebook-PC:$ ./a.out
Enter the maximum weight of knapsack : 50

Enter no of items presents : 3

Enter the values(profit) of each item : 
60
100
120

Enter the weight of each item : 
10
20
30

Answer is- 220
tony@tony-HP-Pavilion-g6-Notebook-PC:$ g++ B3.cpp
tony@tony-HP-Pavilion-g6-Notebook-PC:$ ./a.out
Enter the maximum weight of knapsack : 10

 Enter no of items present : 4

 Enter the values(profit) of each item : 
10
40
30
50

 Enter the weight of each item : 
5
4
6
3
Answer is-90
tony@tony-HP-Pavilion-g6-Notebook-PC:$ 

*/




/*
#include<iostream>

using namespace std;
class knap
{
	float pro[20],wt[20];
	int mw,n,ub,v[20],k;
	int wt1,pt;

public:
	knap()
	{
		k=-1;
		wt1=pt=0;
	}
	int getdata();
	int getubound();
	int getleastcost();
	int knapsack();
	int display();
};

int knap::getdata()           // get data function.
{
	cout<<"\nenter the number of items";
	cin>>n;
	
	cout<<"\nenter the values";
	for(int i=0;i<n;i++)
	{
		cout<<"\nenter the weight";
		cin>>wt[i];
		cout<<"\nenter the profit";
		cin>>pro[i];
	}
	
	cout<<"\nenter the maximum weight";
	cin>>mw;
	return 0;
}

int knap::display()			 // display data function.
{
	cout<<"\nThe solution vector is:";
	for(int i=0;i<n;i++)
	{
		cout<<"";
		cout<<v[i];
			
	}
	cout<<"\nAnd the cost is"<<pt;
	return 0;
}
int knap::getubound()     // to set the upper bound in each node.
{
	for(int i=k+1;i<n;i++)
	{
		if(wt1+wt[i]<=mw)
		{
			wt1=wt1+wt[i];
			pt=pt+pro[i];		
				
		}
	}
	return pt;
}

int knap::getleastcost()  // to get the minimum cost .
{
	for(int i=k+1;i<n;i++)
	{	wt1=wt1+wt[i];
		if(wt1<=mw)
		{
			pt=pt+pro[i];		
				
		}
		else
		{
			return (pt+((1-((wt1-mw)/wt[i]))*pro[i]));
		}
	}
	return pt;
}

int knap::knapsack()
{
	int l=0;
	int ub1=0,ub2=0,c1=0,c2=0;
	int wt3=0,pt3=0;

	while(l<n)
	{
		wt3=wt1;
		pt3=pt;
		ub1=getubound();
		wt1=wt3;
		pt=pt3;
		c1=getleastcost();
		wt1=wt3;
		pt=pt3;
		k=l;
		ub2=getubound();
		wt1=wt3;
		pt=pt3;
		c2=getleastcost();
		wt1=wt3;
		pt=pt3;
		
		if(ub1>ub2)
		{
			v[l]=1;
			wt1=wt1+wt[l];
			pt=pt+pro[l];
	
		}
		else
		{
			v[l]=0;
		}
		l++;
		ub1=ub2=c1=c2=0;
	}
	display();
	return 0;
}

int main()
{
	knap p;
	p.getdata();
	p.knapsack();
	return 0;
}

output:

tony@tony-HP-Pavilion-g6-Notebook-PC:~/Music/CL1$ g++ B3_0-1\ Knapsack.cpp 
tony@tony-HP-Pavilion-g6-Notebook-PC:~/Music/CL1$ ./a.out

enter the number of items3

enter the values
enter the weight8

enter the profit32

enter the weight12

enter the profit24

enter the weight6

enter the profit6

enter the maximum weight15

The solution vector is:101
And the cost is38
tony@tony-HP-Pavilion-g6-Notebook-PC:~/Music/CL1$ 


*/
