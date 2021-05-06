/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_command4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:38:25 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/06 19:07:04 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/processor.h"

char	*from_up_to_low(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] >= 'A' && arg[i] <= 'Z')
			arg[i] += 32;
	}
	return (arg);
}

int	write_no_such_file_or_dir(t_proc *com, char *command)
{
	write_error(command, NULL, "No such file or directory");
	init_error(1, &com->error);
	return (2);
}

int	write_command_not_found(t_proc *com)
{
	write_error(com->com, NULL, "command not found");
	init_error(127, &com->error);
	return (1);
}

int	flag_check_file(t_proc *com, char *command_tmp, int *find, int *check)
{
	int	flag;

	flag = 0;
	if (!(absolute_or_relative_path(command_tmp, com)))
		*find = find_bin_command(com->bin, from_up_to_low(command_tmp), com);
	if (*find == 2)
		flag = 1;
	if (*find != 2)
		*check = check_type_of_file(com, command_tmp);
	if (*check == 2)
		flag = 1;
	return (flag);
}

int	check_file_before_exec(t_proc *com, char *command_tmp)
{
	int	flag;
	int	check;
	int	find;

	find = 0;
	check = 0;
	flag = flag_check_file(com, command_tmp, &find, &check);
	if (!find && !check)
	{
		flag = write_command_not_found(com);
		init_error(127, &com->error);
	}
	if (flag)
	{
		free_array((void **)com->bin);
		return (1);
	}
	free_array((void **)com->bin);
	return (0);
}
