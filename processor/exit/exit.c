/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:39:15 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/04 16:48:44 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/processor.h"

int	ft_is_number(char *a)
{
	int	i;
	int	res;
	int	count;

	i = -1;
	res = 0;
	count = 1;
	if (a[0] == '-' || a[0] == '+')
		i++;
	while (a[++i])
	{
		if (ft_isdigit(a[i]))
		{
			res = res * count + (a[i] - '0');
			count = 10;
		}
		else
			return (-1);
	}
	return (res);
}

void	exit_with_many_args(t_proc *com, char *arg)
{
	if (ft_is_number(arg) != -1)
	{
		write(2, "exit\n", 5);
		write_error("exit", NULL, "too many arguments");
		init_error(1, &com->error);
	}
	else
	{
		write(2, "exit\n", 5);
		write_error("exit", arg, "numeric argument required");
		init_error(255, &com->error);
		exit(com->error);
	}
}

void	exit_if_arg_is_number(t_proc *com, long long res)
{
	res = ft_atoi(com->arg);
	if (com->arg[0] == '-')
	{
		res += __LONG_LONG_MAX__;
		res += 1;
	}
	if (res != -1)
	{
		write(2, "exit\n", 5);
		init_error(res % 256, &com->error);
		exit(com->error);
	}
	else
	{
		write(2, "exit\n", 5);
		write_error("exit", com->arg, "numeric argument required");
		init_error(255, &com->error);
		exit(com->error);
	}
}

void	exit_with_arg(t_proc *com, t_com *list, long long res)
{
	if (list->args[1] && list->args[2])
		exit_with_many_args(com, list->args[1]);
	else
	{
		res = ft_is_number(com->arg);
		if (res != -1)
			exit_if_arg_is_number(com, res);
		else
		{
			write(2, "exit\n", 5);
			write_error("exit", com->arg, "numeric argument required");
			init_error(255, &com->error);
			exit(com->error);
		}
	}
}

void	exit_command(t_proc *com, t_com *list)
{
	int			i;
	long long	res;

	com->arg = list->args[1];
	if (!com->arg)
	{
		write(2, "exit\n", 5);
		exit(com->error);
	}
	else
		exit_with_arg(com, list, res);
}
