#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <sys/time.h>

#define N 5
// ASSUMED FUNCTION = x1*x2*x3*...*xn

int HM[N][N];
int HM_NonThread[N][N];
int x[N];

struct pair
{
	int i;
	int j;
};
// -----------------------------------------------------------
int grad(int i, int j)
{
	if(i == j) return 0;
	int val = 1;
	for(int it=0;it<N;it++)
	{
		if(it != i && it != j) val = val * x[it];
	}
	return val;
	return 0;
}
void * runner(void * pairp)
{
	struct pair *p = (struct pair *) pairp;

	int i = p->i;
	int j = p->j;

	HM[i][j] = grad(i, j);

	pthread_exit(0);
}

void HessianMatrixCalc(int i, int j)
{
	HM_NonThread[i][j] = grad(i, j);
}

// -----------------------------------------------------------


int main(int argc, char *argv[])
{
	//printf("------------------------------------ Hessian Matrix --------------------------------------\n");

	if(argc != 1) printf("Wrong number of parameters.\n");
	else
	{
		//------------------------------------THREADED-------------------------------------
		struct timeval start, stop;
		double secs = 0;

		for(int i=0;i<N;i++)
		{
			x[i] = i+1;
		}

		struct pair p[N*N];

		pthread_t tid[N*N];
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		int index = 0;
		gettimeofday(&start, NULL);
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				p[index].i = i;
				p[index].j = j;
				pthread_create(&tid[index], &attr, runner, &p[index]);
				index++;
			}
		}
		for(int i=0;i<N*N;i++) pthread_join(tid[i], NULL);

		gettimeofday(&stop, NULL);
		secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
		printf("\nExe time (Threaded):  %f\n", secs);

		// Display
		printf("\nAnswer (Threaded):\n");
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				printf("%d ", HM[i][j]);
			}
			printf("\n");
		}
		//------------------------------------THREADED-------------------------------------

		//------------------------------------NON THREADED-------------------------------------
		double secs_nt = 0;
		struct timeval start_nt, stop_nt;
		gettimeofday(&start_nt, NULL);

		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				HessianMatrixCalc(i, j);
			}
		}

		gettimeofday(&stop_nt, NULL);
		secs_nt = (double)(stop_nt.tv_usec - start_nt.tv_usec) / 1000000 + (double)(stop_nt.tv_sec - start_nt.tv_sec);
		printf("\nExe time (Non Threaded):  %f\n", secs_nt);

		// Display
		printf("\nAnswer (Non Threaded):\n");
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				printf("%d ", HM_NonThread[i][j]);
			}
			printf("\n");
		}
		//------------------------------------NON THREADED-------------------------------------
	}
	printf("\n");
	//printf("------------------------------------ Hessian Matrix --------------------------------------\n");
	return 0;
}