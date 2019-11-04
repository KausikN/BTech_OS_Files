#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

struct data
{
	int i;
};
// -----------------------------------------------------------
int K = 0;
int Interested[2];
int Passed[2];
int flag = 1;
// -----------------------------------------------------------

// -----------------------------------------------------------
int x = 5;
void * runner(void * d)
{
	struct data *p = (struct data *)d;
	do
	{
		while(flag == 0);	// Wait till Interested set to 0 for this process is captured in busy wait of other process

		int exit = 0;
		while(exit == 0)
		{
			Interested[p->i] = 1;
			// printf("\t\t\tSTART: p: %d, Interested: %d, K: %d\n", p->i, Interested[p->i], K);
			while(K != p->i)
			{
				// printf("Waiting in Process %d...\n", p->i);
				if(Interested[K] == 0) K = p->i;
			}
			flag = 1; // After capturing set flag to 0
			Passed[p->i] = 1;
			int done = 1;

			for (int j=0;j<2;j++)
			{
				if (j != p->i && Passed[j] == 1)
				{
					Passed[p->i] = 0;
					done = 0;
				}
			}
			if(done == 1) exit = 1;
		}

		// CS
		printf("ENTER P: %d, X: %d\n", p->i, x);
		if(p->i == 0)x++;
		else x--;
		printf("EXIT P: %d, X: %d\n", p->i, x);
		sleep(1);
		// CS

		Passed[p->i] = 0;
		Interested[p->i] = 0;
		// printf("Coming Out of Process %d...\n", p->i);
		flag = 0; // Set flag to 0 to wait till it is captured
	} while(1);

	pthread_exit(0);
}


// -----------------------------------------------------------

int main()
{
	//printf("------------------------------------ Dejkstras Algo --------------------------------------\n");


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

	printf("\n");
	//printf("------------------------------------ Dejkstras Algo --------------------------------------\n");
	return 0;
}
