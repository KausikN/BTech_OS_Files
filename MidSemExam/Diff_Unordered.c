#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<pthread.h>

#include <sys/time.h>

int busy = 0;

struct files
{
	char f1[100];
	char f2[100];
};
// -----------------------------------------------------------
void * runner(void *p)
{
	struct files *f = p;

	//printf("\n%s - %s\n", f->f1, f->f2);

	//while(busy == 1);
	//busy = 1;

	int pid = fork();

	if(pid == 0)
	{
		printf("\nDifference between %s and %s: \n", f->f1, f->f2);
		execlp("diff", "diff", f->f1, f->f2, NULL);
		exit(0);
	}
	wait(NULL);

	//busy = 0;

	//printf("\nDone\n");

	pthread_exit(0);
}

void PrintTime()
{
	time_t t;

	time(&t);
    printf("\nCurrent time is : %s\n", ctime(&t));
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
		    		//strcpy(f[i*no_of_files + j].f1, argv[i+1]);
		    		//strcpy(f[i*no_of_files + j].f2, argv[j+1]);
		    		strcpy(f[noofcombinations].f1, argv[i+1]);
		    		strcpy(f[noofcombinations].f2, argv[j+1]);
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
	    } 
	    /*
		pthread_t tid[no_of_files*no_of_files];
		pthread_attr_t attr;
		pthread_attr_init(&attr); 
		for (int i=0; i<no_of_files; i++)
	    { 
	    	for (int j=0; j<no_of_files; j++)
		    { 
		    	if(i<j)
		    	{
		    		pthread_create(&tid[i*no_of_files + j], &attr, runner, &f[i*no_of_files + j]);
		    	}
		    } 
	    } 

	    for (int i=0; i<no_of_files; i++)
	    { 
	    	for (int j=0; j<no_of_files; j++)
		    { 
		    	if(i<j)
		    	{
		    		pthread_join(tid[i*no_of_files + j], NULL);
		    	}
		    } 
	    } 
	    */
	}

	gettimeofday(&stop, NULL);
	secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
	printf("\nCombinations: %d  -  Exe time:  %f\n", noofcombinations, secs);

	printf("\n------------------------------------ DIFF --------------------------------------\n");
	return 0;

}
