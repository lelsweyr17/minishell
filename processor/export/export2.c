/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:39:26 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/05 21:58:14 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/processor.h"

int	ft_is_str(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}

char	**add_new_str(char **envp, int size, char *arg)
{
	char	**new;
	int		i;

	i = -1;
	new = (char **)ft_calloc(size + 1, sizeof(char *));
	while (envp[++i])
		new[i] = ft_strdup(envp[i]);
	new[i] = ft_strdup(arg);
	new[i + 1] = 0;
	free_array((void **)envp);
	return (new);
}

char	**export_add_new_object(char **envp, char *str)
{
	int		i;
	int		k;
	int		arg_len;
	int		len;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	k = search_key(envp, str);
	len = array_size(envp);
	if (k == -1)
		envp = add_new_str(envp, len + 1, str);
	else if (k >= 0 && str[i] == '=')
	{
		tmp = envp[k];
		envp[k] = ft_strdup(str);
		free(tmp);
	}
	return (envp);
}

void	if_ft_is_not_str_export(char *arg, t_proc *com)
{
	arg = change_arg_for_unset(arg);
	write_error("export", arg, "not a valid identifier");
	init_error(1, &com->error);
}

char	**exp_command(t_proc *com, char **envp, char **args)
{
	int	i;

	if (args[0])
	{
		i = -1;
		while (args[++i])
		{
			com->arg = args[i];
			if (com->arg[0] == '$' && com->arg[1])
				arg_dollar_conditions(envp, com);
			else if (!ft_is_str(com->arg))
				if_ft_is_not_str_export(com->arg, com);
			else
				envp = export_add_new_object(envp, com->arg);
		}
	}
	else
		export_sort(com, envp);
	return (envp);
}
