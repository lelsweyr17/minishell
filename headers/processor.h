/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:37:56 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/06 19:13:37 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSOR_H
# define PROCESSOR_H

# include "minishell.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <term.h>
# include <stdlib.h>
# include "../libft/libft.h" 
# include <errno.h>
# include <dirent.h>
# include "structs.h"

char		**add_oldpwd(char **envp);
void		save_pwd(t_proc *com);
char		**processor(char **envp, t_list *list, t_proc *com);
int			ft_is_str(char *str);
void		pwd_command(t_proc *com);
char		**cd_command(t_proc *com, char **envp, char *arg);
void		echo_command(t_proc *com, char **envp, t_com *list, char *arg);
char		*ft_getenv(char **envp, char *key);
char		**exp_command(t_proc *com, char **envp, char **arg);
int			array_size(char **ar);
int			export_equal_args(t_proc *com, char **envp);
void		export_sort(t_proc *com, char **envp);
void		env_command(char **envp);
char		**delete_str(char **envp, int size, int num_str);
char		**add_new_str(char **envp, int size, char *arg);
char		**unset_command(t_proc *com, char **envp, char **arg);
int			search_key(char **envp, char *arg);
void		write_error(char *com, char *arg, char *comment);
void		init_error(int err, int *error);
void		exit_command(t_proc *com, t_com *list);
void		prepare_function(t_proc *com, char **envp, char **res);
void		free_array(void **array);
int			bin_command(t_proc *com, char **envp);
void		com_export(t_proc *com, char **envp);
void		null_flags(t_proc *com);
char		*arg_res(char **res, t_proc *com);
void		execve_command(t_proc *com, char **arg, char **envp);
char		**change_pwd(char **envp, char *pwd, char *oldpwd);
int			absolute_or_relative_path(char *line, t_proc *com);
char		*path_with_bin(char *path, char *com);
char		*change_arg_for_unset(char *arg);
char		*get_dollar_arg(char *arg, int *start, int flag, char **env);
int			check_file_in_dir(char *path, char *command, t_proc *com);
int			find_bin_command(char **array, char *command, t_proc *com);
char		*from_up_to_low(char *arg);
int			check_file_before_exec(t_proc *com, char *command_tmp);
int			check_type_of_file(t_proc *com, char *command);
int			write_command_not_found(t_proc *com);
void		write_invalid_parameter_name(t_proc *com);
void		write_not_a_valid_identifier(char *arg, t_proc *com);
int			write_no_such_file_or_dir(t_proc *com, char *command);
char		**export_add_new_object(char **envp, char *str);
char		**export_dollar(char *arg, t_proc *com, char **envp, int flag);
char		**build_in_commands(t_proc *com, char **envp, char **arg, \
			t_com *list);
int			pipe_number(t_list *lst);
void		pipe_operator(int pipe_num, char **env, t_list *lst, t_proc *com);
void		fd_pid_pipe_full(t_pipe *pip);
void		pid_child_command(t_pipe *pip, char **env, t_com *list, \
			t_proc *com);
void		pipe_command(char **env, char **arg, t_proc *com, t_com *list);
void		close_dup_middle_command(int i, t_pipe *pip, t_proc *com);
void		close_dup_first_command(int i, t_pipe *pip, t_proc *com);
void		close_dup_last_command(int i, t_pipe *pip, t_proc *com);
void		waitpid_operator(t_pipe *pip, t_proc *com);
char		**check_bin_minishell(t_proc *com, char **env);
int			ft_is_number(char *a);
void		cd_errno(t_proc *com);
void		cd_with_arg(t_proc *com);
void		cd_in_current_dir(t_proc *com, int *flag);
int			check_build_in_with_slesh(char *arg, t_proc *com, t_com *list);
char		**arg_dollar_conditions(char **envp, t_proc *com);
char		**unset_dollar(char *arg, t_proc *com, char **envp, int flag);
char		**unset_delete_condition(char **envp, char *str, t_proc *com);
char		**redirect_operator(t_proc *com, char **env, t_com *list);
char		**function(char **env, t_proc *com, t_com *list);
void		redirect_pipe_condition(char **env, char **arg, t_proc *com, \
			t_com *list);

#endif