#include <iostream>
#include <stdlib.h>
#include <omp.h>
#define MAX 100
using namespace std; 

class Quick
{
	int a[MAX];
public:
	int partition(int *a,int low,int high);			//pass pointer for a only in protoype & defination,not while calling
	void quicksort(int *a,int low,int high);		//return type void for quicksort & int for partition
};


void Quick::quicksort(int *a,int low,int high)		//class function defination
{
	int p;										//define outside omp section
	if(low<high)
	{
		omp_set_nested(1);						//to turn on parallelism bit
		omp_set_num_threads(MAX/2);				//set num of threads
		#pragma omp parallel sections			//to execute below block in parallel
		{
			p=partition(a,low,high);
					
			#pragma omp section				//one thread for each section
			{

				cout<<"\nleft part-	pivot index="<<p<<" & thread= "<<omp_get_thread_num()<<"\n";
				quicksort(a,low,p-1);
			}

			#pragma omp section
			{
				cout<<"\nright part-	pivot index="<<p<<" & thread= "<<omp_get_thread_num()<<"\n";
				quicksort(a,p+1,high);
			}		
		}
	}	
}

int Quick::partition(int *a,int low,int high)
{
	int i=low-1;
	int temp;
	int pivot=a[high];					//last element
	for(int j=low;j<=high-1;j++)
	{
		if(a[j]<=pivot)
		{	
			i++;
			temp=a[j];					//swap a[i] & a[j]
			a[j]=a[i];
			a[i]=temp;
		}
	}
	temp=a[i+1];						//insert pivot in correct position
	a[i+1]=a[high];
	a[high]=temp;

	return (i+1);						//return index of pivot
}

int main()
{
	int a[MAX];							//define a[] before creating object,else it'll crash
	int n=MAX;							//esssential 
	
	Quick q;
	
	for(int z=0;z<n;z++)
	{
		a[z]=rand()%20;					//randomly insert numbers from 0 to 20
	}
    //sort(a,a+n);
	cout<<"Un-sorted list-\n";
	for(int z=0;z<n;z++)
	{
		cout<<a[z]<<"\n";
	}

	q.quicksort(a,0,n-1);				//call function first time

	cout<<"sorted list-\n";
	for(int z=0;z<n;z++)
	{
		cout<<a[z]<<"\n";
	}

	return 0;

}
