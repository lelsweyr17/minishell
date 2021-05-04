/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:39:55 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/04 15:26:53 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/processor.h"

void	pwd_command(void)
{
	char	*a;

	a = getcwd(NULL, 0);
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
	tmp = envp[k];
	envp[k] = ft_strjoin("OLDPWD=", oldpwd);
	free(tmp);
	tmp = envp[l];
	envp[l] = ft_strjoin("PWD=", pwd);
	free(tmp);
	return (envp);
}
