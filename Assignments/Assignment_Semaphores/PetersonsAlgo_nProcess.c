#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define MAX_PROCESSES 100

int circle_points = 0, square_points = 0;
double rand_x, rand_y, origin_dist;
int interval;

int no_of_points = 0;

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
		printf("pr: %d - pt: %d - ENTER\n", p->i, no_of_points);
		no_of_points++;

		rand_x = (double)(rand() % (interval + 1)) / interval;
		rand_y = (double)(rand() % (interval + 1)) / interval;

		origin_dist = rand_x * rand_x + rand_y * rand_y;

		if (origin_dist <= 1)
			circle_points++;

		square_points++;
		printf("pr: %d - pt: %d - EXIT\n", p->i, no_of_points);
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

	} while(no_of_points < interval*interval);

	pthread_exit(0);
}
// -----------------------------------------------------------

int main(int argc, char *argv[])
{
	//printf("------------------------------------ Petersons Algo --------------------------------------\n");

	if(argc != 3) printf("Wrong number of parameters.\n");
	else
	{
		no_of_process = atoi(argv[1]);
		interval = atoi(argv[2]);

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

	    double pi = (double)(4 * circle_points) / square_points;
	    printf("\nFinal Estimation of Pi = %f,\n", pi);
	}
	printf("\n");
	//printf("------------------------------------ Petersons Algo --------------------------------------\n");
	return 0;
}
