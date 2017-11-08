#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    int n,n_clusters,n_attr,sum,min,i1=1,flag;
    cout<<"Number of elements\n";
    cin>>n;
    
    cout<<"Number of attr's\n";
    cin>>n_attr;
    
    cout<<"Number of clusters\n";
    cin>>n_clusters;
    
    float k1[n][n_attr];   //for elements
    float k2[n_clusters][n][n_attr];  //for clusters & its Elements
    float mean[n_clusters][n_attr],old_mean[n_clusters][n_attr];   //for clusters mean
    float t1[n_clusters],t2[n_attr];
    int count[n_clusters];
    
    
    cout<<"Enter elements:\n";
    for(int i=0;i<n;i++)
    {   cout<<"Element "<<i+1<<"\n";
        for(int j=0;j<n_attr;j++)
        {
            cin>>k1[i][j];
        }
    }
    
    //enter initial clusters
    
    for(int i=0;i<n_clusters;i++)
    {   cout<<"Cluster "<<i+1<<"\n";
        for(int j=0;j<n_attr;j++)
        {
            cin>>mean[i][j];
        }
    }
    
    do{
        
        //copy mean to old mean
        for(int i=0;i<n_clusters;i++)
        {
            count[i]=0;
            for(int j=0;j<n_attr;j++)
            {
                old_mean[i][j]=mean[i][j];
            }
        }
      
      
        //cluster Elements
        
        for(int i=0;i<n;i++)
        {   
            for(int j=0;j<n_clusters;j++)
            {   float tmp=0;
                for(int k=0;k<n_attr;k++)
                {
                    tmp+=(k1[i][k] - mean[j][k])*(k1[i][k] - mean[j][k]);
                }
                t1[j]=sqrt(tmp);
            }
            
            //find minimum
            min=0;
            for(int j=1;j<n_clusters;j++)
            {
                if(t1[j]<t1[min])
                {
                    min=j;
                }
            }
            
            //add element to its specific cluster
            
            for(int k=0;k<n_attr;k++)
            {
                k2[min][count[min]][k]=k1[i][k];
            }
            count[min]++;
            
        }
        
        //new centroid
        for(int i=0;i<n_clusters;i++)
        {  
            for(int j=0;j<n_attr;j++)
            {
                t2[j]=0;
            }
            
            
            for(int j=0;j<count[i];j++)
            {   
                for(int k=0;k<n_attr;k++)
                {
                    t2[k]+=k2[i][j][k];
                }
            }
            
            for(int j=0;j<n_attr;j++)
            {
                mean[i][j]=t2[j]/count[i];
            }
            
        }
        
        
        
        //printing clusters
        cout<<"\nIteration "<<i1++<<"\n";
        for(int i=0;i<n_clusters;i++)
        {
            int k;
            cout<<"Cluster "<<i+1<<":\n";
            for(int j=0;j<count[i];j++)
            {
                cout<<"(";
                for(k=0;k<n_attr-1;k++)
                {
                    cout<<k2[i][j][k]<<" ,";
                }
                cout<<k2[i][j][k]<<")\n";
            }
            
             //printing centroids
            cout<<"centroid "<<i+1<<"\n";
            cout<<"(";
            for(j=0;j<n_attr-1;j++)
            {
                cout<<mean[i][j]<<", ";
            }
            cout<<mean[i][j]<<" )\n";
        }
        
        cout<<"-------------";
        
       

        
        
        //checking old mean & new mean
        
         for(int i=0;i<n_clusters;i++)
        {
            for(int j=0;j<n_attr;j++)
            {
                if(old_mean[i][j]==mean[i][j])
                {
                    flag=0;
                }
                else{
                    flag=1;
                    break;
                }
            }
        }
        
    }while(flag);

        cout<<"\nfinal clusters:\n";
        for(int i=0;i<n_clusters;i++)
        {
            cout<<"Cluster "<<i+1<<":\n";
            for(int j=0;j<count[i];j++)
            {
                cout<<"(";
                for(int k=0;k<n_attr-1;k++)
                {
                    cout<<k2[i][j][k]<<" ,";
                }
                cout<<k2[i][j][n_attr-1]<<")\n";
            }
        }
        return 0;
    
}
