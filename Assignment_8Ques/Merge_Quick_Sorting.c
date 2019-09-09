#include<stdio.h>
#include<unistd.h>
#include<string.h>
//#include<process.h>

int arr[100];

// -----------------------------------------------------------
int Partition(int beg, int end){
	int i=beg,j=end;
	int p;
	p=beg;

	int val=p;
	while(i<j){
		while(arr[p]>=arr[i] && i<end){
			i++;
		}
		while(arr[p]<arr[j] && j>beg){
			if(j==p+1 && i<=p)j=p-1;
			//if(j!=beg)j--;
			else j--;
			
		}
		if(i<j){
			int temp = arr[i];
			arr[i]=arr[j];
			arr[j]=temp;
		}	
	}
	int temp = arr[p];
	arr[p]=arr[j];
	arr[j]=temp;
	val=j;
	return val;
}

void QuickSort(int beg, int end){
	if(beg<end){
		int j = Partition(beg, end);
		int pidq = vfork();
		if(pidq == 0)
		{ 
			QuickSort(beg, j-1);
			exit(0);
		}
		else if(pidq > 0) QuickSort(j+1, end);
	}
}

// -----------------------------------------------------------
void MergeArray(int beg, int mid, int end) 
{ 
    int n1 = mid - beg + 1; 
    int n2 =  end - mid; 

    int L[n1], R[n2]; 

    for (int i = 0; i < n1; i++) L[i] = arr[beg + i]; 
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1+ j]; 

    int i=0, j=0, k=beg;
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

void MergeSort(int beg, int end) 
{ 
    if (beg < end) 
    { 
        int mid = (beg+end)/2; 
		
		int pidm = vfork();
		if(pidm == 0)
		{
			MergeSort(beg, mid); 
			exit(0);
		}
        else if(pidm > 0)
        {
        	MergeSort(mid+1, end);
        	wait(NULL);
        	
        	MergeArray(beg, mid, end); 
        } 
    } 
}
// ----------------------------------------------------------- 

int main()
{
	printf("------------------------------------ MERGE AND QUICK SORTING --------------------------------------\n");

	int size = 0;
	printf("Enter size of array: ");
	scanf("%d", &size);

	printf("Enter the array: ");
	//int arr[size];
	for(int i=0;i<size;i++)
	{
		scanf("%d", &arr[i]);
	}

	int pid = fork();

	if(pid == 0)
	{
		printf("Merge Sorted: ");
		
		MergeSort(0, size-1);

		for(int i=0;i<size;i++) printf("%d ", arr[i]);

		printf("\n");
		return 0;
	}
	else if(pid > 0)
	{
		wait(NULL);
		printf("Quick Sorted: ");
		
		QuickSort(0, size-1);

		for(int i=0;i<size;i++) printf("%d ", arr[i]);

		printf("\n");
		printf("------------------------------------ MERGE AND QUICK SORTING --------------------------------------\n");
		return 0;
	}

	
	
}
