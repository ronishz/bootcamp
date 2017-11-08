#include<iostream>
#include<math.h>
using namespace std;

int main()
	{
	int i1, i2, t4, n, flag, countI = 1, nClusters, nAttrs;
	
	cout<<"Enter Number of Clusters: ";
	cin>>nClusters;
	cout<<"Enter Number of Attributes: ";
	cin>>nAttrs;
	cout<<"Enter Number of Entries: ";
	cin>>n;
    
	float k0[n][nAttrs];
	float k1[nClusters][n][nAttrs];
    
	float t1[nClusters],t2[nAttrs];
	int count[nClusters];
	
	float m[nClusters][nAttrs];	//initial means
	float om[nClusters][nAttrs];    //old means
	
	cout<<"\nEnter "<<n<<" entries of "<<nAttrs<<" Attributes:\n";
	for(i1=0;i1<n;i1++)
	{
		for(int i = 0; i < nAttrs; i++)
			cin>>k0[i1][i];
	}
	
	for(int i = 0; i < nClusters; i++){
		cout<<"\nEnter initial centroid "<<i+1<<" with "<<nAttrs <<" attributes:";
		for(int j = 0; j < nAttrs; j++)
			cin>>m[i][j];
	}
	
	do
	{
		//saving old means
		for(int i = 0; i < nClusters; i++){
			for(int j = 0; j < nAttrs; j++)
				om[i][j] = m[i][j];
			count[i] = 0;
		}
		
		//creating clusters
		for(i1=0;i1<n;i1++) {
		   	//calculating distance to centroids
			for(int i = 0; i < nClusters; i++){
				float tmp = 0;//euclidean distance
				for(int j = 0; j < nAttrs; j++)
					tmp += (k0[i1][j] - m[i][j]) * (k0[i1][j] - m[i][j]);
				t1[i] = sqrt(tmp);
			}
		
			int min=0;
			//near to min_th centroid
			for(int i = 1; i < nClusters; i++)
				if(t1[i]<t1[min])
					min = i;
					
			for(int i = 0; i < nAttrs; i++)
				k1[min][count[min]][i]=k0[i1][i];
			count[min]++;
		}
		
		//calculating new centroid
		for(int i = 0; i < nClusters; i++){
			for(int j = 0; j < nAttrs; j++)
				t2[j]=0;
			for(t4=0; t4<count[i]; t4++) {
				for(int j = 0; j < nAttrs; j++)
					t2[j] += k1[i][t4][j];
			}
			for(int j = 0; j < nAttrs; j++)
				m[i][j]=t2[j]/count[i];
		}

		//printing clusters
		cout<<"\nIteration "<<countI++<<":"<<endl;
		for(int i = 0; i < nClusters; i++) {
			int j;
			cout<<"\nCluster "<<i+1<<":";
			for(t4=0;t4<count[i];t4++) {
				cout<<"\n( ";
				for(j = 0; j < nAttrs-1; j++)
					cout<<k1[i][t4][j]<<", ";
				cout<<k1[i][t4][j]<<" )";
			}
			cout<<"\nCentroid "<<i+1<<"= ( ";
			
			for(j = 0; j < nAttrs-1; j++)
				cout<<m[i][j]<<", ";
			cout<<m[i][j]<<" )";
		}
			cout<<"\n -------------\n";
		
		for(int i = 0; i < nClusters; i++){
			for(int j = 0; j < nAttrs; j++){
				if(m[i][j]==om[i][j])
					flag = 0;
				else{
					flag = 1;
					break;
				}
			}
		}
	}while(flag);

	cout<<"\nFinal Clusters created are:";
	for(int i = 0; i < nClusters; i++){
		int j;
		cout<<"\n\nCluster "<<i+1<<":";
		for(t4=0;t4<count[i];t4++)
		{
			cout<<"\n( ";
			for(j = 0; j < nAttrs-1; j++)
				cout<<k1[i][t4][j]<<", ";
			cout<<k1[i][t4][j]<<" ) ";
		}
	}
	cout<<endl;

	//ending
	return 0;
}


/* OUTPUT

student@B4L0106:~$ g++ -o kMeans kMeans.cpp 
student@B4L0106:~$ ./kMeans 
Enter Number of Clusters: 2
Enter Number of Attributes: 2
Enter Number of Entries: 4

Enter 4 entries of 2 Attributes:
1 1
2 1
4 3
5 4

Enter initial centroid 1 with 2 attributes:1 1

Enter initial centroid 2 with 2 attributes:2 1

Iteration 1:

Cluster 1:
( 1, 1 )
Centroid 1= ( 1, 1 )
Cluster 2:
( 2, 1 )
( 4, 3 )
( 5, 4 )
Centroid 2= ( 3.66667, 2.66667 )
 -------------

Iteration 2:

Cluster 1:
( 1, 1 )
( 2, 1 )
Centroid 1= ( 1.5, 1 )
Cluster 2:
( 4, 3 )
( 5, 4 )
Centroid 2= ( 4.5, 3.5 )
 -------------

Iteration 3:

Cluster 1:
( 1, 1 )
( 2, 1 )
Centroid 1= ( 1.5, 1 )
Cluster 2:
( 4, 3 )
( 5, 4 )
Centroid 2= ( 4.5, 3.5 )
 -------------

Final Clusters created are:

Cluster 1:
( 1, 1 ) 
( 2, 1 ) 

Cluster 2:
( 4, 3 ) 
( 5, 4 ) 
student@B4L0106:~$  

*/
