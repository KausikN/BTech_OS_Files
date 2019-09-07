#include<stdio.h>
#include<unistd.h>
#include<string.h>
//#include<process.h>


// -----------------------------------------------------------


// -----------------------------------------------------------


int main()
{
	printf("------------------------------------ ODD EVEN SERIES GEN --------------------------------------\n");

	int size = 0;
	printf("Enter size of series: ");
	scanf("%d", &size);

	int pid = fork();

	if(pid == 0)
	{
		printf("Even Series: ");
		for(int i=0;i<size;i++)
		{
			printf("%d ", 2*i);
		}
		printf("\n");
		return 0;
	}
	else if(pid > 0)
	{
		wait(NULL);
		printf("Odd Series: ");
		for(int i=0;i<size;i++)
		{
			printf("%d ", 2*i+1);
		}
		printf("\n");
		printf("------------------------------------ ODD EVEN SERIES GEN --------------------------------------\n");
		return 0;
	}

	
	
}
