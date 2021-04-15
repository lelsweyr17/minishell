#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// void    run_pipe(int *fd, char **arg, char **envp)
// {
//     dup2(fd[1], 1);
//     execve("/bin/ls", arg, envp);
//     close(fd[1]);
// }

int main(int argc, char **argv, char **envp)
{
    int i;
    int fd[2], stdin_0, stdout_1, new0;
    pid_t pid[2];
    char *argv2[2] = {"ps", NULL};
    char *argv1[3] = {"cat", "-e", NULL};
    int status;
    int options;
    i = -1;
    
    stdin_0 = dup(0);
    stdout_1 = dup(1);
    pipe(fd);
    // while (++i < 2)
    // {
        pid[0] = fork();
        if (pid[0] == 0) {
            dup2(fd[1], 1);
            execve("/bin/cat", argv1, envp);
            close(fd[1]);
        }
        pid[1] = fork();
        if (pid[1] == 0)
        {
            close(fd[1]);
            dup2(fd[0], 0);
            execve("/bin/ls", argv2, envp);
            close(fd[0]);
        }
        close(fd[0]);
        close(fd[1]);
// }
    // i = -1;
    while (++i < 2)
       waitpid(pid[i], &status, 0);
    return (0);
}