#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int circle_points = 0, square_points = 0;
double rand_x, rand_y, origin_dist;

int interval;
// -----------------------------------------------------------

void * runner(void * p)
{
	rand_x = (double)(rand() % (interval + 1)) / interval; 
    rand_y = (double)(rand() % (interval + 1)) / interval; 

    origin_dist = rand_x * rand_x + rand_y * rand_y; 

    if (origin_dist <= 1) 
        circle_points++; 

    square_points++;

	pthread_exit(0);
}


// -----------------------------------------------------------


int main(int argc, char *argv[])
{
	//printf("------------------------------------ PI ESTIMATION --------------------------------------\n");

	if(argc != 2) printf("Wrong number of parameters.\n");
	else
	{
		interval = atoi(argv[1]); 

		pthread_t tid[interval*interval];
		pthread_attr_t attr;
		pthread_attr_init(&attr); 

	    srand(time(NULL)); 

	    for (int i=0; i<(interval * interval); i++)
	    { 
	    	pthread_create(&tid[i], &attr, runner, NULL);
	    } 

	    for (int i=0; i<(interval * interval); i++)
	    { 
	    	pthread_join(tid[i], NULL);
	    }

	    double pi = (double)(4 * circle_points) / square_points; 
	    printf("\nFinal Estimation of Pi = %f,\n", pi);
	}
	printf("\n");
	//printf("------------------------------------ PI ESTIMATION --------------------------------------\n");
	return 0;
}