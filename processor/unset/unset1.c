/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:40:24 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/06 15:35:55 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/processor.h"

int	search_key(char **envp, char *arg)
{
	int	i;
	int	len;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	len = i;
	i = -1;
	while (envp[++i])
	{
		if (!(ft_strncmp(envp[i], arg, len)))
		{
			if (envp[i][len] == '=' || envp[i][len] == 0)
				return (i);
		}
	}
	return (-1);
}

char	**unset_dollar(char *arg, t_proc *com, char **envp, int flag)
{
	int		i;
	int		len;
	int		num_str;
	char	*str;
	int		start;

	i = 0;
	num_str = 0;
	str = NULL;
	str = get_dollar_arg(arg, &start, flag, envp);
	if (str && ft_strchr(str, '='))
		write_invalid_parameter_name(com);
	else if (str && ft_strlen(str))
	{
		envp = unset_delete_condition(envp, str, com);
		free(str);
	}
	else
		free(str);
	return (envp);
}

char	**unset_command(t_proc *com, char **envp, char **args)
{
	int	i;
	int	j;
	int	len;
	int	num_str;

	i = 0;
	j = -1;
	num_str = 0;
	len = array_size(envp);
	if (!args[0])
		return (envp);
	while (args[++j])
	{
		com->arg = args[j];
		while (com->arg && com->arg[i] && com->arg[i] != '=')
			i++;
		if (com->arg[0] == '$' && com->arg[1])
			envp = arg_dollar_conditions(envp, com);
		else if (com->arg && ft_strchr(com->arg, '='))
			write_invalid_parameter_name(com);
		else
			envp = unset_delete_condition(envp, com->arg, com);
	}
	return (envp);
}

char	**delete_str(char **envp, int size, int num_str)
{
	char	**new;
	int		i;
	int		j;

	i = -1;
	j = -1;
	new = (char **)ft_calloc(size, sizeof(char *));
	while (++i < size)
		if (i != num_str)
			new[++j] = envp[i];
	free(envp[num_str]);
	free(envp);
	return (new);
}
