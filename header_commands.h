#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>
# include <string.h>
# include <term.h>
# include <stdlib.h>
# include "libft/libft.h" 
# include <errno.h>
# include <dirent.h>
# include "get_next_line/get_next_line.h"

typedef	struct		s_bin
{
	char			*path;
}					t_bin;

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
	char			**bin;
	char			*com;
	char			*tmp;
	t_bin			bin_exec;
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
void				write_error(char *com, char *arg, char *comment);
void				init_error(int err, int *error);
void				exit_command(t_command *com);
void				prepare_function(t_command *com, char **envp, char *line);
void				sign_flags(char *a, t_command *com);
void				free_array(char **array);
int					bin_command(t_command *com, char **envp);
void				com_export(t_command *com, char **envp);
void				null_flags(t_command *com);
char				*arg_res(char **res, t_command *com);
void    			execve_command(t_command *com, char **arg, char **envp);
char				**change_pwd(t_command *com, char **envp, char *pwd, char *oldpwd);
int					check_bin_file(char *line, char **envp, t_command *com);
char				*path_with_bin(char *path, char *com);
char				*change_arg_for_unset(char *arg);

#endif
