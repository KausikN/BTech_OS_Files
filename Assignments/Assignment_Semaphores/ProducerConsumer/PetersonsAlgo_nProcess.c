#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define MAX_PROCESSES 100

struct data
{
	int i;
};
// -----------------------------------------------------------
int lock;
int waiting[MAX_PROCESSES];
int no_of_process = 1;
// -----------------------------------------------------------
int test_set(int *target)
{
	int rv = *target;
	*target = 1;
	return rv;
}
// -----------------------------------------------------------
int x = 5;
void * runner(void * d)
{
	struct data *p = (struct data *)d;
	do
	{
		waiting[p->i] = 1;
		int key = 1;

		while(waiting[p->i] == 1 && key == 1)
		{
			key = test_set(&lock);
			//printf("\t\tWAIT pr: %d - key-lock: %d-%d\n", p->i, key, lock);
		}

		// CS
		printf("ENTER P: %d, X: %d\n", p->i, x);
		if(p->i % 2 == 0)x++;
		else x--;
		printf("EXIT P: %d, X: %d\n", p->i, x);
		sleep(1);
		// CS

		waiting[p->i] = 0;

		int j = (p->i + 1) % no_of_process;
		while(j != p->i && waiting[j] == 0)
		{
			//printf("\t\tEXITCOND pr: %d, j: %d\n", p->i, j);
			j = (j + 1) % no_of_process;
		}
		if(j == p->i)
		{
			lock = 0;
		}
		else
		{
			waiting[j] = 0;
		}

	} while(1);

	pthread_exit(0);
}
// -----------------------------------------------------------

int main(int argc, char *argv[])
{
	//printf("------------------------------------ Petersons Algo --------------------------------------\n");

	if(argc != 2) printf("Wrong number of parameters.\n");
	else
	{
		no_of_process = atoi(argv[1]);

		pthread_t tid[no_of_process];
		pthread_attr_t attr;
		pthread_attr_init(&attr);

    	srand(time(NULL));

		struct data d[no_of_process];

		for(int i=0;i<no_of_process;i++)
		{
			d[i].i = i;
			pthread_create(&tid[i], &attr, runner, &d[i]);
		}

		for(int i=0;i<no_of_process;i++)
		{
			pthread_join(tid[i], NULL);
		}
	}
	printf("\n");
	//printf("------------------------------------ Petersons Algo --------------------------------------\n");
	return 0;
}
