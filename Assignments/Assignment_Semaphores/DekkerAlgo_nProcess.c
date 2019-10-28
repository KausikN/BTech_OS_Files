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
int turn;
int flag[MAX_PROCESSES];
int no_of_process = 1;
// -----------------------------------------------------------
int x = 5;
// -----------------------------------------------------------

void * runner(void * d)
{
	struct data *p = (struct data *)d;
	do
	{
		flag[p->i] = 1;
		printf("\t\t\tSTART: p: %d, flag_p: %d, turn: %d\n", p->i, flag[p->i], turn);
		int exit = 0;
		int i = 0;
		while(exit == 0)
		{
			while (i != p->i && flag[i] == 1)
			{
	            if (turn != p->i)
				{
	                flag[p->i] = 0;
	                while (turn != p->i);
	                flag[p->i] = 1;
	            }
				//printf("\t\t\tSTAT: p: %d, pdash: %d, turn: %d\n", flag[p->i], flag[1 - p->i], turn);
	        }
			i++;
			if(i == no_of_process) exit = 1;
		}

		// CS
		printf("ENTER P: %d, X: %d\n", p->i, x);
		if(p->i % 2 == 0)x++;
		else x--;
		printf("EXIT P: %d, X: %d\n", p->i, x);
		// printf("pr: %d - pt: %d - ENTER\n", p->i, no_of_points);
		// no_of_points++;
		//
		// rand_x = (double)(rand() % (interval + 1)) / interval;
		// rand_y = (double)(rand() % (interval + 1)) / interval;
		//
		// origin_dist = rand_x * rand_x + rand_y * rand_y;
		//
		// if (origin_dist <= 1)
		// 	circle_points++;
		//
		// square_points++;
		// printf("pr: %d - pt: %d - EXIT\n", p->i, no_of_points);
		// CS

		turn = (p->i + 1) % no_of_process;
        flag[p->i] = 0;

	} while(no_of_points < interval*interval);

	pthread_exit(0);
}
// -----------------------------------------------------------

int main(int argc, char *argv[])
{
	//printf("------------------------------------ Dekkers Algo --------------------------------------\n");

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
	//printf("------------------------------------ Dekkers Algo --------------------------------------\n");
	return 0;
}
