#include<iostream>
using namespace std;

class node
{
	int lower_bound,upper_bound,n,profit[10],weight[10],M,object_no,in_ex;		//8
	public:
		node();
		void getData();
		void displayData();
		int u_bound(int cp,int cw,int k,int M);
		int bound(int cp,int cw,int k,int M);
		void LCBB();
			
};
//CONSTRUCTOR
node :: node()
{
	lower_bound = upper_bound = object_no = 0;
	n = 0;
	M = 0;
	for(int i=0;i<10;i++)
	{
		profit[i] = 0;
		weight[i] = 0;
	}
}
//ACCEPT DATA
void node :: getData()
{
	cout<<"\nEnter the number of objects: ";
	cin>>n;
	cout<<"\nEnter the objects and corresponding profit:- ";
	for(int i=1;i<=n;i++)
	{
		cout<<"\nWeight["<<i<<"] "<<"Profit["<<i<<"]=> ";
		cin>>weight[i]>>profit[i];
	}
	cout<<"\nEnter knapsack capacity: ";
	cin>>M;
}
//DISPLAY ACCEPTED DATA
void node :: displayData()
{
	cout<<"\nDATA: ";
	cout<<"\nWeight: ";
	for(int i=1;i<=n;i++)
	{
		cout<<weight[i]<<"  ";
	}
	
	cout<<"\nProfit: ";
	for(int i=1;i<=n;i++)
	{
		cout<<profit[i]<<"  ";
	}
}
//LOWER BOUND
int node :: bound(int cp,int cw,int k,int M)
{
	int b,c;
	b = cp;
	c = cw;
	
	for(int i=k+1;i<=n;i++)
	{
		c = c + weight[i];
		if(c < M)
		{
			b = b - profit[i];
		}
		else
		{
			return (b-(1-(c-M)/weight[i])*profit[i]);
		}
	}
	return b;
}
//UPPER BOUND
int node :: u_bound(int cp,int cw,int k,int M)
{
	int b,c;
	b = cp;
	c = cw;
	for(int i=k+1;i<=n;i++)
	{
		if((c + weight[i]) <= M)
		{
			c = c + weight[i];
			b = b - profit[i];
		}
	}
	return b;
}
//LCBB
void node :: LCBB()
{
	int result[10] = {0};
	int wt = 0;
	int pr = 0; 
	int upper = 9999;
	int k = 0;
	node *left,*right,*E;
	
	left = new node();
	right = new node();
	E = new node();

//---------------------------------------------------------------------------	

	E->upper_bound = E->u_bound(0,0,0,M);
	E->lower_bound = E->bound(0,0,0,M);
	E->in_ex = -1;
	E->object_no = 0;
	
	upper = E->upper_bound;

//----------------------------------------------------------------------------
	
	int i = 1;
	while(1)
	{
		k = E->object_no + 1;
		//RIGHT CHILD i.e EXCLUDE

	//-----------------------------------------------------------
 
		right->upper_bound = u_bound(pr,wt,k,M);
		right->lower_bound = bound(pr,wt,k,M);
		right->in_ex = 0;
		right->object_no = k;
		
		if(right->upper_bound < upper)
		{
			upper = right->upper_bound;
		}
		
	//------------------------------------------------------------
 
		//LEFT CHILD i.e INCLUDE
		left->in_ex = 1;
		left->object_no = k;
		
		if(wt + weight[k] <= M)
		{
			left->upper_bound = u_bound(pr-profit[k],wt+weight[k],k,M);
			left->lower_bound = bound(pr-profit[k],wt+weight[k],k,M);
		}
		else
		{
			E->upper_bound = pr;
			left->lower_bound = pr;
		}
		
	//---------------------------------------------------------------- 
	
		if(left->lower_bound <= right->lower_bound && left->upper_bound <= right->upper_bound)
		{
			E = left;
		}
		else
		{
			E = right;
		}
	
 	//------------------------------------------------------------------
 
		
		i++;
		
		if(E->in_ex == 1)
		{
			result[i-1] = E->in_ex;
			pr = pr - profit[E->object_no];
			wt = wt + weight[E->object_no];
		}
	
  	//-------------------------------------------------------------------
	
		if(E->object_no == n)
		{
			break;
		}
	}//end of while loop
	
	cout<<"\nSolution vector: ";
	for(int l=1;l<=n;l++)
	{
		cout<<"  "<<result[l];
	}
	cout<<"\nMaximum Profit is: "<<-(E->lower_bound);
	cout<<endl;
}
//MAIN FUNCTION
int main()
{
	node n1;
	n1 = node();
	
	n1.getData();
	n1.displayData();
	n1.LCBB();
	return 0 ;
}
