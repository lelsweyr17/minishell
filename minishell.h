#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>
# include <string.h>
# include <term.h>
# include <stdlib.h>
# include "libft/libft.h" 
# include <errno.h>

typedef struct  s_command
{
    int         echo;
    int         cd;
    int         pwd;
    int         exp;
    int         unset;
    int         env;
    int         exit;
    char        *arg;
    int         quote;
    int         double_quotes;
    int         error;
}               t_command;

#endif