/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:40:29 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/05 22:00:11 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/processor.h"

void	write_invalid_parameter_name(t_proc *com)
{
	com->arg = change_arg_for_unset(com->arg);
	write_error("unset", com->arg, "invalid parameter name");
	init_error(1, &com->error);
}

void	write_not_a_valid_identifier(char *arg, t_proc *com)
{
	arg = change_arg_for_unset(arg);
	write_error("unset", arg, "not a valid identifier");
	init_error(1, &com->error);
}

char	*change_arg_for_unset(char *arg)
{
	char	*tmp;

	tmp = arg;
	arg = ft_strjoin("`", arg);
	free(tmp);
	tmp = arg;
	arg = ft_strjoin(arg, "'");
	free(tmp);
	return (arg);
}

char	**unset_delete_condition(char **envp, char *str, t_proc *com)
{
	int	len;
	int	num_str;

	len = array_size(envp);
	if (!ft_is_str(str))
		write_not_a_valid_identifier(str, com);
	else
	{
		num_str = search_key(envp, str);
		if (num_str != -1)
			envp = delete_str(envp, len, num_str);
	}
	return (envp);
}

char	**arg_dollar_conditions(char **envp, t_proc *com)
{
	if (ft_isdigit(com->arg[1]))
		envp = unset_dollar(com->arg + 2, com, envp, 1);
	else
		envp = unset_dollar(com->arg + 1, com, envp, 0);
	return (envp);
}
