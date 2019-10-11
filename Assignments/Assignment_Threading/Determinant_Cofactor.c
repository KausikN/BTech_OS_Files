#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int N;

int adj[100][100];
float inv[100][100];
int A[100][100];

struct data{
	int i;
	int j;
};

void cofactor(int mat[100][100], int temp[100][100], int p, int q, int n){

	int i=0, j=0;

	for(int row= 0; row<n; row++){
		for(int col=0; col<n; col++){
			if(row!=p && col!=q){
				temp[i][j++] = mat[row][col];
				if(j==n-1){
					j=0;
					i++;
				}
			}
		}
	}

}

int determinant(int mat[100][100], int n){
	
	int D=0;

	if(n==1)
		return mat[0][0];

	int temp[N][N];
	int sign=1;


	for(int f=0; f<n; f++){
		cofactor(mat, temp, 0, f, n);
		D += sign * mat[0][f] * determinant(temp, n-1);

		sign=-sign;
	}
	return D;
}

void* runnercofacval(void *param){

	int temp[N][N];
	int sign=1;

	struct data *data = param;
	cofactor(A, temp, data->i, data->j, N);
	sign = ((data->i + data->j)%2==0) ? 1: -1;
	adj[data->j][data->i] = sign * (determinant(temp, N-1));

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
				A[i][j] = atoi(argv[ind + i*N + j]);
			}
		}

		printf("\nMatrix: \n");
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
				printf("%d ", A[i][j]);
			printf("\n");
		}

		pthread_t tid[N*N];
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		if(N==1)
		{
			adj[0][0]=1;
		}
		else
		{
			int k=0;
			for(int i=0; i<N; i++)
			{
				for(int j=0; j<N; j++)
				{
					struct data *d = (struct data *) malloc(sizeof(struct data));

					d->i = i;
					d->j = j;

					pthread_create(&tid[k],&attr, runnercofacval, d);
					k++;
				}
			}
			for(int i=0; i<k; i++)
				pthread_join(tid[i],NULL);

		}
		printf("Adjoint:\n");
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<N; j++)
				printf("%d ",adj[i][j]);
			printf("\n");
		}

		int det = determinant(A, N);
		if(det==0)
		{
			printf("Inverse doesn't exist\n");
			return 0;
		}

		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++)
				inv[i][j]= adj[i][j]/((float)det);

		printf("Inverse:\n");
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<N; j++)
				printf("%f ",inv[i][j]);
			printf("\n");
		}
	}
	printf("\n");
	//printf("------------------------------------ Determinant Cofactor --------------------------------------\n");
	return 0;
}