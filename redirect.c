#include "header_commands.h"

void    redirect_command(char *arg1, char *arg2)
{
    int fd1;
    int fd2;
    char buf[100] = {0};

    fd1 = open(arg1, O_RDWR | O_RDONLY | O_CREAT, 0755);
    fd2 = open(arg2, O_RDWR | O_RDONLY | O_CREAT, 0755);
    printf("%d\n", fd1);
    printf("%d\n", fd2);
    // while (read(fd1, buf, 1))
    // {
    //     write(fd2, buf, 1);
    // }
    printf("%d\n", dup2(fd1, fd2));
    printf("%d\n", fd1);
    printf("%d\n", fd2);
    close(fd2);
    close(fd1);
}

int main()
{
    redirect_command("test", "test1");
    return (0);
}