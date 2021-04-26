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
	char			*line;
	char			**args;
	int				pipamount;
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
char				*str_free(char **line, char *tmp);
int					pars_shift_line(char **line, int i);
/* minishell_utils1.c */
int					isprevempty(char *str, int begin, int last);
int					isempty(char *str, int hash);
void				pars_free(t_all *all);
/* minishell_parser2.c */
void				pars_get_args(t_all *all);
void				pars_split_args(t_com *com);
char				*pars_get_next_arg(t_com *com, char **line, int *i, int s);
int					pars_get_com(t_com *com);
void				pars_cmp_com(t_com *com, char **commands);
/* minishell_parser3.c */
void				pars_echo_n(t_com *com);
void				pars_echo(t_com *com);
int					pars_get_env_value(char **line, char **env, int n, int i);
int					pars_dollar(char **line, int i, int n);
int					pars_find_quotes(char **line, char c, int i, int delescape);

int					pars_check_redirects(t_all *all, char **line, char c, int i);

int					array_size(char **ar);

#endif