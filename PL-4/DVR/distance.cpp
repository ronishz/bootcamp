#include<stdio.h>
#include<iostream>
using namespace std;                                            
struct node
{
    unsigned dist[5];
    unsigned from[5];
}DVR[5];

char conv(int a)
{
if(a==0)
	return 'A';
if(a==1)
	return 'B';
if(a==2)
	return 'C';
if(a==3)
	return 'D';
if(a==4)
	return 'E';

}
int main()
{
    cout<<"\t\tDISTANCE VECTOR ROUTING ALGORITHM:";
    int costmat[5][5];
    int nodes, i, j, k;
    cout<<"\nEnter the number of nodes : ";
    cin>>nodes; //Enter the nodes
    cout<<"Enter the cost matrix : \n" ;
    for(i = 0; i < nodes; i++)
     {
        for(j = 0; j < nodes; j++)
        {
            cin>>costmat[i][j];
            costmat[i][i] = 0;
            DVR[i].dist[j] = costmat[i][j]; //initialise the distance equal to cost matrix
            DVR[i].from[j] = j;
        }
    }
            for(i = 0; i < nodes; i++) //We choose arbitary vertex k and we calculate thedirect distance from the node i to k using the cost matrix and add the distance from k to node j
            	{
		for(j = 0; j < nodes; j++)
			{
            		for(k = 0; k < nodes; k++)
	                	{
				if(costmat[i][k]<999 && costmat[i][k] != 0) //k directly connected to i
                			{   
					if(DVR[i].dist[j] >= DVR[i].dist[k] + DVR[k].dist[j])
						{
                    				DVR[i].dist[j] = DVR[i].dist[k] + DVR[k].dist[j];
						if(i != k)						
							DVR[i].from[j] = k;
						else
							DVR[i].from[j] = j;
						}
					}
				}
			}
		}
        for(i = 0; i < nodes; i++)
        {
            cout<<"\n\n For router: "<<conv(i);
            cout<<"\t\nNode\tNext hop\tcost ";
            for(j = 0; j < nodes; j++)
                cout<<"\t\n"<<conv(j)<<"\t"<<conv(DVR[i].from[j])<<"\t\t"<<DVR[i].dist[j];
        }
    cout<<" \n\n ";
    return 0;
}
