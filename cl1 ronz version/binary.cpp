#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<unistd.h>
#include<omp.h>
#include <algorithm>
using namespace std;

class binarySearch{
  int a[100],n,low,high,key,op;
public:
    void getdata();
    int b_r(int *a,int low,int high,int key);
    void b_nr(int *a,int low,int high,int key);
    
};

int binarySearch::b_r(int *a,int low,int high,int key)
{
    int mid=(low+high)/2;
    if(key==a[mid])
    {
        cout<<"Key found at location "<<mid+1<<"\n";
        return 0;
    }
    else if(key>a[mid])
    {
        low=mid+1;
    }
    else if(key<a[mid])
    {
        high=mid-1;
    }
    
    if(low>high){
        cout<<"key not found\n";
        return 0;
    }
    
    b_r(a,low,high,key);
}

void binarySearch::b_nr(int *a,int low,int high,int key)
{
    int mid;
    while(low<high)
    {
        mid=(low+high)/2;
        if(key==a[mid])
        {
            cout<<"Key found at location "<<mid+1<<"\n";
            return;
        }
        else if(key>a[mid])
        {
            low=mid+1;
        }
        else if(key<a[mid])
        {
            high=mid-1;
        }
        
    }
    cout<<"key not found\n";
}


void binarySearch::getdata()
{
    cout<<"Enter no of elements\n";
    cin>>n;
    low=0;
    high=n-1;
    double start,end;
    
    for(int i=0;i<n;i++)
    {
        a[i]=rand()%100;
        cout<<a[i]<<" ";
    }
    cout<<"\n";
    sort(a,a+n);
    
    cout<<"sorted array-\n";
    
    for(int i=0;i<n;i++)
    {
        cout<<a[i]<<" ";
    }
    
    cout<<"1.Recursive,2.Non-Recursive\n";
    cin>>op;
    cout<<"Enter key to search\n";
    cin>>key;
    
    if(op==1){
        start=omp_get_wtime();
        b_r(a,low,high,key);
        end=omp_get_wtime();
    }
    else if(op==2)
    {
        low=0;
        high=n-1;
        start=omp_get_wtime();
        b_nr(a,low,high,key);
        end=omp_get_wtime();
    }
    
    cout<<"time: "<<end-start<<"\n";
    
    
    
}

int main()
{
    binarySearch b;
    b.getdata();
    
    
    return 0;
}
