#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main()
{
    printf("------------------------- BIDIRECTIONAL PIPES ---------------------------\n");

    int data_processed;

    int pipe1[2];

    int pipe2[2];

    char text_child[100];
    char text_parent[100];

    printf("Enter child text: ");
    scanf(" %[^\n]", text_child);

    printf("Enter parent text: ");
    scanf(" %[^\n]", text_parent);

    if (pipe(pipe1) == 0 && pipe(pipe2) == 0)
    {
        int pid = fork();
        if (pid == -1)
        {
            fprintf(stderr, "Fork failure");
            return 0;        
        }
        else if (pid == 0)
        {
            char buf[100];

            close(pipe1[1]);
            close(pipe2[0]);

            read(pipe1[0], buf, sizeof(buf));
            printf("\nRecv in child: %s\n", buf);

            write(pipe2[1], text_child, sizeof(text_child));

            close(pipe1[0]);
            close(pipe2[1]);
            
            exit(0);
            return 0;
        }
        else 
        {
            char buf[100];

            close(pipe1[0]);
            close(pipe2[1]);

            write(pipe1[1], text_parent, sizeof(text_parent));
            
            read(pipe2[0], buf, sizeof(buf));
            printf("\nRecv in parent: %s\n", buf);

            close(pipe1[1]);
            close(pipe2[0]);
        }
    }

    printf("\n------------------------- BIDIRECTIONAL PIPES ---------------------------\n");

    return 0;
}