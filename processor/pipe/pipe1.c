/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:39:34 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/02 17:39:35 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/processor.h"

void	close_fds(int **fd, int fd1, int fd2)
{
	int	i;

	i = -1;
	while (fd[++i])
	{
		if (fd[i][0] != fd1)
			close(fd[i][0]);
		if (fd[i][1] != fd2)
			close(fd[i][1]);
	}
}

void	close_dup_last_command(int i, t_pipe *pip, t_proc *com)
{
	close_fds(pip->fd, pip->fd[i - 1][0], -1);
	dup2(pip->fd[i - 1][0], 0);
}

void	close_dup_first_command(int i, t_pipe *pip, t_proc *com)
{
	close_fds(pip->fd, -1, pip->fd[i][1]);
	dup2(pip->fd[i][1], 1);
}

void	close_dup_middle_command(int i, t_pipe *pip, t_proc *com)
{
	close_fds(pip->fd, pip->fd[i - 1][0], pip->fd[i][1]);
	dup2(pip->fd[i - 1][0], 0);
	dup2(pip->fd[i][1], 1);
}

void	pipe_operator(int pipe_num, char **env, t_list *lst, t_proc *com)
{
	t_com	*list;
	t_pipe	*pip;

	pip = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
	pip->pipe_num = pipe_num;
	fd_pid_pipe_full(pip);
	pip->i = -1;
	while (++pip->i <= pip->pipe_num)
	{
		list = lst->content;
		pip->pid[pip->i] = fork();
		if (pip->pid[pip->i] == 0)
			pid_child_command(pip, env, list, com);
		dup2(pip->std_in, 0);
		dup2(pip->std_out, 1);
		lst = lst->next;
	}
	waitpid_operator(pip, com);
	free_array((void **)pip->fd);
	free(pip->pid);
	free(pip);
	dup2(pip->std_in, 0);
	dup2(pip->std_out, 1);
}
