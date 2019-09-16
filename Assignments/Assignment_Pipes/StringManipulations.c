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
		wait(NULL);
		int op = 0;
		printf("\nCopy	-	1\nConcat	-	2\nCompare	-	3\nUppercase	-	4\nLowercase	-	5\n");
		printf("Enter operation: ");
		scanf("%d", &op);

		if(op == 0)	// exit
		{
			printf("\n------------------------------------ STRING MANS --------------------------------------\n");
			return 0;
		}
		else if(op == 1)	// String Copy
		{
			char str_inp[500];
			char str_out[500];

			int fd[2];

			pipe(fd);

			if(fork()) 
			{
				close(fd[0]);

				printf("Enter input string: ");
				scanf(" %[^\n]", str_inp);

				write(fd[1], str_inp, sizeof(str_inp));

				close(fd[1]);
			} 
			else 
			{
				close(fd[1]);

				read(fd[0], str_out, sizeof(str_out));
				close(fd[0]);

				printf("\nReceived string: %s\n", str_out);
				exit(0);
				return 0;
			}
		}
		else if(op == 2)	// String Concat
		{
			char str_inp1[500];
			char str_inp2[500];
			char str_out[500];

			int fd[2];

			pipe(fd);

			if(fork()) 
			{
				close(fd[0]);

				printf("Enter input string 1: ");
				scanf("%s", str_inp1);

				write(fd[1], str_inp1, sizeof(str_inp1));

				wait(NULL);

				close(fd[1]);
			} 
			else 
			{
				close(fd[1]);

				read(fd[0], str_out, sizeof(str_out));
				close(fd[0]);

				printf("Enter input string 2: ");
				scanf("%s", str_inp2);

				strcat(str_out, str_inp2);

				printf("\nConcatinated string: %s\n", str_out);
				exit(0);
				return 0;
			}
		}
		else if(op == 3)	//String Compare
		{
			char str_inp1[500];
			

			int fd[2];

			pipe(fd);

			if(fork()) 
			{
				close(fd[0]);

				printf("Enter input string 1: ");
				scanf("%s", str_inp1);

				write(fd[1], str_inp1, sizeof(str_inp1));

				wait(NULL);

				close(fd[1]);
			} 
			else 
			{
				close(fd[1]);

				char str1[500];
				char str2[500];

				read(fd[0], str1, sizeof(str1));

				printf("Enter input string 2: ");
				scanf("%s", str2);

				if(strlen(str1) != strlen(str2)) printf("\nThe two strings do not match.\n");
				else 
				{
					int comparecheck = 1;
					for(int i=0;i<strlen(str1);i++)
					{
						if(str1[i] != str2[i])
						{
							comparecheck = 0;
							i = strlen(str1);
						}
					}
					if(comparecheck == 1) printf("\nThe two strings match.\n");
					else printf("\nThe two strings do not match.\n");
				}

				close(fd[0]);					

				exit(0);
				return 0;
			}
		}
		else if(op == 4)	//UpperCase
		{
			char str_inp[500];
			char str_out[500];

			int fd[2];

			pipe(fd);

			if(fork()) 
			{
				close(fd[0]);

				printf("Enter input string: ");
				scanf("%s", str_inp);

				write(fd[1], str_inp, sizeof(str_inp));

				wait(NULL);

				close(fd[1]);
			} 
			else 
			{
				close(fd[1]);

				read(fd[0], str_out, sizeof(str_out));

				for(int i=0;i<strlen(str_out);i++)
				{
					if((int)str_out[i] >= 97) str_out[i] -= 32;
				}
				
				printf("Uppercase String: %s", str_out);

				close(fd[0]);					

				exit(0);
				return 0;
			}
		}
		else if(op == 5)	//LowerCase
		{
			char str_inp[500];
			char str_out[500];

			int fd[2];

			pipe(fd);

			if(fork()) 
			{
				close(fd[0]);

				printf("Enter input string: ");
				scanf("%s", str_inp);

				write(fd[1], str_inp, sizeof(str_inp));

				wait(NULL);

				close(fd[1]);
			} 
			else 
			{
				close(fd[1]);

				read(fd[0], str_out, sizeof(str_out));

				for(int i=0;i<strlen(str_out);i++)
				{
					if((int)str_out[i] < 91 && (int)str_out[i] > 64) str_out[i] += 32;
				}
				
				printf("Lowercase String: %s", str_out);

				close(fd[0]);					

				exit(0);
				return 0;
			}
		}
	}
}
