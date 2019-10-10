#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int A[100][100];
int I[100][100];
int N;

struct data
{
	int n;
	int D;
	int sign;
	int f;
	int mat[100][100];
	int temp[100][100];
};
// -----------------------------------------------------------
void getCofactor(int *mat[], int *temp[], int p, int q, int n) 
{ 
    int i = 0, j = 0; 

    for (int row = 0; row < n; row++) 
    { 
        for (int col = 0; col < n; col++) 
        { 
            if (row != p && col != q) 
            { 
                temp[i][j++] = mat[row][col]; 

                if (j == n - 1) 
                { 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
} 

void * detrunner(struct data * p)
{
	//printf("\nStarted %d-%d\n", i, j);

	getCofactor(p->mat, p->temp, 0, p->f, p->n); 
    p->D += p->sign * p->mat[0][p->f] * determinantOfMatrix(p->temp, p->n - 1);

	pthread_exit(0);
}

int determinantOfMatrix(int *mat[], int n) 
{
    int D = 0;

    if (n == 1) 
        return mat[0][0]; 
  
    int temp[N][N];
  
    int sign = 1;

    pthread_t tid[n];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	struct data d[n];

	for(int i=0;i<n;i++)
	{
		d[i].n = n; d[i].D = D;
		for(int j=0;j<n;j++)
		{
			for(int k=0;k<n;k++)\
			{
				d[i].mat[j][k] = mat[j][k];
			}
		}
	}

    for (int f = 0; f < n; f++) 
    { 
        d[f].sign = sign; d[f].f = f;
        pthread_create(&tid[f], &attr, detrunner, &d[f]);

        sign = -sign; 
    }

    for(int i=0;i<n;i++) pthread_join(tid[i], NULL);
  
    return D; 
} 



// -----------------------------------------------------------


int main(int argc, char *argv[])
{
	//printf("------------------------------------ Determinant Cofactor --------------------------------------\n");

	if(argc < 2) printf("Wrong number of parameters.\n");
	else
	{
		//printf("%d\n", argc);
		N = atoi(argv[1]);

		int ind = 2;

		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				A[i][j] = atoi(argv[ind + i*j + j]);
			}
		}
		printf("Answer: \n");

		//struct data p[M*N];

		// pthread_t tid[M*N];
		// pthread_attr_t attr;
		// pthread_attr_init(&attr);

		// int index = 0;

		// for(int i=0;i<M;i++)
		// {
		// 	for(int j=0;j<N;j++)
		// 	{
		// 		p[index].i = i;
		// 		p[index].j = j;
		// 		pthread_create(&tid[index], &attr, runner, &p[index]);
		// 		index++;
		// 	}
		// }

		// for(int i=0;i<=M*N;i++) pthread_join(tid[i], NULL);

		printf("DET: %d\n", determinantOfMatrix(A, N));

		// Display
		//printf("\nAnswer:\n");
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				printf("%d ", I[i][j]);
			}
			printf("\n");
		}
	}
	printf("\n");
	//printf("------------------------------------ Determinant Cofactor --------------------------------------\n");
	return 0;
}