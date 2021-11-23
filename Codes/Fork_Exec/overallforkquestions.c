#include <stdio.h>
#include <unistd.h>
int main() 
{
    int i;
    for(i=1;i<=3;i++) 
    {
        fork();
        printf("*\n");
    }
}
// 14 processes in all with \n in redirection and 24 without redirection ---
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
    pid_t pid;
    pid=fork();
    if (pid!=0)
        fork();
    fork();
    printf("Count \n");
    return 0;
}
//6 processes in all
//----
#include<stdio.h>
#include<unistd.h>
int main()
{ 
    int i;
    for(i=0;i<2;i++)
	{
        if(fork()==0) printf("hello");
    }
}
//4 times hello printed

if (fork() == 0)
  { a = a + 5; printf(“%d,%d\n”, a, &a); }
  else { a = a –5; printf(“%d, %d\n”, a, &a); } 
(A) u = x + 10 and v = y
(B) u = x + 10 and v != y
(C) u + 10 = x and v = y
(D) u + 10 = x and v != y
c is the answer
-----
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
    pid_t pid;
    if(fork()&& fork())
    {
        fork();
    }
    if(fork()||fork())
    {
        fork();
        fork();
    }
    printf("GATE 2017");

    return 0;
}
//36 processes are  created in memory
/*
// 1 process

if(fork() && fork())  //  creates 2 more  // After first fork() only parent one will execute 2nd fork().
{
fork();    // very first parent process will get here and creates one more process.
}

===== here total process = 4.  ( 1 is new process created by 1st fork and total 3 by parent process)


if(fork() || fork())    // creates 2 more by each 4 process. Here only new child by first fork() will execute 2nd fork.
{

// 2 process reach here (original plus 1st child that tried 2nd fork above) 
fork();   
fork();

// here tota = 8 process inside this "if" body.
}

total process here = 4 * ( 1 + 8) = 36.
printf("GATE 2017");

*/
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
    if(fork() && fork()) 
        fork(); 
    if(fork() || fork()) 
        fork();
    printf("hello"); 
    return 0;
}
//20 processes

