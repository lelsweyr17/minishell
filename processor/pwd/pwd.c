/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:39:55 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/06 15:11:48 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/processor.h"

void	pwd_command(t_proc *com)
{
	char	*a;

	a = getcwd(NULL, 0);
	if (!a)
		a = ft_strdup(com->pwd);
	write(1, a, ft_strlen(a));
	write(1, "\n", 1);
	free(a);
}

char	**change_pwd(char **envp, char *pwd, char *oldpwd)
{
	char	*tmp;
	int		k;
	int		l;

	if (search_key(envp, "OLDPWD") == -1)
		envp = add_oldpwd(envp);
	k = search_key(envp, "OLDPWD");
	l = search_key(envp, "PWD");
	if (k != -1)
	{
		tmp = envp[k];
		envp[k] = ft_strjoin("OLDPWD=", oldpwd);
		free(tmp);
	}
	if (l != -1)
	{
		tmp = envp[l];
		envp[l] = ft_strjoin("PWD=", pwd);
		free(tmp);
	}
	return (envp);
}
