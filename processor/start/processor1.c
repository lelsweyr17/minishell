/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:40:14 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/04 16:15:03 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/processor.h"

char	**build_in_commands(t_proc *com, char **envp, char **arg, t_com *list)
{
	if (list->type == 1)
		echo_command(com, envp, list, arg[1]);
	else if (list->type == 2)
		envp = cd_command(com, envp, arg[1]);
	else if (list->type == 4)
		pwd_command(com);
	else if (list->type == 8)
		envp = exp_command(com, envp, arg + 1);
	else if (list->type == 16)
		envp = unset_command(com, envp, arg + 1);
	else if (list->type == 32)
		env_command(envp);
	else if (list->type == 64)
		exit_command(com, list);
	else
	{
		if (!check_build_in_with_slesh(arg[0], com, list))
			com->com = arg[0];
	}
	return (envp);
}

void	free_array(void **array)
{
	int	i;

	i = -1;
	if (array)
	{
		while (array[++i])
			free(array[i]);
		free(array);
	}
}				

char	**function(char **env, t_proc *com, t_com *list)
{
	if (!(ft_strncmp(list->args[0], ".", 2)))
	{
		write_error(list->args[0], NULL, "filename argument required");
		write(2, ".: usage: . filename [arguments]\n", 34);
		init_error(2, &com->error);
	}
	else
	{
		env = build_in_commands(com, env, list->args, list);
		if (com->com && !bin_command(com, env))
			execve_command(com, list->args, env);
	}
	return (env);
}

char	**redirect_condition(char **env, t_proc *com, t_com *list)
{
	if (list->re)
		env = redirect_operator(com, env, list);
	else
		env = function(env, com, list);
	return (env);
}

char	**processor(char **env, t_list *lst, t_proc *com)
{
	int			i;
	int			pipe_num;
	t_com		*list;

	list = lst->content;
	prepare_function(com, env, list->args);
	if (list->pipsem == '|')
	{
		pipe_num = pipe_number(lst);
		pipe_operator(pipe_num, env, lst, com);
		i = -1;
		while (++i < pipe_num)
			lst = lst->next;
	}
	else
		env = redirect_condition(env, com, list);
	free(com->ex_port);
	return (env);
}
