#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int arr[100];

struct data
{
	int beg;
	int end;

	int x;
};
// -----------------------------------------------------------
void * BinarySearch(void * d) 
{
	struct data *dm = d;
	int beg = dm->beg;
	int end = dm->end;
	int x = dm->x;

	//printf("\nBS: beg: %d, end: %d, x: %d\n", beg, end, x);

	if (beg < end) 
	{ 
		int mid = (beg+end)/2;

		if(arr[mid] == x) printf("\n%d found at index %d\n", x, mid);
		else 
		{
			pthread_t tid;
			pthread_attr_t attr;
			pthread_attr_init(&attr);

			struct data d;
			d.x = x;

			if(x < arr[mid])
			{
				d.beg = beg;
				d.end = mid;
			}
			else if(x > arr[mid])
			{
				d.beg = mid + 1;
				d.end = end;
			}

			pthread_create(&tid, &attr, BinarySearch, &d);

			pthread_join(tid, NULL);
		}

	}
	pthread_exit(0);
}
// ----------------------------------------------------------- 

int main(int argc, char *argv[])
{
	//printf("------------------------------------ MERGE AND QUICK SORTING --------------------------------------\n");

	if(argc < 3) printf("Wrong number of parameters.\n");
	else 
	{
		int n = argc - 2;

		struct data d;
		d.beg = 0;
		d.end = n-1;
		d.x = atoi(argv[1]);

		for(int i=0;i<n;i++)
		{
			arr[i] = atoi(argv[2 + i]);
		}

		// Sort
		/*
		for(int i=0;i<n-1;i++) {
			for(int j=0;j<n-i-1;j++) {
				if(arr[j] > arr[j+1])
				{
					int temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}
			}
		}
		for(int i=0;i<n;i++) printf("%d ", arr[i]);
		*/

		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		pthread_create(&tid, &attr, BinarySearch, &d);

		pthread_join(tid, NULL);

		printf("\n");
	}
	
	//printf("------------------------------------ MERGE AND QUICK SORTING --------------------------------------\n");
	
}
