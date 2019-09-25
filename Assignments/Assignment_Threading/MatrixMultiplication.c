#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int A[100][100];
int B[100][100];
int C[100][100];
int M, N, K;

struct pair
{
	int i;
	int j;
};
// -----------------------------------------------------------
void * runner(void * pairp)
{
	struct pair *p = pairp;

	int i = p->i;
	int j = p->j;

	//printf("\nStarted %d-%d\n", i, j);

	int sum = 0;
	for(int it=0;it<K;it++)
	{
		sum = sum + A[i][it]*B[it][j];
	}
	
	C[i][j] = sum;

	pthread_exit(0);
}

// -----------------------------------------------------------


int main(int argc, char *argv[])
{
	//printf("------------------------------------ Matrix Multiplication --------------------------------------\n");

	if(argc < 4) printf("Wrong number of parameters.\n");
	else
	{
		M = atoi(argv[1]);
		N = atoi(argv[2]);
		K = atoi(argv[3]);

		int ind = 4;

		for(int i=0;i<M;i++)
		{
			for(int j=0;j<K;j++)
			{
				A[i][j] = atoi(argv[ind + i*j + j]);
			}
		}
		ind = ind + M*K;
		for(int i=0;i<K;i++)
		{
			for(int j=0;j<N;j++)
			{
				B[i][j] = atoi(argv[ind + i*j + j]);
			}
		}

		struct pair p[M*N];

		pthread_t tid[M*N];
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		int index = 0;

		for(int i=0;i<M;i++)
		{
			for(int j=0;j<N;j++)
			{
				p[index].i = i;
				p[index].j = j;
				pthread_create(&tid[index], &attr, runner, &p[index]);
				index++;
			}
		}

		for(int i=0;i<=M*N;i++) pthread_join(tid[i], NULL);

		// Display
		//printf("\nAnswer:\n");
		for(int i=0;i<M;i++)
		{
			for(int j=0;j<N;j++)
			{
				printf("%d ", C[i][j]);
			}
			printf("\n");
		}
	}
	printf("\n");
	//printf("------------------------------------ Matrix Multiplication --------------------------------------\n");
	return 0;
}