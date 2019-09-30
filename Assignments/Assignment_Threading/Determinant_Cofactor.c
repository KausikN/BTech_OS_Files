#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int A[100][100];
int 
int N;

struct data
{
	int i;
	int j;
};
// -----------------------------------------------------------
void getCofactor(int mat[][], int temp[][], int p, int q, int n) 
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

int determinantOfMatrix(int mat[][], int n) 
{ 
    int D = 0;

    if (n == 1) 
        return mat[0][0]; 
  
    int temp[N][N];
  
    int sign = 1; 

    for (int f = 0; f < n; f++) 
    { 
        getCofactor(mat, temp, 0, f, n); 
        D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1); 

        sign = -sign; 
    } 
  
    return D; 
} 

void * determinant(void * datap)
{
	struct data *p = datap;

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
		ind = ind + M*K;
		for(int i=0;i<K;i++)
		{
			for(int j=0;j<N;j++)
			{
				//printf("\nInt: %d,%d -> %d\n", i, j, ind + i*N + j);
				B[i][j] = atoi(argv[ind + i*N + j]);
			}
		}
		printf("Answer: \n");

		struct data p[M*N];

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
	//printf("------------------------------------ Determinant Cofactor --------------------------------------\n");
	return 0;
}