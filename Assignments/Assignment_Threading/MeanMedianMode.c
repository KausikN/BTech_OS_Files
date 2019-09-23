#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int n;
// -----------------------------------------------------------
void * mean(int * p)
{
	int arr[n];
	for(int i=0;i<n;i++)
	{
		arr[i] = p[i];
	}

	float mean = 0;
	for(int i=0;i<n;i++)
	{
		mean = mean + arr[i];
	}
	mean = mean / n;
	printf("\nMean: %f\n", mean);

	pthread_exit(0);
}

void * median(int * p)
{
	int arr[n];
	for(int i=0;i<n;i++)
	{
		arr[i] = p[i];
	}
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
	int median = arr[n/2 - 1];
	printf("\nMedian: %d\n", median);	

	pthread_exit(0);
}

void * mode(int * p)
{
	int arr[n];
	for(int i=0;i<n;i++)
	{
		arr[i] = p[i];
	}

	int mode = 0;
	int maxcount = 0;

	for (int i=0;i<n;i++) {
		int count = 0;

		for (int j=0;j<n;j++) {
			if (arr[j] == arr[i])
			count++;
		}

		if (count > maxcount) {
			maxcount = count;
			mode = arr[i];
		}
	}
	
	printf("\nMode: %d\n", mode);
	pthread_exit(0);
}

// -----------------------------------------------------------


int main(int argc, char *argv[])
{
	//printf("------------------------------------ MEAN MEDIAN MODE --------------------------------------\n");

	if(argc < 2) printf("Wrong number of parameters.\n");
	else
	{
		n = argc - 1;

		int arr[n];
		for(int i=0;i<n;i++) arr[i] = atoi(argv[1 + i]);

		pthread_t tid[3];
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		pthread_create(&tid[0], &attr, mean, arr);
		pthread_create(&tid[1], &attr, median, arr);
		pthread_create(&tid[2], &attr, mode, arr);


		pthread_join(tid[0], NULL);
		pthread_join(tid[1], NULL);
		pthread_join(tid[2], NULL);
	}
	printf("\n");
	//printf("------------------------------------ MEAN MEDIAN MODE --------------------------------------\n");
	return 0;
}