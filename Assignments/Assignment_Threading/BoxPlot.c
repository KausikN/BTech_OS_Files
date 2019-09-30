#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int min, max;
float median, lquartile, uquartile;
float iqr, lwhisker, uwhisker;

int outlier[100];
// -----------------------------------------------------------

struct data
{
	int n;
	int arr[100];

	int beg;
	int end;
};

void * findmin(struct data * p)
{
	struct data d = *p;

	lwhisker = lquartile - 1.5*iqr;

	min = d.arr[0];
	for(int i=0;i<d.n;i++) 
	{
		if(d.arr[i] < lwhisker)
			outlier[i] = 1;
		if(min > d.arr[i]) 
			min = d.arr[i]; 
	}

	pthread_exit(0);
}
void * findmax(struct data * p)
{
	struct data d = *p;

	uwhisker = uquartile + 1.5*iqr;

	max = d.arr[0];
	for(int i=0;i<d.n;i++)
	{
		if(d.arr[i] < lwhisker)
			outlier[i] = 1;
		if(max < d.arr[i]) 
			max = d.arr[i]; 
	}	

	pthread_exit(0);
}
void * findmedian(struct data * p)
{
	struct data d = *p;

	int size = d.end - d.beg + 1;
	
	if(size%2 == 1) median = d.arr[d.beg + (int)((size-1)/2)];
	else 
	{
		float l = d.arr[d.beg + (int)(size/2)];
		float r = d.arr[d.beg + (int)(size/2) - 1];
		median = (l+r)/2;
	}

	pthread_exit(0);
}
void * findlq(struct data * p)
{
	struct data d = *p;

	int size = d.end - d.beg + 1;
	
	if(size%2 == 1) lquartile = d.arr[d.beg + (int)((size-1)/2)];
	else 
	{
		float l = d.arr[d.beg + (int)(size/2)];
		float r = d.arr[d.beg + (int)(size/2) - 1];
		lquartile = (l+r)/2;
	}

	pthread_exit(0);
}
void * finduq(struct data * p)
{
	struct data d = *p;

	int size = d.end - d.beg + 1;
	
	if(size%2 == 1) uquartile = d.arr[d.beg + (int)((size-1)/2)];
	else 
	{
		float l = d.arr[d.beg + (int)(size/2)];
		float r = d.arr[d.beg + (int)(size/2) - 1];
		uquartile = (l+r)/2;
	}

	pthread_exit(0);
}



// -----------------------------------------------------------


int main(int argc, char *argv[])
{
	//printf("------------------------------------ BOX PLOT --------------------------------------\n");

	if(argc < 2) printf("Wrong number of parameters.\n");
	else
	{
		int n = argc - 1;

		int arr[n];
		for(int i=0;i<n;i++) arr[i] = atoi(argv[1 + i]);

		struct data d[3];
		d[0].n = n;
		d[1].n = n;
		d[2].n = n;

		// Sort
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

		printf("\nSorted array: ");
		for(int i=0;i<n;i++)
		{
			outlier[i] = 0;

			d[0].arr[i] = arr[i];
			d[1].arr[i] = arr[i];
			d[2].arr[i] = arr[i];
			printf("%d ", arr[i]);
		}
		printf("\n");

		pthread_t tid[5];
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		d[0].beg = 0;
		d[0].end = (int)(n/2) - 1;

		pthread_create(&tid[0], &attr, findlq, &d[0]);
		d[1].beg = (int)((n+1) / 2);
		d[1].end = n - 1;

		pthread_create(&tid[1], &attr, finduq, &d[1]);
		d[2].beg = 0;
		d[2].end = n - 1;
		pthread_create(&tid[2], &attr, findmedian, &d[2]);
		pthread_join(tid[0], NULL);
		pthread_join(tid[1], NULL);

		iqr = uquartile - lquartile;

		pthread_create(&tid[3], &attr, findmin, &d[2]);
		pthread_create(&tid[4], &attr, findmax, &d[2]);

		pthread_join(tid[2], NULL);
		pthread_join(tid[3], NULL);
		pthread_join(tid[4], NULL);

		printf("\nMax:              %d\n", max);	
		printf("\nUpper Whisker:    %f\n", uwhisker);	
		printf("\nUpper Quartile:   %f\n", uquartile);	
		printf("\nMedian:           %f\n", median);	
		printf("\nLower Quartile:   %f\n", lquartile);	
		printf("\nLower Whisker:    %f\n", lwhisker);
		printf("\nMin:              %d\n", min);

		printf("\nOutliers: ");
		for(int i=0;i<n;i++)
		{
			if(outlier[i] == 1) printf("%d ", arr[i]);
		}
		printf("\n");

	}
	printf("\n");
	//printf("------------------------------------ BOX PLOT --------------------------------------\n");
	return 0;
}