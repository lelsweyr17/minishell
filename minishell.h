#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
// # include "minishell_parser.h"
# include <term.h>
# include <termios.h>
# include <termcap.h>
# include <math.h>

typedef struct		s_comm
{
	char			*arg;
	int				error;
	char			**ex_port;
}					t_comm;

/* REDIRECT */
typedef struct		s_re
{
	char			*fn;
	int				type;
}					t_re;

typedef struct		s_com
{
	// t_comm			*comm;
	int				type;
	int				n;
	char			pipsem;
	int				place;
	int				pipamount;
	char			*line;
	char			**args;
	t_list			*re;
}					t_com;

typedef struct		s_par
{
	int				i;
	int				st;
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
void				pars_shift_array(char **args, int a);
int					pars_shift_line(char **line, int n);
char				*strtrim_free(char *str);
int					pars_split_commands(t_all *all);
void				pars_get_command(t_all *all);
void				pars_split_args(t_all *all);
char				*str_free(char **line, char *tmp);
int					pars_shift_line(char **line, int i);
int					isnotempty(char *str, int hash);
void				pars_free(t_all *all);

#endif