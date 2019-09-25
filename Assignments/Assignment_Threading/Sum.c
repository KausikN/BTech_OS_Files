#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int sum = 0;
// -----------------------------------------------------------
void * runner(void * param)
{
	int upperlimit = atoi(param);

	for(int i=0;i<=upperlimit;i++)
	{
		sum = sum + i;
	}

	pthread_exit(0);
}

// -----------------------------------------------------------


int main(int argc, char *argv[])
{
	//printf("------------------------------------ SUM --------------------------------------\n");
	if(argc < 2) printf("Wrong number of parameters.\n");
	else
	{
		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		pthread_create(&tid, &attr, runner, argv[1]);

		pthread_join(tid, NULL);

		printf("Sum: %d\n", sum);
	}
	printf("\n");
	//printf("------------------------------------ SUM --------------------------------------\n");
	return 0;
}