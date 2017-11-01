#include <iostream>
#include <stdlib.h>
#include<math.h>
#include<vector>
using namespace std;

int min(int arr[], int maxIndex)   // return a minimum value from an array given as an input parameter.
{
	int min=100;
	for(int i=0;i<maxIndex;i++)
	{
		if(arr[i]<min)
		{
			min=arr[i];
		}
	}
	return min;
}

int indexOf(int number,int arr[], int maxIndex) // return the index of the no an array
{
	int index;
	for(int i=0;i<maxIndex;i++)
	{
		if(number==arr[i])
		{
			index=i;
			break;	
		}
	}
	return index;
}

int mean(vector<int> vc ) // return the mean of all the elements present in vector array
{
	int sum=0;
	for(int i=0;i<vc.size();i++)
		sum=sum+vc[i];
		return sum/vc.size();
}

void show(vector<int> vc ) // display the elements present in vector array
{
	for(int i=0;i<vc.size();i++)
	{
		cout<<vc[i]<<",";	
	}
}

bool isEqual(int arr1[], int arr2[], int maxIndex) // to check if two arrays are equal or not 
{
	for(int i=0;i<maxIndex;i++)
	{
		if(arr1[i]!=arr2[i])
		return false;
	}
	return true;
}

int main()
{
	int noOfItems;
	int k;	
	cout<<"Total numbers you want enter (value of n: )?"<<endl;
	cin>> noOfItems;
	cout<<"Enter value of K:"<<endl;
	cin>> k;
	int cluster[k];
	int oldCluster[k];
	int objects[noOfItems];
	int row[k];
	vector< vector<int> > groups;
	
	for(int i=0;i<noOfItems;i++)
	{
		cout<<"Enter Value "<<(i+1)<<endl;      
		cin>>objects[i];					// storing the values of arrays
		if(i<k)
		{
			cluster[i]=objects[i];         // storing the array to temp
		}
	}
	
	for(int i=0;i<k;i++)  // adding k values to the end of the "groups" vector (array).
	{
		vector<int> newGroup;             // creating a temp vector. 
		groups.push_back(newGroup);		  // push k values at end of the array. 
	}
	
	int iter =1;     // iter for counting no of interation taken by this algorithm to build output.
	do
	{
		for(int i=0;i<noOfItems;i++)
		{
			for(int j=0;j<k;j++)
			{
				row[j] = abs(cluster[j]-objects[i]); // Absolute value
			}	
	    		groups[indexOf(min(row,k),row,k)].push_back(objects[i]);  // pushing remaning values in the array 
		}
		
		for(int j=0;j<k;j++)
		{
	     	if(!groups[j].empty()) // if groups is not empty then
			{
				oldCluster[j]=cluster[j];  // store input array i.e. cluster into temp variable i.e oldCluster.
				cluster[j] = mean(groups[j]); //and new cluster will contain the mean of groups
			}
		}
		
		if(!isEqual(oldCluster,cluster,k)) // if oldCluster and cluster are not equal then
		{
			for(int i=0;i<k;i++)
				groups[i].clear(); //delete 1st k items from the group.
		}
		iter++;	// increment the count of iter.
	
	}while(!isEqual(oldCluster,cluster,k)); // this will work till oldCluster and cluster are not equal.
	
	cout<<"\n\n";
	for(int i=0;i<k;i++)
	{
		cout<<"C"<<(i+1)<<" : "<<cluster[i]<<endl;   // printing clusters and their values.
	}
	for(int i=0;i<k;i++)
	{
		cout<<"\n\nGroup "<<(i+1)<<" : \n"<<endl;    // printing Groups and their values.
		show(groups[i]);
	}
	cout<<"\n\nNumber of Iterations "<<iter<<endl;   // displaying no of times clusters changed and values are edited
	
	return 0;
}

/*
Output :-

[root@localhost cl1]# g++ kmeans.cpp
[root@localhost cl1]# ./a.out
Total numbers you want enter?
3
Enter value of K:
4 5 6
Enter Value 1
Enter Value 2
Enter Value 3
2 3 4

C1 : 5
C2 : 6
C3 : 2
C4 : 0
Group 1 : 

5,

Group 2 : 

6,

Group 3 : 

2,

Group 4 : 

Number of Iterations 2
[root@localhost cl1]# 
*/


