#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<stdlib.h>

#define totchars 128
//#include<process.h>


// -----------------------------------------------------------


// -----------------------------------------------------------


int main()
{
	printf("------------------------------------ CHARACTER HISTOGRAM --------------------------------------\n");

	char text[500];

	while(1)
	{

		printf("Enter the text: ");
		scanf("%s", text);

		int freq[totchars] = {0};
		// for(int i=0;i<totchars;i++)
		// {
		// 	freq[i] = 0;
		// }

		int pid = vfork();

		if(pid == 0)
		{
			for(int i=0;i<strlen(text);i++)
			{
				freq[(int)text[i]]++;
			}
			exit(0);
		}
		else if (pid > 0)
		{
			wait(NULL);

			for(int i=0;i<totchars;i++)
			{
				printf("%c (%d) ", (char)i, freq[i]);
				for(int j=0;j<freq[i];j++) printf("*");
				printf("\n");
			}

			printf("\n\n");

			int exit = 0;
			printf("Do you want to exit: ");
			scanf("%d", &exit);
			if(exit == 1)
			{
				printf("\n------------------------------------ CHARACTER HISTOGRAM --------------------------------------\n");
				return 0;
			}
		}
	}
}
