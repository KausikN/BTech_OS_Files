#include<stdio.h>
#include<unistd.h>
#include<string.h>
//#include<process.h>


// -----------------------------------------------------------


// -----------------------------------------------------------


int main()
{
	printf("------------------------------------ COMMAND PROMPT --------------------------------------\n");

	char cmd[500];

	while(1)
	{
		printf("||cmd||-> ");
		scanf(" %[^\n]", cmd);
		//scanf("%s", cmd);

		if(strcmp(cmd, "exit") == 0)
		{
			printf("\n------------------------------------ COMMAND PROMPT --------------------------------------\n");
			return 0;
		}
		else 
		{
			system(cmd);
			printf("\n");
		}
	}
}