/*

#include<iostream>
using namespace std;
class mean
{
	float X[10],Y[10],k,n1,p[10],q[10],dist[10],cnt[10];
	float m[10],n[10],total1[10],total2[10];
	int flag[10],flag1,f,prev[10];
	public:
	void accept();
	void display();
	void kmean();
	int nochange();
};
void mean::accept()                  // to get input from the user 
{
	cout<<"\nEnter Number of cluster : ";
	cin>>k;
	cout<<"\nEnter number of objects : ";
	cin>>n1;
	cout<<"\nEnter objects values : \n";
	for(int i=0;i<n1;i++)
	{
		cin>>X[i]>>Y[i];
	}
	for(int i=0;i<k;i++)
	{
		cout<<"\nEnter  "<<i+1<<"  centroid : ";
		cin>>m[i]>>n[i];
	}
}
void mean::display()                 // displaying the output as clusters 
{
	for(int j=0;j<k;j++)
	{
		cout<<"\nCluster "<<j+1<<"\n";
		for(int i=0;i<n1;i++)
		{
			if(flag[i]==j)
			{		
				cout<<"X["<<X[i]<<"]["<<Y[i]<<"]\n";
			}
		}
	}
	cout<<"\n\n";
}
int mean::nochange()
{
	int cc;
	cc=0;
	if(f==1)
	{
		f=0;
		return 1;
	}
	else
	{
		for(int i=0;i<n1;i++)
		{
			if(flag[i]==prev[i])
				cc=cc+1;
		}
		if(cc==n1)
		{
			return 0;
		}		
		else 
			return 1;
	}
}
void mean::kmean()
{
	f=1;
	do
	{
		cout<<"-------------------------------------------------------\n    ";
		for(int j=0;j<k;j++)
		{
		
			cout<<"\t\tM"<<j+1<<"["<<m[j]<<","<<n[j]<<"]   ";
		
		}
		cout<<"\n-------------------------------------------------------\n";
		cout<<"\n";
	
		for(int i=0;i<n1;i++)
		{
			total1[i]=total2[i]=cnt[i]=0;
			prev[i]=flag[i];
		}
	
		int min;
	
		for(int i=0;i<n1;i++)
		{
			min=999;
			cout<<"X"<<i+1<<"["<<X[i]<<","<<Y[i]<<"]\t";
			for(int j=0;j<k;j++)
			{		
				p[i]=X[i]-m[j];
				if(p[i]<0)
				{				//if p[i] is -ve then make it +ve
					p[i]=p[i]*(-1);
				}
				
				q[i]=Y[i]-n[j];
				if(q[i]<0)				//if q[i] is -ve then make it +ve
				{
					q[i]=q[i]*(-1);
				}
				
				dist[i]=p[i]+q[i];		//x2[i]-x1[i]+y2[i]-y1[i]
			
				cout<<"\t"<<dist[i]<<"\t";
				if(dist[i]<min)
				{
					min=dist[i];        // finding min distance value form dist array. 
 					flag[i]=j; 			// setting cluster value to ith flag. 
				}		
			}
			cout<<"\tM"<<flag[i]+1;
			cout<<"\n";
		}
	
		if(f==1)
		{
			for(int i=0;i<n1;i++)
			{
				prev[i]=flag[i];   // setting every flag value to a temp array.
			}
		}

		cout<<"-------------------------------------------------------\n";
	
		for(int i=0;i<n1;i++)
		{
			for(int j=0;j<k;j++)
			{
				if(flag[i]==j)
				{
					total1[j]=total1[j]+X[i]; // making clusters for x1
					total2[j]=total2[j]+Y[i]; // making clusters for x2 
					cnt[j]=cnt[j]+1;         // count++ . 
				}
			}
		}	
	
		for(int j=0;j<k;j++)
		{
			m[j]=total1[j]/cnt[j];    // finding mean of total to assign this to centroid for x1
			n[j]=total2[j]/cnt[j];    // finding mean of total to assign this to centroid for y2
		}
	
		display();	// display the output array and clusters and centroid.
		flag1=nochange(); // change flag1 value as nochange() will return 1 or 0  
	}while(flag1);
}

int main()
{

	mean obj;
	obj.accept();
	obj.kmean();

	return 0;
}

/*
output: 
[student@localhost akshada1]$ c++ kalgo.cpp
[student@localhost akshada1]$ ./a.out

Enter Number of cluster: 2

Enter number of objects : 4

Enter objects values : 
1 1
2 5
3 2
4 8

Enter  1  centroid : 1 1

Enter  2  centroid : 3 2
-------------------------------------------------------
    	M1[1,1]   	M2[3,2]   
-------------------------------------------------------

X1[1,1]		0		3		M1
X2[2,5]		5		4		M2
X3[3,2]		3		0		M2
X4[4,8]		10		7		M2
-------------------------------------------------------

Cluster 1
X[1][1]

Cluster 2
X[2][5]
X[3][2]
X[4][8]


-------------------------------------------------------
    	M1[1,1]   	M2[3,5]   
-------------------------------------------------------

X1[1,1]		0		6		M1
X2[2,5]		5		1		M2
X3[3,2]		3		3		M1
X4[4,8]		10		4		M2
-------------------------------------------------------

Cluster 1
X[1][1]
X[3][2]

Cluster 2
X[2][5]
X[4][8]


-------------------------------------------------------
    	M1[2,1.5]   	M2[3,6.5]   
-------------------------------------------------------

X1[1,1]		1.5		7.5		M1
X2[2,5]		3.5		2.5		M2
X3[3,2]		1.5		4.5		M1
X4[4,8]		8.5		2.5		M2
-------------------------------------------------------

Cluster 1
X[1][1]
X[3][2]

Cluster 2
X[2][5]
X[4][8]


[student@localhost akshada1]$ 

*/


*/
