#include<iostream>
using namespace std;

class Bins{
	int arr[100],cnt,num;
	public:
		void disp();
		void accept();
		void ins_sort();
		void binary();
};

void Bins::accept(){
	cout<<"\nEnter number of elements: ";
	cin>>cnt;
	
	for(int i=0;i<cnt;i++){
		cout<<"\nEnter element "<<i+1<<" of array: ";
		cin>>arr[i];
	}
	
}	

void Bins::disp(){
	for(int i=0;i<cnt;i++){
		cout<<"\nElement "<<i+1<<" is: "<<arr[i];	
	}
}

void Bins::binary(){
	int i=0,j=0,mid=0,high=0,low=0,flag=0;
	low=0;
	high=cnt-1;
	mid=(low+high)/2;
	cout<<"\nEnter the element to be searched: ";
	cin>>num;
	while(flag==0){
		if(high<low)
		{
			break;
		}
		if(arr[mid]<num){
			low=mid+1;
			mid=(low+high)/2;
		}
		else if(arr[mid]>num){
			high=mid-1;
			mid=(low+high)/2;
		}
		else{
			cout<<"\n>>>>>>>>>>>>>Number found at position: "<<mid+1<<"\n";
			flag=1;
			break;
		}
	}
	if(flag==0){
		cout<<"\n>>>>>>>>>>>>>Not found\n";
	}
}

void Bins::ins_sort(){
	int k, temp;
	for(int i=0;i<cnt;i++){
		for(int j=0;j<cnt;j++){
			if(arr[i]<arr[j]){
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}
	for(int i=0;i<cnt;i++){
		cout<<"\nElement "<<i+1<<" is: "<<arr[i];	
	}
}

int main(){
	Bins b;
	cout<<"\n>>>>>>>>>>>Binary Search:";
	b.accept();
	b.ins_sort();
	cout<<"\nSorted Data is: ";
	b.disp();
	b.binary();
	return 0;
}	
