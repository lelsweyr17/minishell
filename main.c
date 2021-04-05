#include <stdio.h>
#include <termcap.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <term.h>

int    ft_putchar(int c)
{
    return (write(1, &c, 1));
}

int main(int argc, char const *argv[], char const *envp[])
{
    char str[2000];
    int l;
    struct termios term;
    char *term_name = "xterm-256color";

    tcgetattr(0, &term);
    term.c_lflag &= ~(ECHO);
    term.c_lflag &= ~(ICANON);
    tcsetattr(0, TCSANOW, &term);
    tgetent(0, term_name);
    while (strcmp(str, "\4"))
    {
        write(1, "MSHELL-1.0-> ", 13);
        tputs(save_cursor, 1, ft_putchar);
        do
        {
            l = read(0, str, 100);
            str[l] = 0;
            if (!strcmp(str, "\e[A"))
            {
                tputs(restore_cursor, 1, ft_putchar);
                tputs(tigetstr("ed"), 1, ft_putchar);
                write(1, "previous", 8);
            }
            else if (!strcmp(str, "\e[B"))
            {
                tputs(restore_cursor, 1, ft_putchar);
                tputs(tigetstr("ed"), 1, ft_putchar);
                write(1, "next", 4);
            }
            else if (!strcmp(str, "\177"))
            {
                tputs(cursor_left, 1, ft_putchar);
                tputs(tgetstr("dc", 0), 1, ft_putchar);
            }
            else
                write(1, str, l);
        }
        while (strcmp(str, "\n") && strcmp(str, "\4"));
    }
    write(1, "\n", 1);
    return (0);
}