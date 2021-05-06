/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:40:08 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/02 17:40:09 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/processor.h"

void	redirect_pipe_condition(char **env, t_proc *com, t_com *list)
{
	if (list->re)
	{
		redirect_operator(com, env, list);
		exit(com->error);
	}
	else
		pipe_command(env, list->args, com, list);
}
