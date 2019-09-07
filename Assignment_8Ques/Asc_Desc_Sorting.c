#include<stdio.h>
#include<unistd.h>
#include<string.h>
//#include<process.h>


// -----------------------------------------------------------


// -----------------------------------------------------------


int main()
{
	printf("------------------------------------ ASCENDING AND DESCENDING ORDER SORTING --------------------------------------\n");

	int size = 0;
	printf("Enter size of array: ");
	scanf("%d", &size);

	printf("Enter the array: ");
	int arr[size];
	for(int i=0;i<size;i++)
	{
		scanf("%d", &arr[i]);
	}

	int pid = fork();

	if(pid == 0)
	{
		printf("Descending order: ");
		
		for(int i=0;i<size;i++)
		{
			int max_i = i;
			for(int j=i;j<size;j++)
			{
				if(arr[j] > arr[max_i])
				{
					max_i = j;
				}
			}
			int temp = arr[max_i];
			arr[max_i] = arr[i];
			arr[i] = temp;
		}

		for(int i=0;i<size;i++) printf("%d ", arr[i]);

		printf("\n");
		return 0;
	}
	else if(pid > 0)
	{
		wait(NULL);
		printf("Ascending order: ");
		
		for(int i=0;i<size;i++)
		{
			int max_i = 0;
			for(int j=0;j<size-i;j++)
			{
				if(arr[j] > arr[max_i])
				{
					max_i = j;
				}
			}

			int temp = arr[max_i];
			arr[max_i] = arr[size - i - 1];
			arr[size - i - 1] = temp;
		}

		for(int i=0;i<size;i++) printf("%d ", arr[i]);

		printf("\n");
		printf("------------------------------------ ASCENDING AND DESCENDING ORDER SORTING --------------------------------------\n");
		return 0;
	}

	
	
}
