#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

// -----------------------------------------------------------
void * runner(void * p)
{
	int n = p;
	//printf("\nStarted %d\n", n);

	int check = 0;
	int a = n-1;
	while(a > 1)
	{
		if(n%a == 0)
		{
			a=-1;
			break;
		}
		a--;
	}
	if(a > 0)
	{
		printf("%d ", n);
	}

	pthread_exit(0);
}

// -----------------------------------------------------------


int main(int argc, char *argv[])
{
	//printf("------------------------------------ PRIME SERIES GEN --------------------------------------\n");

	if(argc != 2) printf("Wrong number of parameters.\n");
	else
	{
		int n = atoi(argv[1]);

		//printf("Limit: %d\n", n);

		//printf("Prime Series: \n");

		pthread_t tid[n+1];
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		int no = 2;
		while(no <= n)
		{
			pthread_create(&tid[no], &attr, runner, no);

			no++;
		}

		for(int i=2;i<=n;i++) pthread_join(tid[i], NULL);
	}
	printf("\n");
	//printf("------------------------------------ PRIME SERIES GEN --------------------------------------\n");
	return 0;
}