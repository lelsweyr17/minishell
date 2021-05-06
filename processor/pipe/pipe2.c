/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:39:39 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/02 17:39:45 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/processor.h"

void	waitpid_operator(t_pipe *pip, t_proc *com)
{
	int	i;

	i = -1;
	while (++i <= pip->pipe_num)
	{
		waitpid(pip->pid[i], &com->error, WUNTRACED);
		if (i == 0)
			close(pip->fd[i][1]);
		else if (i == pip->pipe_num)
			close(pip->fd[i - 1][0]);
		else
		{
			close(pip->fd[i - 1][0]);
			close(pip->fd[i][1]);
		}
	}
}

int	pipe_number(t_list *lst)
{
	int		count;
	t_com	*list;

	count = 0;
	list = lst->content;
	while (list->pipsem == '|')
	{
		count++;
		lst = lst->next;
		list = lst->content;
	}
	return (count);
}

void	fd_pid_pipe_full(t_pipe *pip)
{
	int	i;

	i = -1;
	pip->fd = (int **)ft_calloc(pip->pipe_num + 1, sizeof(int *));
	pip->pid = (pid_t *)ft_calloc(pip->pipe_num + 1, sizeof(pid_t));
	while (++i < pip->pipe_num)
	{
		pip->fd[i] = (int *)ft_calloc(2, sizeof(int));
		pipe(pip->fd[i]);
	}
	pip->fd[i] = NULL;
	pip->std_in = dup(0);
	pip->std_out = dup(1);
}

void	pipe_command(char **env, char **arg, t_proc *com, t_com *list)
{
	if (!(ft_strncmp(arg[0], ".", 2)))
	{
		write_error(arg[0], NULL, "filename argument required");
		write(2, ".: usage: . filename [arguments]\n", 34);
		exit(2);
	}
	else
	{
		env = build_in_commands(com, env, arg, list);
		if (com->com && !bin_command(com, env))
		{
			env = check_bin_minishell(com, env);
			execve(com->bin_exec.path, arg, env);
			if (errno)
			{
				write_error(com->com, NULL, strerror(errno));
				exit(1);
			}
			else
				init_error(0, &com->error);
		}
		else
			exit(com->error);
	}
}

void	pid_child_command(t_pipe *pip, char **env, t_com *list, t_proc *com)
{
	if (pip->i == 0)
	{
		close_dup_first_command(pip->i, pip);
		redirect_pipe_condition(env, com, list);
	}
	else if (pip->i == pip->pipe_num)
	{
		close_dup_last_command(pip->i, pip);
		redirect_pipe_condition(env, com, list);
	}
	else
	{
		close_dup_middle_command(pip->i, pip);
		redirect_pipe_condition(env, com, list);
	}
	dup2(pip->std_in, 0);
	dup2(pip->std_out, 1);
}
