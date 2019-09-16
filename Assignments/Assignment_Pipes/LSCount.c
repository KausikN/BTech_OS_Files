#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
//#include<process.h>


// -----------------------------------------------------------


// -----------------------------------------------------------


int main()
{
	printf("------------------------------------ LS COUNT --------------------------------------\n");

	int op = 1;

	char filename[50];
	int chars = 0, words = 0, lines = 0, sentences = 0; 

	while(1)
	{	
		if(op == 0)	// exit
		{
			printf("\n------------------------------------ LS COUNT --------------------------------------\n");
			return 0;
		}

		chars = 0, words = 0, lines = 0;

		int fd[2];

		pipe(fd);


		if(fork()) 
		{
			wait(NULL);

			int words = 0, chars = 0, lines = 0;

			close(fd[1]);

			char buf[100];

			printf("\n");
			int j;
			while((j = read(fd[0], buf, sizeof(buf))) > 0)
			{
				int index = 0;
				while(index < j)
				{
					printf("%c", buf[index]);
					if(buf[index] == ' ')
					{
						words++;
					}
					else if(buf[index] == '\n')
					{
						words++;
						lines++;
					}
					chars++;

					index++;
				}
			}

			printf("\nOutput has %d chars, %d words, %d lines.\n No of files: %d", chars, words, lines, words);

			
		} 
		else 
		{
			close(fd[0]);

			dup2(fd[1], 1);
			system("ls");

		    close(fd[1]);
			
			exit(0);
			return 0;
		}
			

		printf("\nDo you want to continue: ");
		scanf("%d", &op);
	}
}
