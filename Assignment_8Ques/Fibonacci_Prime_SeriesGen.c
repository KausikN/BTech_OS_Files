#include<stdio.h>
#include<unistd.h>
#include<string.h>
//#include<process.h>


// -----------------------------------------------------------


// -----------------------------------------------------------


int main()
{
	printf("------------------------------------ FIBONACCI AND PRIME SERIES GEN --------------------------------------\n");

	int size = 0;
	printf("Enter size of series: ");
	scanf("%d", &size);

	int pid = fork();

	if(pid == 0)
	{
		printf("Fibonacci Series: ");
		int a=1,b=1;
		printf("1 1 ");
		for(int i=0;i<size;i++)
		{
			a = a + b;
			b = a - b;

			printf("%d ", a);
		}
		printf("\n");
		return 0;
	}
	else if(pid > 0)
	{
		//wait(NULL);
		printf("Prime Series: ");
		int n = 2;
		int no = 0;
		while(no < size)
		{
			int a = n-1;
			while(a > 1)
			{
				if(n%a == 0)
				{
					a=-1;
					break;
				}
				a--;
			}
			if(a > 0)
			{
				printf("%d ", n);
				no++;
			}

			n++;
		}
		printf("\n");
		printf("------------------------------------ FIBONACCI AND PRIME SERIES GEN --------------------------------------\n");
		return 0;
	}

	
	
}
