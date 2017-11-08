#include<omp.h>
#include<iostream>
using namespace std;
int part(int*, int, int);
void qs(int*, int, int);

int main(){
	int n;
	cout<<"\nEnter number of elements: ";
	cin>>n;
	int arr[n];
	for(int i=0;i<n;i++){
		cout<<"\nEnter element "<<i+1<<" : ";
		cin>>arr[i];
	}
	cout<<"\n>>>>>>>> Sorted Elements";
	qs(arr,0,n-1);
	for(int i=0;i<n;i++){
		cout<<"\nElement "<<i+1<<" is: "<<arr[i];
		
	}
	cout<<"\n";
	return 0;
}

int part(int arr[], int low, int high){
	int piv=0;
	int i=0;
	int j=0;
	piv=arr[high];
	i=low-1;
	int tmp;
	for(j=low;j<high;j++){
		if(arr[j]<=piv){
			i++;
			tmp=arr[j];
			arr[j]=arr[i];
			arr[i]=tmp;
		}
	}
	tmp=arr[high];
	arr[high]=arr[i+1];
	arr[i+1]=tmp;
	return (i+1);
}

void qs(int arr[], int low, int high){
	int q=0;
	int k=0;
	if(low<high){
		q=part(arr,low,high);

		cout<<"\nPivot at "<<q<<" by thread "<<k;
		#pragma omp parallel sections
		{
			#pragma omp section
			{
				k++;
				cout<<"TID: "<<omp_get_thread_num();
				qs(arr,low,q-1);
			}
			#pragma omp section
			{
				k++;
				cout<<"TID: "<<omp_get_thread_num();
				qs(arr,q+1,high);
			}
		}
	}
}	
