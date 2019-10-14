#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#define RANGE 255 

int arrcount[100];
int array[100];

struct data
{
	int arr[100];
	int n;
};

struct count_sort_data
{
	struct data *d;
	int exp;
};
// -----------------------------------------------------------
int getMax(int arr[], int n) 
{ 
    int mx = arr[0]; 
    for (int i = 1; i < n; i++) 
        if (arr[i] > mx) 
            mx = arr[i]; 
    return mx; 
} 

void * countSort(struct count_sort_data * param) 
{ 
	struct count_sort_data *cd = param;
 
    char output[cd->n];  
  
    int count[RANGE + 1], i;  
    memset(count, 0, sizeof(count));  
 
    for(i = 0; cd->arr[i]; ++i)  
        ++count[cd->arr[i]];  

    for (i = 1; i <= RANGE; ++i)  
        count[i] += count[i-1];  
 
    for (i = 0; cd->arr[i]; ++i)  
    {  
        output[count[cd->arr[i]]-1] = cd->arr[i];  
        --count[cd->arr[i]];  
    }  
  
    /*  
    For Stable algorithm  
    for (i = sizeof(arr)-1; i>=0; --i)  
    {  
        output[count[arr[i]]-1] = arr[i];  
        --count[arr[i]];  
    }  
      
    For Logic : See implementation  
    */

    for (i = 0; cd->arr[i]; ++i)  
        cd->arr[i] = output[i]; 

    pthread_exit(0);
} 


// ----------------------------------------------------------- 
void * BubbleSort(void * param)
{
	struct data *d = param;

	for(int i=1;i<d->n;i++){
		int tcheck=0;
		for(int j=0;j<d->n-i;j++){
			if(d->arr[j]>d->arr[j+1]){
				int temp=d->arr[j];
				d->arr[j]=d->arr[j+1];
				d->arr[j+1]=temp;
				tcheck=1;
			}
		}
		if(tcheck==0)break;
	}

	pthread_exit(0);
}
// ----------------------------------------------------------- 
void * InsertionSort(void * param)
{
	struct data *d = param;

	for(int i=1;i<d->n;i++){
		for(int j=i;j>0;j--){
			if(d->arr[j-1]>d->arr[j]){
				int temp=d->arr[j];
				d->arr[j]=d->arr[j-1];
				d->arr[j-1]=temp;
			}
			else break;
		}
	}

	pthread_exit(0);
}
// ----------------------------------------------------------- 

int main(int argc, char *argv[])
{
	//printf("------------------------------------ COUNT SORTING --------------------------------------\n");

	if(argc < 2) printf("Wrong number of parameters.\n");
	else 
	{
		int n = argc - 1;

		for(int i=0;i<n;i++)
		{
			arrcount[i] = atoi(argv[1 + i]);
			array[i] = atoi(argv[1 + i]);
		}

		struct data d[3];
		for(int i=0;i<n;i++)
		{
			d[0].arr[i] = arrcount[i];
			d[1].arr[i] = arrcount[i];
			d[2].arr[i] = arrcount[i];
		}
		d[0].n = n;
		d[1].n = n;
		d[2].n = n;

		pthread_t tid[2];
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		pthread_create(&tid[0], &attr, countSort, &d[0]);
		pthread_create(&tid[1], &attr, BubbleSort, &d[1]);
		pthread_create(&tid[1], &attr, InsertionSort, &d[2]);

		pthread_join(tid[0], NULL);
		pthread_join(tid[1], NULL);
		pthread_join(tid[2], NULL);

		printf("Count Sorted: ");

		for(int i=0;i<n;i++) printf("%d ", d[0].arr[i]);

		printf("\n");

		printf("Bubble Sorted: ");

		for(int i=0;i<n;i++) printf("%d ", d[1].arr[i]);

		printf("\n");

		printf("Insertion Sorted: ");

		for(int i=0;i<n;i++) printf("%d ", d[2].arr[i]);

		printf("\n");
	}
	
	//printf("------------------------------------ COUNT SORTING --------------------------------------\n");
	
}
