#ifndef HEADER_COMMANDS_H
# define HEADER_COMMANDS_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
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

typedef struct s_bin
{
	char	*path;
}	t_bin;

typedef struct s_command
{	
	int		echo_n;
	char	*arg;
	int		no_quotes;
	int		quote;
	int		double_quotes;
	int		error;
	int		slesh;
	char	**ex_port;
	char	**bin;
	char	*com;
	char	*tmp;
	t_bin	bin_exec;
}	t_command;

int			ft_is_str(char *str);
void		pwd_command(t_command *com);
char		**cd_command(t_command *com, char **envp);
void		echo_command(t_command *com, char **envp);
char		*ft_getenv(char **envp, char *key);
char		**exp_command(t_command *com, char **envp, char **arg);
int			array_size(char **ar);
int			export_equal_args(t_command *com, char **envp);
void		export_sort(t_command *com, char **envp);
void		env_command(char **envp, t_command *com);
char		**delete_str(char **envp, int size, t_command *com, int num_str);
char		**add_new_str(char **envp, int size, t_command *com, char *arg);
char		**unset_command(t_command *com, char **envp, char **arg);
int			search_key(char **envp, char *arg);
char		**add_oldpwd(char **envp);
void		write_error(char *com, char *arg, char *comment);
void		init_error(int err, int *error);
void		exit_command(t_command *com);
void		prepare_function(t_command *com, char **envp, char **res);
void		free_array(char **array);
int			bin_command(t_command *com, char **envp);
void		com_export(t_command *com, char **envp);
void		null_flags(t_command *com);
char		*arg_res(char **res, t_command *com);
void		execve_command(t_command *com, char **arg, char **envp);
char		**change_pwd(t_command *com, char **envp, char *pwd, char *oldpwd);
int			absolute_or_relative_path(char *line, char **envp, t_command *com);
char		*path_with_bin(char *path, char *com);
char		*change_arg_for_unset(char *arg);
char		*get_dollar_arg(char *arg, int *start, int flag);
int			check_file_in_dir(char *path, char *command, t_command *com);
int			find_bin_command(char **array, char *command, t_command *com);
char		*from_up_to_low(char *arg);
int			check_file_before_exec(char **envp, t_command *com, \
	char *command_tmp);
int			check_type_of_file(char **envp, t_command *com, char *command);
void		write_command_not_found(t_command *com);

#endif
