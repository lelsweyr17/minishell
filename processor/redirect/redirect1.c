/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:40:02 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/06 15:19:43 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/processor.h"

int	redirect_input(t_proc *com, t_re *re)
{
	if (com->bin_exec.fd[0] != -1)
		close(com->bin_exec.fd[0]);
	com->bin_exec.fd[0] = open(re->fn, O_RDONLY);
	if (com->bin_exec.fd[0] < 0)
	{
		write_no_such_file_or_dir(com, re->fn);
		close(com->bin_exec.fd[0]);
		return (0);
	}
	return (1);
}

void	redirect_output(t_proc *com, t_re *re)
{
	if (com->bin_exec.fd[1] != -1)
		close(com->bin_exec.fd[1]);
	com->bin_exec.fd[1] = open(re->fn, O_RDWR | O_RDONLY \
	| O_CREAT | O_TRUNC, 0644);
}

void	double_redirect_output(t_proc *com, t_re *re)
{
	if (com->bin_exec.fd[1] != -1)
		close(com->bin_exec.fd[1]);
	com->bin_exec.fd[1] = open(re->fn, O_RDWR | O_RDONLY \
	| O_CREAT | O_APPEND, 0644);
}

int	redirect_iterator(t_proc *com, t_com *list)
{
	t_re		*re;
	t_list		*begin;

	begin = list->re;
	com->bin_exec.fd[0] = -1;
	com->bin_exec.fd[1] = -1;
	while (list->re)
	{
		re = list->re->content;
		if (re->type == 2)
		{
			if (!(redirect_input(com, re)))
				return (0);
		}
		else if (re->type == 1)
			redirect_output(com, re);
		else if (re->type == 3)
			double_redirect_output(com, re);
		list->re = list->re->next;
	}
	dup2(com->bin_exec.fd[0], 0);
	dup2(com->bin_exec.fd[1], 1);
	list->re = begin;
	return (1);
}

char	**redirect_operator(t_proc *com, char **env, t_com *list)
{
	com->bin_exec.std_in = dup(0);
	com->bin_exec.std_out = dup(1);
	if (!(redirect_iterator(com, list)))
		return (env);
	if (list->pipsem == '|')
		pipe_command(env, list->args, com, list);
	else
		env = function(env, com, list);
	if (com->bin_exec.fd[0])
		close(com->bin_exec.fd[0]);
	if (com->bin_exec.fd[1])
		close(com->bin_exec.fd[1]);
	dup2(com->bin_exec.std_in, 0);
	dup2(com->bin_exec.std_out, 1);
	return (env);
}
