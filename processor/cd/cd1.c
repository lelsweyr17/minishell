/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:38:45 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/04 16:28:14 by lelsweyr         ###   ########.fr       */
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
		ft_putstr_fd(envp[i] + 7, 1);
		write(1, "\n", 1);
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

char	*pwd_not_found(t_proc *com)
{
	char	*pwd;
	char	*tmp;

	write(1, "cd: error retrieving current directory: getcwd: cannot ", 56);
	write(1, "access parent directories: No such file or directory\n", 54);
	init_error(1, &com->error);
	pwd = path_with_bin(com->pwd, com->arg);
	if (com->pwd)
		free(com->pwd);
	com->pwd = ft_strdup(pwd);
	return (pwd);
}

char	**cd_command(t_proc *com, char **envp, char *arg)
{
	int		flag;
	char	*oldpwd;
	char	*pwd;

	oldpwd = ft_strdup(com->pwd);
	com->arg = arg;
	errno = 0;
	flag = change_dir(com, envp);
	if (errno != 0 && com->arg)
		cd_errno(com);
	else
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			pwd = pwd_not_found(com);
		else if (!pwd)
			pwd = ft_strdup(com->pwd);
		if (ft_strncmp(oldpwd, pwd, ft_strlen(pwd)) || \
			ft_strncmp(oldpwd, pwd, ft_strlen(oldpwd)) || flag)
			envp = change_pwd(envp, pwd, oldpwd);
		free(pwd);
	}
	free(oldpwd);
	return (envp);
}
