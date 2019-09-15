#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
//#include<process.h>


// -----------------------------------------------------------


// -----------------------------------------------------------


int main()
{
	printf("------------------------------------ PALINDROME CHECK --------------------------------------\n");

	int ex = 0;

	char text[500];
	int text_size = 0;

	while(ex == 0)
	{
		printf("Enter string: ");
		scanf("%s", text);

		text_size = strlen(text);

		char text_rev[500];

		int fd[2];

		pipe(fd);

		if(fork()) 
		{
			close(fd[0]);

			char buf[2];
			buf[0] = '1';
			buf[1] = '\0';
			int index = text_size-1;
			while(index >= 0)
			{
				//printf("\n\n%c(%d/%d)\n\n", text[index], index, text_size);
				buf[0]  = text[index];
				index--;
				if(buf[0] == '\0') break;
				write(fd[1], buf, sizeof(buf));
			}

			close(fd[1]);
			wait(NULL);
		} 
		else 
		{
			int check = 1;

			close(fd[1]);

			char buf[2];
			buf[0] = '1';
			buf[1] = '\0';
			int index = 0;
			printf("Reversed String:\n");
			while(index < text_size)
			{
				read(fd[0], buf, sizeof(buf));
				if(buf[0] == '\0') break;
				else if(buf[0] != text[index]) check = 0;
				printf("%c", buf[0]);
				index++;
			}
			printf("\n");

			close(fd[0]);

			printf("Original String: %s\n", text);

			if(check == 1) printf("\nIt is a palindrome.\n");
			else printf("\nIt is not a palindrome.\n");
			exit(0);
			return 0;
		}
	}

	printf("\n------------------------------------ STRING MANS --------------------------------------\n");
	return 0;
}
