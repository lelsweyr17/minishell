#include "header_commands.h"

void    pipe_command()
{

}

int main(int argc, char **argv, char **envp)
{
    char a[100];
    int fd[2];
    pid_t pid;
    char *arg[3];
    arg[0] = "ls";
    arg[1] = "-la";
    arg[2] = NULL;

    pid = fork();
    if (pid == 0)
    {
        pipe(fd);
        printf("%d - %d\n", fd[0], fd[1]);
        dup2(fd[1], 1);
        execve("/bin/ls", arg, envp);
        close(fd[1]);
    }
    else
        wait(&pid);
    printf("Finish\n");
}