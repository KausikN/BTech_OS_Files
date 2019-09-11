#include<stdio.h>
#include<unistd.h>
#include<string.h>
//#include<process.h>


// -----------------------------------------------------------


// -----------------------------------------------------------


int main()
{
	printf("------------------------------------ EXEC TEST DRIVER --------------------------------------\n");
	
	int choice = 1;
	
	while(choice != 0)
	{
		printf("Execl  -  1\n");
		printf("Execlp -  2\n");
		printf("Execle -  3\n");
		//printf("Execlpe -  4\n");
		printf("Execv  -  5\n");
		printf("Execvp  -  6\n");
		printf("Execve  -  7\n");
		//printf("Execvpe -  8\n");
		printf("Exit   -  0\n");

	
		printf("Enter choice: ");
		scanf("%d", &choice);

		if(choice == 1)		// Execl
		{
			char cmd_withpath[100];
			char arg[100];

			printf("Enter cmd(with path): ");
			scanf("%s", cmd_withpath);

			int argcheck = 0;
			printf("Do you want an argument: ");
			scanf("%d", &argcheck);

			if(argcheck != 0) 
			{
				printf("Enter an argument: ");
				scanf("%s", arg);
				execl(cmd_withpath, cmd_withpath, arg, (char *)NULL);
			}
			else execl(cmd_withpath, cmd_withpath, "", (char *)NULL);
		}

		else if(choice == 2)		// Execlp
		{
			char cmd_withoutpath[100], arg[100];

			printf("Enter cmd(without path): ");
			scanf("%s", cmd_withoutpath);

			int argcheck = 0;
			printf("Do you want a argument: ");
			scanf("%d", &argcheck);

			if(argcheck != 0) 
			{
				printf("Enter an argument: ");
				scanf("%s", arg);
				execlp(cmd_withoutpath, cmd_withoutpath, arg, (char *)NULL);
			}
			else execlp(cmd_withoutpath, cmd_withoutpath, "", (char *)NULL);
		}

		else if(choice == 3)		// Execle
		{
			char cmd_withpath[100], arg[100];
			char *env[] = {"PORT=9009", NULL};

			printf("Enter cmd(with path): ");
			scanf("%s", cmd_withpath);

			int argcheck = 0;
			printf("Do you want a argument: ");
			scanf("%d", &argcheck);

			if(argcheck != 0) 
			{
				printf("Enter an argument: ");
				scanf("%s", arg);
				execle(cmd_withpath, cmd_withpath, arg, (char *)NULL, env);
			}
			else execle(cmd_withpath, cmd_withpath, "", (char *)NULL, env);
		}
	/*
		else if(choice == 4)		// Execlpe
		{
			char cmd_withoutpath[100], arg[100];
			char *env[100] = {NULL};

			printf("Enter cmd(without path): ");
			scanf("%s", cmd_withoutpath);

			int noofenvs = 0;
			printf("Enter no of env vars: ");
			scanf("%d", &noofenvs);

			if(noofenvs > 0) printf("Enter the env vars: ");
			for(int i=0;i<noofenvs;i++) scanf("%s", env[i]);
			env[noofenvs][0] = '\0';

			int argcheck = 0;
			printf("Do you want a argument: ");
			scanf("%d", &argcheck);

			if(argcheck == 1) 
			{
				scanf("%s", arg);
				execlpe(cmd_withoutpath, arg, (char *)NULL, env);
			}
			else execlpe(cmd_withoutpath, "", (char *)NULL, env);
		}
	*/
		else if(choice == 5)		// Execv
		{
			char cmd_withpath[100];

			printf("Enter cmd(with path): ");
			scanf("%s", cmd_withpath);

			int noofargs = 0;
			printf("Enter no of args: ");
			scanf("%d", &noofargs);
			
			char arg[100];
			char *argp[noofargs+2];

			if(noofargs > 0) printf("Enter the args: ");

			argp[0] = cmd_withpath;
			for(int i=0;i<noofargs;i++)
			{
				scanf("%s", arg);
				argp[i+1] = arg;
			} 
			argp[noofargs+1] = (char *)NULL;

			execv(cmd_withpath, argp);
		}

		else if(choice == 6)		// Execvp
		{
			char cmd_withoutpath[100];

			printf("Enter cmd(without path): ");
			scanf("%s", cmd_withoutpath);

			int noofargs = 0;
			printf("Enter no of args: ");
			scanf("%d", &noofargs);
			
			char arg[100];
			char *argp[noofargs+2];

			if(noofargs > 0) printf("Enter the args: ");

			argp[0] = cmd_withoutpath;
			for(int i=0;i<noofargs;i++)
			{
				scanf("%s", arg);
				argp[i+1] = arg;
			} 
			argp[noofargs+1] = (char *)NULL;

			execvp(cmd_withoutpath, argp);
		}

		else if(choice == 7)		// Execve
		{
			char cmd_withpath[100];
			char *env[] = {"PORT=9009", NULL};

			printf("Enter cmd(with path): ");
			scanf("%s", cmd_withpath);

			int noofargs = 0;
			printf("Enter no of args: ");
			scanf("%d", &noofargs);
			
			char arg[100];
			char *argp[noofargs+2];

			if(noofargs > 0) printf("Enter the args: ");

			argp[0] = cmd_withpath;
			for(int i=0;i<noofargs;i++)
			{
				scanf("%s", arg);
				argp[i+1] = arg;
			} 
			argp[noofargs+1] = (char *)NULL;

			execve(cmd_withpath, argp, env);
		}
		/*
		else if(choice == 8)		// Execvpe
		{
			char cmd_withoutpath[100];
			char *env[] = {"PORT=9009", NULL};

			printf("Enter cmd(without path): ");
			scanf("%s", cmd_withoutpath);

			int noofargs = 0;
			printf("Enter no of args: ");
			scanf("%d", &noofargs);
			
			char arg[100];
			char *argp[noofargs+2];

			if(noofargs > 0) printf("Enter the args: ");

			argp[0] = cmd_withoutpath;
			for(int i=0;i<noofargs;i++)
			{
				scanf("%s", arg);
				argp[i+1] = arg;
			} 
			argp[noofargs+1] = (char *)NULL;

			execvpe(cmd_withoutpath, argp, env);
		}
		*/
	}

	printf("------------------------------------ EXEC TEST DRIVER --------------------------------------\n");
	return 0;
}
