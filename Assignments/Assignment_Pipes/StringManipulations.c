#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
//#include<process.h>


// -----------------------------------------------------------


// -----------------------------------------------------------


int main()
{
	printf("------------------------------------ STRING MANS --------------------------------------\n");

	while(1)
	{
		int op = 0;
		printf("\nCopy	-	1\nConcat	-	2\nCompare	-	3\nUppercase	-	4\nLowercase	-	5\n");
		printf("Enter operation: ");
		scanf("%d", &op);

		if(op == 0)	// exit
		{
			printf("\n------------------------------------ STRING MANS --------------------------------------\n");
			return 0;
		}
		else if(op == 1)
		{
			char str_inp[500];
			char str_out[500];

			int fd[2];

			pipe(fd);

			if(fork()) 
			{
				// parent process closes the read end
				close(fd[0]);

				printf("Enter input string: ");
				scanf(" %[^\n]", str_inp);

				// puts data in pipe
				write(fd[1], str_inp, sizeof(str_inp));

				close(fd[1]);
			} 
			else 
			{
				// Child process closes the write end
				close(fd[1]);

				// reads from the pipe
				read(fd[0], str_out, sizeof(str_out));
				close(fd[0]);

				// output the received string
				printf("\nReceived string: %s\n", str_out);
				exit(0);
				return 0;
			}
		}
		else if(op == 2)
		{
			char str_inp[500];
			char str_out[500];

			int fd[2];

			pipe(fd);

			if(fork()) 
			{
				// parent process closes the read end
				close(fd[0]);

				printf("Enter input string: ");
				scanf(" %[^\n]", str_inp);

				// puts data in pipe
				write(fd[1], str_inp, sizeof(str_inp));

				close(fd[1]);
			} 
			else 
			{
				// Child process closes the write end
				close(fd[1]);

				// reads from the pipe
				read(fd[0], str_out, sizeof(str_out));
				close(fd[0]);

				// output the received string
				printf("\nReceived string: %s\n", str_out);
				exit(0);
				return 0;
			}
		}
	}
}
