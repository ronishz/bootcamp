#include<stdio.h>
#include<omp.h>

void InsertionSort(int a[],int n);
void BinarySearch(int a[],int bottom,int top,int num);

int main()
{
	int a[20],n,num,i,j,mid, top, bottom;
	double start,finish;
        printf("Enter the number of elements in an array: ");
        scanf("%d", &n);
        printf("\nEnter the elements of array: \n");
        for (i=0;i<n;i++)
        	scanf("%d", &a[i]);
        
        start=omp_get_wtime();
        InsertionSort(a,n);
        	
	printf("\nSorted array is : \n");
        for (i=0;i<n;i++)
        	printf("%d\t",a[i]);
        	
        printf("\n\nEnter number to be searched : ");
        scanf("%d", &num);
       
        top = n - 1;
        bottom = 0;
        BinarySearch(a,bottom,top,num);
        finish=omp_get_wtime();
        printf("\nRequired time is %f seconds.\n", finish - start);
	return 0;
}

void InsertionSort(int a[],int n)
{
	int i,j,temp;
	for(i=1;i<n;i++)
	{ 
		temp=a[i]; 	
		for(j=i-1;j>=0 && a[j]>temp;j--)
	        {
         	   a[j+1]=a[j];
		}
		a[j+1]=temp;
	}
}

void BinarySearch(int a[],int bottom,int top,int num)
{
	int mid,tid;
	while (num != a[mid] && bottom <= top)
	{
		mid = (top + bottom)/2;
		#pragma omp parallel sections
		{
			#pragma omp section
			{	
			tid = omp_get_thread_num();
			printf("Thread %d is checking if required number is less than mid (%d)\n",tid,a[mid]);
			if (num < a[mid])
				top = mid - 1;
			}
			#pragma omp section
			{
			tid = omp_get_thread_num();
			printf("Thread %d is checking if required number is greater than mid (%d)\n",tid,a[mid]);

			if (num > a[mid])
				bottom = mid + 1;
			}
		}
	}
        

        if (num == a[mid])
        	printf("\nThe number is found at index: %d\n", mid);
        else
                printf("\nThe number is not found.\n");
        
}
