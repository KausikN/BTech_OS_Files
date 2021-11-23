
// Question 16
// Multithreaded DIFF Command

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<pthread.h>

#include <sys/time.h>

struct files
{
	char f1[100];
	char f2[100];
	int fd[2];
};

// -----------------------------------------------------------
void * runner(void *p)
{
	struct files *f = p;

	int pid = fork();

	if(pid == 0)
	{
		close(f->fd[0]);
		dup2(f->fd[1], 1);

		close(f->fd[1]);

		execlp("diff", "diff", f->f1, f->f2, NULL);
		exit(0);
	}
	wait(NULL);

	pthread_exit(0);
}

// -----------------------------------------------------------


int main(int argc, char **argv)
{
	printf("\n------------------------------------ DIFF --------------------------------------\n");

	int noofcombinations = 0;

	struct timeval start, stop;
	double secs = 0;

	gettimeofday(&start, NULL);

	if(argc < 3) printf("Wrong number of parameters.\n");
	else
	{
		int no_of_files = argc - 1;

		struct files f[no_of_files*no_of_files];

		for (int i=0; i<no_of_files; i++)
	    { 
	    	for (int j=0; j<no_of_files; j++)
		    { 
		    	if(i<j)
		    	{
		    		strcpy(f[noofcombinations].f1, argv[i+1]);
		    		strcpy(f[noofcombinations].f2, argv[j+1]);
		    		pipe(f[noofcombinations].fd);
		    		noofcombinations++;
		    	}
		    } 
	    } 

	    pthread_t tid[noofcombinations];
		pthread_attr_t attr;
		pthread_attr_init(&attr); 
		for (int i=0; i<noofcombinations; i++)
	    { 
		    pthread_create(&tid[i], &attr, runner, &f[i]);
	    } 

	    for (int i=0; i<noofcombinations; i++)
	    {
		    pthread_join(tid[i], NULL);

		    close(f[i].fd[1]);

		    printf("Difference between %s and %s: \n", f[i].f1, f[i].f2);

		    char buf[100];
		    int j;
		    while((j = read(f[i].fd[0], buf, sizeof(buf))) > 0)
			{
				printf("%s", buf);
				fflush(stdout);
			}
			printf("\n");
			close(f[i].fd[0]);
	    }

	    
	}

	gettimeofday(&stop, NULL);
	secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
	printf("\nCombinations: %d  -  Exe time:  %f\n", noofcombinations, secs);

	printf("\n------------------------------------ DIFF --------------------------------------\n");
	return 0;

}
