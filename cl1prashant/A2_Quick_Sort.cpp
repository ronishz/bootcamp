/*

Aim: Using Divide and Conquer Strategies design a class for Concurrent Quick Sort using C++.

*/


#include<iostream>
#include<ctime> // for calculating execution time of program.
#include<omp.h> // for running code on  different processors.
using namespace std;

class quick
{
public:
    void quicksort(int *arr, int n)
    {
        int j=0,k=0;
        int *arrl=new int[n];   // New is used to allocate block of memory 
        int *arrh=new int[n];   // New is used to allocate block of memory 
        int p=0;
        int pivot=arr[0];

        if(n==0 || n==1)
        {
        	return;
		}
		
        #pragma omp parallel for
        for(int i=1;i<n;i++)   
        {
            int element=arr[i];
            if(element<=pivot)    // elements less then pivote will be store in lower array.
            {
                arrl[j++]=arr[i];
            }
            else				// elements greater then pivote will be store in higher array.
            {
                arrh[k++]=arr[i];
            }
        }

        #pragma omp section
        quicksort(arrl,j);   // calling quick sort for lower array.
        for(int i=0;i<j;i++)
        {
            arr[p++]=arrl[i];   //putting Lower array to its place.
        }
        arr[p++]=pivot;   // putting pivot value to its correct position.

        #pragma omp section
        quicksort(arrh,k);   // calling quick sort for higher array.
        for(int i=0;i<k;i++)
        {
            arr[p++]=arrh[i];   //putting Higher array to its place.
        }
        delete(arrl);     // Deallocates a block of memory.
        delete(arrh);     // Deallocates a block of memory.s
    }

};

int main()
{
    quick q;
    int n;
    cout<<"\nEnter the number of elements : ";
    cin>>n;
    int arr[n];
    cout<<"\nEnter the array : "<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
   
    int start_s=clock(); // starting the clock
    
    q.quicksort(arr,n);
    
    cout<<"The sorted array is : "<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<", ";
    }
        
    int stop_s=clock(); // stoping the same clock
    cout << "\nTime of Exection : " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 <<"seconds"<< endl; // for display the time of exection.
    return 0;

}

/*

OUTPUT:

tony@tony-HP-Pavilion-g6-Notebook-PC:~$ g++ quicksort.cpp
tony@tony-HP-Pavilion-g6-Notebook-PC:~$ ./a.out

 Enter the number of elements : 5

 Enter the Elements : 88
66
44
33
77

The sorted elements are : 
33  44  66  77  88  
tony@tony-HP-Pavilion-g6-Notebook-PC:~$ ./a.out

 Enter the number of elements : 7

 Enter the Elements : 11
22
44
33
12
32
76

The sorted elements are : 
11  12  22  32  33  44  76  
tony@tony-HP-Pavilion-g6-Notebook-PC:~$ 

*/
