#include "header_commands.h"

void    redirect_output(char *com, char *file, char **envp)
{
    int stdin_0;
    int stdout_1;
    int fd;
    char *argv[2] = {"pwd", NULL};

    stdin_0 = dup(0);
    stdout_1 = dup(1);
    fd = open(file, O_RDWR | O_RDONLY | O_CREAT | O_TRUNC, 0755);
    dup2(fd, 1);
    execve(com, argv, envp);
    dup2(stdin_0, 0);
    dup2(stdout_1, 1);
    close(fd);
}

void    redirect_input(char *com, char *file, char **envp)
{
    int stdin_0;
    int stdout_1;
    int fd;
    char *argv[2] = {"pwd", NULL};

    stdin_0 = dup(0);
    stdout_1 = dup(1);
    fd = open(file, O_RDWR | O_RDONLY | O_CREAT | O_TRUNC, 0755);
    dup2(fd, 0);
    execve(com, argv, envp);
    dup2(stdin_0, 0);
    dup2(stdout_1, 1);
    close(fd);
}

int main(int argc, char **argv, char **envp)
{
    redirect_output("/bin/ls", "test", envp);
    redirect_input("", "", envp);
    return (0);
}