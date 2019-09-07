#include<stdio.h>
#include<unistd.h>
#include<string.h>
//#include<process.h>


// -----------------------------------------------------------


// -----------------------------------------------------------


int main()
{
	printf("------------------------------------ EXEC TEST DRIVER --------------------------------------\n");

	printf("Execl  -  1\n");
	printf("Execlp -  2\n");
	printf("Execle -  3\n");
	printf("Execlpe -  4\n");
	printf("Execv  -  5\n");
	printf("Execvp  -  6\n");
	printf("Execve  -  7\n");
	printf("Execvpe -  8\n");
	printf("Exit   -  0\n");

	int choice = 0;
	printf("Enter choice: ");
	scanf("%d", &choice);

	if(choice == 1)		// Execl
	{
		char cmd_withpath[100], arg[100];

		printf("Enter cmd(with path): ");
		scanf("%s", cmd_withpath);

		int argcheck = 0;
		printf("Do you want an argument: ");
		scanf("%d", &argcheck);

		if(argcheck == 1) 
		{
			printf("Enter an argument: ");
			scanf("%s", arg);
			execl(cmd_withpath, arg, (char *)NULL);
		}
		else execl(cmd_withpath, "", (char *)NULL);
	}

	else if(choice == 2)		// Execlp
	{
		char cmd_withoutpath[100], arg[100];

		printf("Enter cmd(without path): ");
		scanf("%s", cmd_withoutpath);

		int argcheck = 0;
		printf("Do you want a argument: ");
		scanf("%d", &argcheck);

		if(argcheck == 1) 
		{
			printf("Enter an argument: ");
			scanf("%s", arg);
			execlp(cmd_withoutpath, arg, (char *)NULL);
		}
		else execlp(cmd_withoutpath, "", (char *)NULL);
	}

	else if(choice == 3)		// Execle
	{
		char cmd_withpath[100], arg[100];
		char env[100][100];

		printf("Enter cmd(with path): ");
		scanf("%s", cmd_withpath);

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
			printf("Enter an argument: ");
			scanf("%s", arg);
			execle(cmd_withpath, arg, (char *)NULL, env);
		}
		else execle(cmd_withpath, "", (char *)NULL, env);
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
		char arg[100][100];

		printf("Enter cmd(with path): ");
		scanf("%s", cmd_withpath);

		int noofargs = 0;
		printf("Enter no of args: ");
		scanf("%d", &noofargs);

		if(noofargs > 0) printf("Enter the args: ");
		for(int i=0;i<noofargs;i++) scanf("%s", arg[i]);
		arg[noofargs][0] = '\0';

		execv(cmd_withpath, arg);
	}

	else if(choice == 6)		// Execvp
	{
		char cmd_withoutpath[100];
		char arg[100][100];

		printf("Enter cmd(without path): ");
		scanf("%s", cmd_withoutpath);

		int noofargs = 0;
		printf("Enter no of args: ");
		scanf("%d", &noofargs);

		if(noofargs > 0) printf("Enter the args: ");
		for(int i=0;i<noofargs;i++) scanf("%s", arg[i]);
		arg[noofargs][0] = '\0';

		execvp(cmd_withoutpath, arg);
	}

	else if(choice == 7)		// Execve
	{
		char cmd_withpath[100];
		char arg[100][100];
		char env[100][100];

		printf("Enter cmd(with path): ");
		scanf("%s", cmd_withpath);

		int noofenvs = 0;
		printf("Enter no of env vars: ");
		scanf("%d", &noofenvs);

		if(noofenvs > 0) printf("Enter the env vars: ");
		for(int i=0;i<noofenvs;i++) scanf("%s", env[i]);
		env[noofenvs][0] = '\0';

		int noofargs = 0;
		printf("Enter no of args: ");
		scanf("%d", &noofargs);

		if(noofargs > 0) printf("Enter the args: ");
		for(int i=0;i<noofargs;i++) scanf("%s", arg[i]);
		arg[noofargs][0] = '\0';

		execve(cmd_withpath, arg, env);
	}

	else if(choice == 8)		// Execvpe
	{
		char cmd_withoutpath[100];
		char arg[100][100];
		char env[100][100];

		printf("Enter cmd(without path): ");
		scanf("%s", cmd_withoutpath);

		int noofenvs = 0;
		printf("Enter no of env vars: ");
		scanf("%d", &noofenvs);

		if(noofenvs > 0) printf("Enter the env vars: ");
		for(int i=0;i<noofenvs;i++) scanf("%s", env[i]);
		env[noofenvs][0] = '\0';

		int noofargs = 0;
		printf("Enter no of args: ");
		scanf("%d", &noofargs);

		if(noofargs > 0) printf("Enter the args: ");
		for(int i=0;i<noofargs;i++) scanf("%s", arg[i]);
		arg[noofargs][0] = '\0';

		execvpe(cmd_withoutpath, arg, env);
	}

	else if(choice == 0)
	{
		printf("------------------------------------ EXEC TEST DRIVER --------------------------------------\n");
		return 0;
	}


	printf("------------------------------------ EXEC TEST DRIVER --------------------------------------\n");
	return 0;
}
