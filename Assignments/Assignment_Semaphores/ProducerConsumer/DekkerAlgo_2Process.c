#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

struct data
{
	int i;
};
// -----------------------------------------------------------
int turn;
int flag[2];
// -----------------------------------------------------------

// -----------------------------------------------------------
int x = 5;
void * runner(void * d)
{
	struct data *p = (struct data *)d;
	do
	{
		flag[p->i] = 1;
		printf("\t\t\tSTART: p: %d, flag_p: %d, turn: %d\n", p->i, flag[p->i], turn);
        while (flag[1 - p->i] == 1)
		{
            if (turn != p->i)
			{
                flag[p->i] = 0;
                while (turn != p->i);
                flag[p->i] = 1;
            }
			//printf("\t\t\tSTAT: p: %d, pdash: %d, turn: %d\n", flag[p->i], flag[1 - p->i], turn);
        }

		// CS
		printf("ENTER P: %d, X: %d\n", p->i, x);
		if(p->i == 0)x++;
		else x--;
		printf("EXIT P: %d, X: %d\n", p->i, x);
		sleep(1);
		// CS

		turn = 1 - p->i;
        flag[p->i] = 0;

	} while(1);

	pthread_exit(0);
}


// -----------------------------------------------------------

int main()
{
	//printf("------------------------------------ Dekkers Algo --------------------------------------\n");

	pthread_t tidi, tidj;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	srand(time(NULL));

	struct data di;
	di.i = 0;
	struct data dj;
	dj.i = 1;

	flag[0] = 0;
	flag[1] = 0;

  	pthread_create(&tidi, &attr, runner, &di);
	pthread_create(&tidj, &attr, runner, &dj);

  	pthread_join(tidi, NULL);
	pthread_join(tidj, NULL);

	printf("\n");
	//printf("------------------------------------ Dekkers Algo --------------------------------------\n");
	return 0;
}
