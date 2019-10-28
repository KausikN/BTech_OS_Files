#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int circle_points = 0, square_points = 0;
double rand_x, rand_y, origin_dist;
int interval;

int no_of_points = 0;

struct data
{
	int i;
};
// -----------------------------------------------------------
int turn;
int flag[2];
// -----------------------------------------------------------

// -----------------------------------------------------------
int x = 0;
void * runner(void * d)
{
	struct data *p = (struct data *)d;
	do
	{
		flag[p->i] = 1;

		turn = 1 - p->i;

		while(flag[1 - p->i] == 1 && turn == 1 - p->i);

		// CS
		// if(p->i == 0)x++;
		// else x--;
		// printf("P: %d, X: %d\n", p->i, x);
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

		flag[p->i] = 0;
	} while(no_of_points < interval*interval);

	pthread_exit(0);
}


// -----------------------------------------------------------

int main(int argc, char *argv[])
{
	//printf("------------------------------------ Petersons Algo --------------------------------------\n");

	if(argc != 2) printf("Wrong number of parameters.\n");
	else
	{
		interval = atoi(argv[1]);

		pthread_t tidi, tidj;
		pthread_attr_t attr;
		pthread_attr_init(&attr);

    	srand(time(NULL));

		struct data di;
		di.i = 0;
		struct data dj;
		dj.i = 1;

	  	pthread_create(&tidi, &attr, runner, &di);
		pthread_create(&tidj, &attr, runner, &dj);

	  	pthread_join(tidi, NULL);
		pthread_join(tidj, NULL);

	    double pi = (double)(4 * circle_points) / square_points;
	    printf("\nFinal Estimation of Pi = %f,\n", pi);
	}
	printf("\n");
	//printf("------------------------------------ Petersons Algo --------------------------------------\n");
	return 0;
}
