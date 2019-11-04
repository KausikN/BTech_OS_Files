#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define MAX_PROCESSES 100

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
		sleep(1);
        // CS

		turn = (p->i + 1) % no_of_process;
		flag[p->i] = 0;

	} while(1);

	pthread_exit(0);
}
// -----------------------------------------------------------

int main(int argc, char *argv[])
{
	//printf("------------------------------------ Dekkers Algo --------------------------------------\n");

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
	//printf("------------------------------------ Dekkers Algo --------------------------------------\n");
	return 0;
}
