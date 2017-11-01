/*

Aim: Using Divide and Conquer Strategies design a function for Binary Search using C++/ Java/ Python/Scala.

O(1) in case of iterative implementation. In case of recursive implementation, O(Logn) recursion call stack space.

how many times can you divide N by 2 until you have 1 ==> 1 = N / 2^(x)

*/

#include<iostream>  
#include<stdlib.h>  
using namespace std;  

class BinarySearch  
{  
    public:  
    int search(int *arr, const int len, const int s)  
    {  
        int lower = 0;  
        int upper = len - 1;  
        int middle = (lower+upper)/2;  
        while (lower <= upper)  
        {  
            if (arr[middle] == s)  // If the element is present at the middle itself
                return middle;  
            else if (arr[middle] > s)  // If element is smaller than mid, then it can only be present in left subarray
                upper = middle-1;  
            else  				 // Else the element can only be present in right subarray
                lower = middle+1;  
                
            middle = (lower + upper)/2;  
        }  
        return -1;  
    }  
    
    void quicksort(int *arr, const int size)  
    {  
        if(size == 1 || size == 0)  
            return; 
             
        int pivot = arr[0];  
        int *arrl = new int[size];  // New is used to allocate block of memory 
        int *arrh = new int[size];  // New is used to allocate block of memory
        int j=0, k=0;  
        for(int i=1; i<size; i++)  
        {  
            int element = arr[i];  
            if( element <= pivot )  // elements less then pivote will be store in lower array.
                arrl[j++] = element;  
            else  				   // elements greater then pivote will be store in higher array.
                arrh[k++] = element;  
        }  
        quicksort(arrl, j);  // calling quick sort for lower array.
        int p=0;  
        for(int i=0; i<j; i++)  
            arr[p++] = arrl[i];  //putting Lower array to its place.
            
        arr[p++] = pivot;  // putting pivot value to its correct position.
        quicksort(arrh, k);  // calling quick sort for lower array.
        
        for(int i=0; i<k; i++)  
            arr[p++] = arrh[i];  //putting higher array to its place.
            
        delete(arrl); // Deallocates a block of memory.
        delete(arrh); // Deallocates a block of memory.
    }  
}b;  

int main()  
{  \
    int len, s;  
    cout<<"\n\nEnter size of an array: ";  
    cin>>len;  
    int arr[len];  
    cout<<"\nEnter elements of sorted array: ";  
    for(int i=0; i<len; i++)  
        cin>>arr[i];  
        
    b.quicksort(arr, len);  
    
    cout<<"\nSorted array: [ ";  
    for(int i=0; i<len; i++)  
        cout<<arr[i]<<" ";  
    cout<<"]";  
    
    cout<<"\n\nEnter element to be searched: ";  
    cin>>s;  
    
    int result = b.search(arr, len, s);  
    
    if(result != -1)  
        cout<<"\n\n"<< s <<" Element is found at index "<< result <<".\n\n";  
    else  
        cout<<"\nElement is not found ";  
    return 0;  
}  


/*

Output:
tony@tony-HP-Pavilion-g6-Notebook-PC:~$ g++ binary.cpp
tony@tony-HP-Pavilion-g6-Notebook-PC:~$ ./a.out

Enter size of an array: 5

Enter elements of sorted array: 12
34
56
67
78

Sorted array: [ 12 34 56 67 78 ]

Enter element to be searched: 56


56 Element is found at index 2.

tony@tony-HP-Pavilion-g6-Notebook-PC:~$ ./a.out

Enter size of an array: 5

Enter elements of sorted array: 34
23
12
87
98

Sorted array: [ 12 23 34 87 98 ]

Enter element to be searched: 44

Element is not found 

tony@tony-HP-Pavilion-g6-Notebook-PC:~$ 
*/
