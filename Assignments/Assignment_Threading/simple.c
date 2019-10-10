#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int sum = 0;
// -----------------------------------------------------------
void * runner(void * p)
{
	// int upperlimit = atoi(param);

	//pthread_exit(5);
}

// -----------------------------------------------------------


int main(int argc, char *argv[])
{
	//printf("------------------------------------ SUM --------------------------------------\n");
	if(argc < 2) printf("Wrong number of parameters.\n");
	else
	{
		int n = 6;

		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		int scope;
		pthread_attr_getscope(&attr,&scope);
		if(scope == PTHREAD_SCOPE_SYSTEM)
		printf("\nHi1\n");

		pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);

		if(scope == PTHREAD_SCOPE_PROCESS)
		printf("\nHi2\n");

		// pthread_create(&tid, &attr, runner, argv[1]);

		// int ret = pthread_join(tid, &n);

		// printf("\nRET: %d\nn: %d\n", ret, n);

		// printf("\nSum: %d\n", sum);
	}
	printf("\n");
	//printf("------------------------------------ SUM --------------------------------------\n");
	return 0;
}