#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int arrqs[100];
int arrms[100];

struct data
{
	int beg;
	int end;
};
// -----------------------------------------------------------
int Partition(int beg, int end){
	int i=beg,j=end;
	int p;
	p=beg;

	int val=p;
	while(i<j){
		while(arrqs[p]>=arrqs[i] && i<end){
			i++;
		}
		while(arrqs[p]<arrqs[j] && j>beg){
			if(j==p+1 && i<=p)j=p-1;
			//if(j!=beg)j--;
			else j--;
			
		}
		if(i<j){
			int temp = arrqs[i];
			arrqs[i]=arrqs[j];
			arrqs[j]=temp;
		}	
	}
	int temp = arrqs[p];
	arrqs[p]=arrqs[j];
	arrqs[j]=temp;
	val=j;
	return val;
}

void * QuickSort(void * d){
	struct data *dm = d;
	int beg = dm->beg;
	int end = dm->end;

	if(beg<end){
		int j = Partition(beg, end);

		struct data dL;
		dL.beg = beg;
		dL.end = j - 1;
		struct data dR;
		dR.beg = j + 1;
		dR.end = end;

		pthread_t tid[2];
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		pthread_create(&tid[0], &attr, QuickSort, &dL);
		pthread_create(&tid[1], &attr, QuickSort, &dR);

		pthread_join(tid[0], NULL);
		pthread_join(tid[1], NULL);
	}

	pthread_exit(0);
}

// -----------------------------------------------------------
void MergeArray(int beg, int mid, int end) 
{ 
    int n1 = mid - beg + 1; 
    int n2 =  end - mid; 

    int L[n1], R[n2]; 

    for (int i = 0; i < n1; i++) L[i] = arrms[beg + i]; 
    for (int j = 0; j < n2; j++) R[j] = arrms[mid + 1+ j]; 

    int i=0, j=0, k=beg;
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arrms[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arrms[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        arrms[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        arrms[k] = R[j]; 
        j++; 
        k++;
    } 
} 

void * MergeSort(void * d) 
{
	struct data *dm = d;
	int beg = dm->beg;
	int end = dm->end;

    if (beg < end) 
    { 
        int mid = (beg+end)/2;

        struct data dL;
		dL.beg = beg;
		dL.end = mid;
		struct data dR;
		dR.beg = mid + 1;
		dR.end = end;

        pthread_t tid[2];
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		pthread_create(&tid[0], &attr, MergeSort, &dL);
		pthread_create(&tid[1], &attr, MergeSort, &dR);

    	pthread_join(tid[0], NULL);
		pthread_join(tid[1], NULL);
    	
    	MergeArray(beg, mid, end); 
    }
    pthread_exit(0);
}
// ----------------------------------------------------------- 

int main(int argc, char *argv[])
{
	//printf("------------------------------------ MERGE AND QUICK SORTING --------------------------------------\n");

	if(argc < 2) printf("Wrong number of parameters.\n");
	else 
	{
		int n = argc - 1;

		for(int i=0;i<n;i++)
		{
			arrqs[i] = atoi(argv[1 + i]);
			arrms[i] = atoi(argv[1 + i]);
		}

		struct data d;
		d.beg = 0;
		d.end = n-1;

		pthread_t tid[2];
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		pthread_create(&tid[0], &attr, MergeSort, &d);
		pthread_create(&tid[1], &attr, QuickSort, &d);

		pthread_join(tid[0], NULL);
		pthread_join(tid[1], NULL);

		printf("Merge Sorted: ");

		for(int i=0;i<n;i++) printf("%d ", arrqs[i]);

		printf("\n");

		printf("Quick Sorted: ");

		for(int i=0;i<n;i++) printf("%d ", arrms[i]);

		printf("\n");
	}
	
	//printf("------------------------------------ MERGE AND QUICK SORTING --------------------------------------\n");
	
}
