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
# include "get_next_line/get_next_line.h"

typedef	struct		s_env
{	
	char			*key;
	char			*arg;
	int				equal;
	struct s_env	*next;
}					t_env;



typedef struct		s_command
{	
	int				echo;
	int				echo_n;
	int				cd;
	int				pwd;
	int				exp;
	int				unset;
	int				env;
	int				exit;
	char			*arg;
	int				no_quotes;
	int				quote;
	int				double_quotes;
	int				error;
	char			**ex_port;
	t_env			*env_list;
	char			**bin;
}					t_command;

void				pwd_command(t_command *com);
char				**cd_command(t_command *com, char **envp);
void				echo_command(t_command *com, char **envp);
char				*ft_getenv(char **envp, char *key);
char				**exp_command(t_command *com, char **envp);
int					array_size(char **ar);
int					export_equal_args(t_command *com, char **envp);
void				export_sort(t_command *com, char **envp);
void				env_command(char **envp, t_command *com);
char				**delete_str(char **envp, int size, t_command *com, int num_str);
char				**add_new_str(char **envp, int size, t_command *com);
char				**unset_command(t_command *com, char **envp);
int					search_key(char **envp, char *arg);
char				**add_oldpwd(char **envp);


#endif