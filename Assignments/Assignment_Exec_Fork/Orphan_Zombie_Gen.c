#include<stdio.h>
#include<unistd.h>
#include<string.h>
//#include<process.h>


// -----------------------------------------------------------


// -----------------------------------------------------------


int main()
{
	printf("------------------------------------ ORPHAN AND ZOMBIE PROCESS GEN --------------------------------------\n");

	int pid = fork();

	if(pid == 0)
	{
		//printf("Orphan Process: \n");
		
		int pido = fork();
		if(pido > 0)	// Parent
		{
			printf("(Orphan)Parent executed..\n");
			return 0;
		}
		else if(pido == 0)	// Child
		{
			sleep(2.5);	// Wait 10

			printf("(Orphan)Child executed -- Orphan as no parent....\n\n");
			return 0;
		}

		printf("\n");
	}
	else if(pid > 0)
	{
		wait(NULL);
		//printf("Zombie Process: \n");
		
		int pidz = fork();
		
		if(pidz == 0)	// Child
		{
			printf("(Zombie)Child executed..\n");
			exit(0);
			return 0;
		}
		else if(pidz > 0)	// Parent
		{
			sleep(2.5);	// Wait 10    // Now this parent is exe but all of its children have executed already and exited

			printf("(Zombie)Parent executed -- Zombies child has already exited....\n\n");
			return 0;
		}

		printf("\n");
		printf("------------------------------------ ORPHAN AND ZOMBIE PROCESS GEN --------------------------------------\n");
		return 0;
	}

	
	
}
