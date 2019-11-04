#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define MAX_PROCESSES 100

struct data
{
	int i;
	int flow;
};
// -----------------------------------------------------------
sem_t mutex;
int no_of_process = 1;
int flag = 1;
// -----------------------------------------------------------
int baboons_crossing = 0;			// No of baboons crossing currently
int current_flow_direction = 1;		// 1 or -1
int rope_capacity = 5;				// Max no of baboons on the rope allowed
int flow_changing = 0;				//  1 if flow is changing
int rope_broken = 0;				// 0 if no of baboons_crossing < rope_capacity
// -----------------------------------------------------------

void * runner(void * d)
{
	struct data *p = (struct data *)d;
	do
	{
		while(flag == 0) printf("Stuck...\n");

		sem_wait(&mutex);

		if(p->flow != current_flow_direction)
		{
			flow_changing = 1;
			while(baboons_crossing > 0 && current_flow_direction != p->flow);
			flow_changing = 0;
			current_flow_direction = p->flow;
			flag = 1;
		}
		else
		{
			if(flow_changing == 1)
			{
				while((flow_changing == 1 && current_flow_direction == p->flow) || (flow_changing == 0 && current_flow_direction != p->flow));
			}
		}
		// CS
		printf("ENTER B: %d - \t\tflow %d\t\t - \t\t%d / %d\n", p->i, current_flow_direction, baboons_crossing, rope_capacity);
		baboons_crossing++;
		printf("EXITE B: %d - \t\tflow %d\t\t - \t\t%d / %d\n", p->i, current_flow_direction, baboons_crossing, rope_capacity);
		sleep(1);
        // CS

		baboons_crossing--;
		sem_post(&mutex);

		if(flag==1) flag = 0;

	} while(1);

	pthread_exit(0);
}
// -----------------------------------------------------------

int main(int argc, char *argv[])
{
	//printf("------------------------------------ Baboon Crossing --------------------------------------\n");

	if(argc != 2) printf("Wrong number of parameters.\n");
	else
	{
		no_of_process = atoi(argv[1]);

		sem_init(&mutex, 0, rope_capacity);

		pthread_t tid[no_of_process];
		pthread_attr_t attr;
		pthread_attr_init(&attr);

    	srand(time(NULL));

		struct data d[no_of_process];

		for(int i=0;i<no_of_process;i++)
		{
			d[i].i = i;
			if(i%2 == 0) d[i].flow = 1;
			else d[i].flow = -1;
			pthread_create(&tid[i], &attr, runner, &d[i]);
		}

		for(int i=0;i<no_of_process;i++)
		{
			pthread_join(tid[i], NULL);
		}
	}
	printf("\n");
	//printf("------------------------------------ Baboon Crossing --------------------------------------\n");
	return 0;
}
