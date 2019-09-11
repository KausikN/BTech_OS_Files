#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    char *path = "/bin/ls";
    char *arg0 = "ls";
    pid_t pid;
    int pipefd[2];
    int status;
    pipe(pipefd);
    pid = fork();
    if (pid == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        if (execl(path, arg0, NULL) == -1)
            perror("execl");
    } else {
        if (fork() == 0) {
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            close(pipefd[1]);
            if (execl("/bin/cat", "cat", NULL) == -1)
                perror("execl cat");
        } else {
            close(pipefd[0]);
            close(pipefd[1]);
            wait(&status);
            wait(&status);
        }
    }
}
