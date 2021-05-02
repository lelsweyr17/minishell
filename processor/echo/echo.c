/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:39:00 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/02 17:39:01 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/processor.h"

int	array_size(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
		i++;
	return (i);
}

void	echo_command(t_proc *com, char **envp, t_com *list, char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
		write(1, &arg[i++], 1);
	if (!list->n)
		write(1, "\n", 1);
	init_error(0, &com->error);
}
