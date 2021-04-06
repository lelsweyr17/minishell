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

typedef struct	s_command
{
	int			echo;
	int			cd;
	int			pwd;
	int			exp;
	int			unset;
	int			env;
	int			exit;
	char		*arg;
	int			quote;
	int			double_quotes;
	int			error;
	char		**ex_port;
}				t_command;

void			pwd_command(t_command *com);
char			**exp_command(t_command *com, char **envp);
int				array_size(char **ar);
int				export_equal_args(t_command *com, char **envp);
void			export_sort(t_command *com, char **envp);
void			env_command(char **envp, t_command *com);
char			**delete_str(char **envp, int size, t_command *com, int num_str);

#endif