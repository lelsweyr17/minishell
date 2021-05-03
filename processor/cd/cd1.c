/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:38:45 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/03 17:37:48 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/processor.h"

void	cd_minus(t_proc *com, char **envp)
{
	int	i;

	i = search_key(envp, "OLDPWD");
	if (i != -1 && envp[i][6] == '=')
	{
		chdir(envp[i] + 7);
		init_error(0, &com->error);
	}
	else
	{
		write_error("cd", NULL, "OLDPWD not set");
		init_error(1, &com->error);
	}
}

void	cd_home(t_proc *com)
{
	char	*tmp;

	tmp = getenv("HOME");
	if (tmp)
	{
		chdir(tmp);
		init_error(0, &com->error);
	}
	else
	{
		write_error("cd", NULL, "HOME not set");
		init_error(1, &com->error);
	}
}

int	change_dir(t_proc *com, char **envp)
{
	int	flag;

	flag = 1;
	if (com->arg && com->arg[0] == '-' && com->arg[1] == 0)
		cd_minus(com, envp);
	else if (com->arg && com->arg[0] == '.' && com->arg[1] == 0)
		cd_in_current_dir(com, &flag);
	else if (com->arg && com->arg[0] == '-' && com->arg[1] == '-' \
		&& com->arg[2] == 0)
		cd_home(com);
	else if (com->arg && com->arg[0] == '~' && com->arg[1] == 0)
		cd_home(com);
	else if (!com->arg)
		cd_home(com);
	else if (com->arg && com->arg[0] != '-' && com->arg[1] == 0)
		cd_with_arg(com);
	else
		chdir(com->arg);
	return (flag);
}

void	pwd_not_found(t_proc *com)
{
	char	*tmp;
	char	*cur;

	cur = getcwd(NULL, 0);
	if (!cur)
	{
		write(1, "cd: error retrieving current directory: getcwd: cannot", 55);
		write(1, " access parent directories: No such file or directory\n", 54);
		com->pwd = ft_strjoin(com->pwd, "/..");
	}
	else
		com->pwd = ft_strdup(cur);
	free(cur);
}

char	**cd_command(t_proc *com, char **envp, char *arg)
{
	int		flag;
	char	*oldpwd;
	char	*pwd;

	oldpwd = ft_strdup(com->pwd);
	errno = 0;
	com->arg = arg;
	flag = change_dir(com, envp);
	if (errno != 0 && com->arg)
		cd_errno(com);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd_not_found(com);
		return (envp);
	}
	if (ft_strncmp(oldpwd, pwd, ft_strlen(pwd)) || \
		ft_strncmp(oldpwd, pwd, ft_strlen(oldpwd)) || flag)
		envp = change_pwd(envp, pwd, oldpwd);
	free(oldpwd);
	free(pwd);
	return (envp);
}
