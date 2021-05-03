/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:39:50 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/02 17:39:51 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/processor.h"

void	null_flags(t_proc *com)
{
	com->arg = 0;
	com->bin = 0;
	com->com = 0;
	com->bin_exec.path = 0;
	com->ex_port = 0;
	com->slesh = 0;
}

char	*arg_res(char **res, t_proc *com)
{
	int		i;
	char	*arg;

	i = 0;
	arg = (char *)ft_calloc(1, sizeof(char));
	arg[0] = 0;
	while (res[++i])
	{
		arg = ft_strjoin(arg, res[i]);
		if (res[i + 1])
			arg = ft_strjoin(arg, " ");
	}
	if (!ft_strlen(arg))
	{
		free(arg);
		arg = NULL;
	}
	return (arg);
}

char	**add_oldpwd(char **envp)
{
	int		i;
	int		size;
	char	**tmp;

	i = -1;
	size = array_size(envp);
	tmp = (char **)ft_calloc(size + 2, sizeof(char *));
	while (envp[++i])
		tmp[i] = ft_strdup(envp[i]);
	if (search_key(envp, "OLDPWD") == -1)
		tmp[i++] = ft_strdup("OLDPWD");
	tmp[i] = NULL;
	return (tmp);
}

void	com_export(t_proc *com, char **envp)
{
	int	len;
	int	i;

	i = -1;
	len = array_size(envp);
	com->ex_port = (char **)ft_calloc(len + 1, sizeof(char *));
	com->ex_port[len] = NULL;
	while (++i < len)
		com->ex_port[i] = envp[i];
}

void	prepare_function(t_proc *com, char **envp, char **res)
{
	null_flags(com);
	com_export(com, envp);
}
