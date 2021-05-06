/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:39:00 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/06 15:19:30 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/processor.h"

void	echo_command(t_proc *com, char **envp, t_com *list, char *arg)
{
	if (arg)
		write(1, arg, ft_strlen(arg));
	if (!list->n)
		write(1, "\n", 1);
	init_error(0, &com->error);
}
