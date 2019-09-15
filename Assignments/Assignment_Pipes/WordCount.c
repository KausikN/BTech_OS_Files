#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
//#include<process.h>


// -----------------------------------------------------------


// -----------------------------------------------------------


int main()
{
	printf("------------------------------------ WORD COUNT --------------------------------------\n");

	int op = 1;

	char filename[50];
	int chars = 0, words = 0, lines = 0, sentences = 0; 

	while(1)
	{	
		if(op == 0)	// exit
		{
			printf("\n------------------------------------ WORD COUNT --------------------------------------\n");
			return 0;
		}

		chars = 0, words = 0, lines = 0, sentences = 0;

		printf("Enter the filename: ");
		scanf(" %s", filename);

		
		if(op == 1)	// Char Count
		{
			int fd[2];

			pipe(fd);

			char b[2];
			b[0] = '0';
			b[1] = '\0';

			if(fork()) 
			{
				close(fd[0]);

				char buf;

				FILE *fp;
				fp = fopen(filename, "r");
				if(fp == NULL)
				{
					printf("Error opening file\n");
					continue;
				}
				printf("\nChars:\n");
				while(fscanf(fp, "%c", &buf) != EOF)
			    {
			        printf("(%c)", buf);
			        write(fd[1], b, sizeof(b));
			    }
			    fclose(fp);
			    printf("\n");

			    b[0] = '1';
			    write(fd[1], b, sizeof(b));

			    close(fd[1]);
			} 
			else 
			{
				close(fd[1]);

				char s[2];

				while(s[0] != '1')
				{
					read(fd[0], s, sizeof(s));
					chars++;
				}
				chars--;
				
				close(fd[0]);

				printf("\nNo of Charecters: %d\n", chars);
				exit(0);
				return 0;
			}
			wait(NULL);
			op = 2;
		}
		if(op == 2)	// Word Count
		{
			int fd[2];

			pipe(fd);

			char b[2];
			b[0] = '0';
			b[1] = '\0';

			if(fork()) 
			{
				close(fd[0]);

				char word[100];

				FILE *fp;
				fp = fopen(filename, "r");
				if(fp == NULL)
				{
					printf("Error opening file\n");
					continue;
				}
				printf("\nWords:\n");
				while(fscanf(fp, "%s", word) != EOF)
			    {
			        printf("(%s)", word);
			        write(fd[1], b, sizeof(b));
			    }
			    fclose(fp);
			    printf("\n");

			    b[0] = '1';
			    write(fd[1], b, sizeof(b));

			    close(fd[1]);
			} 
			else 
			{
				close(fd[1]);

				char s[2];

				while(s[0] != '1')
				{
					read(fd[0], s, sizeof(s));
					words++;
				}
				words--;

				close(fd[0]);

				printf("\nNo of Words: %d\n", words);
				exit(0);
				return 0;
			}
			wait(NULL);
			op = 3;
		}
		if(op == 3)	// Line Count
		{
			int fd[2];

			pipe(fd);

			char b[2];
			b[0] = '0';
			b[1] = '\0';

			if(fork()) 
			{
				close(fd[0]);

				char line[100];

				FILE *fp;
				fp = fopen(filename, "r");
				if(fp == NULL)
				{
					printf("Error opening file\n");
					continue;
				}
				printf("\nLines:\n");
				while(fscanf(fp, " %[^\n]", line) != EOF)
			    {
			        printf("(%s)", line);
			        write(fd[1], b, sizeof(b));
			    }
			    fclose(fp);
			    printf("\n");

			    b[0] = '1';
			    write(fd[1], b, sizeof(b));

			    close(fd[1]);
			} 
			else 
			{
				close(fd[1]);

				char s[2];

				while(s[0] != '1')
				{
					read(fd[0], s, sizeof(s));
					lines++;
				}
				lines--;
				
				close(fd[0]);

				printf("\nNo of Lines: %d\n", lines);
				exit(0);
				return 0;
			}
			wait(NULL);
			op = 4;
		}
		if(op == 4)	// Sentence Count
		{
			int fd[2];

			pipe(fd);

			char b[2];
			b[0] = '0';
			b[1] = '\0';

			if(fork()) 
			{
				close(fd[0]);

				char sentence_char;

				FILE *fp;
				fp = fopen(filename, "r");
				if(fp == NULL)
				{
					printf("Error opening file\n");
					continue;
				}
				printf("\nSentences:\n");
				while(fscanf(fp, " %c", &sentence_char) != EOF)
			    {
			        printf("%c", sentence_char);
			        if(sentence_char == '.' || sentence_char == '\n')
		        	{
		        		write(fd[1], b, sizeof(b));
		        		printf("-", sentence_char);
		        	} 
			    }
			    fclose(fp);
			    printf("\n");

			    b[0] = '1';
			    write(fd[1], b, sizeof(b));

			    close(fd[1]);
			} 
			else 
			{
				close(fd[1]);

				char s[2];

				while(s[0] != '1')
				{
					read(fd[0], s, sizeof(s));
					sentences++;
				}
				//sentences--;
				
				close(fd[0]);

				printf("\nNo of Sentences: %d\n", sentences);
				exit(0);
				return 0;
			}
			wait(NULL);
			op = 4;
		}

		printf("\nDo you want to continue: ");
		scanf("%d", &op);
	}
}
