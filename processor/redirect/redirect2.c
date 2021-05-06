/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:40:08 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/06 22:11:26 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/processor.h"

void	redirect_pipe_condition(char **env, char **arg, t_proc *com, \
	t_com *list)
{
	if (list->re)
	{
		redirect_operator(com, env, list);
		exit(com->error);
	}
	else
		pipe_command(env, list->args, com, list);
}

int	check_errno(void)
{
	if (errno)
	{
		errno = 0;
		return (0);
	}
	return (1);
}

void	return_input_output(t_proc *com)
{
	dup2(com->bin_exec.fd[0], 0);
	dup2(com->bin_exec.fd[1], 1);
}

void	init_fds_for_redirect(t_proc *com)
{
	com->bin_exec.fd[0] = -1;
	com->bin_exec.fd[1] = -1;
}
