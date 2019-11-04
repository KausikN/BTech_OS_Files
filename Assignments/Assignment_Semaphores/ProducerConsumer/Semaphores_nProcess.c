#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define MAX_PROCESSES 100

struct data
{
	int i;
};
// -----------------------------------------------------------
sem_t mutex;
int no_of_process = 1;
int flag = 1;
// -----------------------------------------------------------
int x = 5;
// -----------------------------------------------------------

void * runner(void * d)
{
	struct data *p = (struct data *)d;
	do
	{
		while(flag == 0);

		sem_wait(&mutex);
		flag = 1;
		// CS
		printf("ENTER P: %d, X: %d\n", p->i, x);
		if(p->i % 2 == 0)x++;
		else x--;
		printf("EXIT P: %d, X: %d\n", p->i, x);
		//sleep(1);
        // CS

		sem_post(&mutex);
		
		flag = 0;

	} while(1);

	pthread_exit(0);
}
// -----------------------------------------------------------

int main(int argc, char *argv[])
{
	//printf("------------------------------------ Semaphores --------------------------------------\n");

	if(argc != 2) printf("Wrong number of parameters.\n");
	else
	{
		no_of_process = atoi(argv[1]);

		sem_init(&mutex, 0, 1);

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
	//printf("------------------------------------ Semaphores --------------------------------------\n");
	return 0;
}
