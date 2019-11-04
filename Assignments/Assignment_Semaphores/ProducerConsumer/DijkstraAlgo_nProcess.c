#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define MAX_PROCESSES 100

struct data
{
	int i;
};
// -----------------------------------------------------------
int K = 0;
int Interested[MAX_PROCESSES];
int Passed[MAX_PROCESSES];
int no_of_process = 1;
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
			while(K != p->i)
			{
				if(Interested[K] == 0) K = p->i;
			}
			flag = 1; // After capturing set flag to 0
			Passed[p->i] = 1;
			int done = 1;

			for (int j=0;j<no_of_process;j++)
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
		if(p->i % 2 == 0)x++;
		else x--;
		printf("EXIT P: %d, X: %d\n", p->i, x);
		sleep(1);
		// CS

		Passed[p->i] = 0;
		Interested[p->i] = 0;
		flag = 0; // Set flag to 0 to wait till it is captured

	} while(1);

	pthread_exit(0);
}
// -----------------------------------------------------------

int main(int argc, char *argv[])
{
	//printf("------------------------------------ Dejkstras Algo --------------------------------------\n");

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
	//printf("------------------------------------ Dejkstras Algo --------------------------------------\n");
	return 0;
}
