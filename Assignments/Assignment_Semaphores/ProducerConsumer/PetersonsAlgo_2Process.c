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
		printf("ENTER P: %d, X: %d\n", p->i, x);
		if(p->i % 2 == 0)x++;
		else x--;
		printf("EXIT P: %d, X: %d\n", p->i, x);
		sleep(1);
		// CS

		flag[p->i] = 0;
	} while(1);

	pthread_exit(0);
}


// -----------------------------------------------------------

int main()
{
	//printf("------------------------------------ Petersons Algo --------------------------------------\n");

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
	//printf("------------------------------------ Petersons Algo --------------------------------------\n");
	return 0;
}
