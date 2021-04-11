#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
// # include "minishell_parser.h"
# include <term.h>
# include <termios.h>
# include <termcap.h>

typedef struct		s_comm
{
	int				echo;
	int				cd;
	int				pwd;
	int				exp;
	int				unset;
	int				env;
	int				exit;
	char			*arg;
	int				quote;
	int				double_quotes;
	int				error;
	char			**ex_port;
}					t_comm;

typedef struct		s_com
{
	// t_comm			*comm;
	int				type;
	int				n;
	char			pipsem;
	char			*line;
}					t_com;

typedef struct		s_par
{
	int				pip;
	int				sem;
}					t_par;

typedef struct		s_all
{
	t_list			*lst;
	t_par			par;
	char			*input;
	char			**env;
}					t_all;

void				parser(t_all *all); //, char **line);
int					pars_split_commands(t_all *all, char *line);
void				pars_get_command(t_all *all);

#endif