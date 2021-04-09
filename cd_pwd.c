#include "minishell.h"

void	pwd_command(t_command *com)
{
	char	*a;

	a = NULL;
	a = getcwd(a, 0);
	write(1, a, ft_strlen(a));
	write(1, "\n", 1);
	free(a);
}

char	**cd_command(t_command *com, char **envp)
{
    char *oldpwd;
	char *pwd;
	char *tmp;
	int i;

	// tmp = com->arg;
	oldpwd = NULL;
	pwd = NULL;
	if (search_key(envp, "OLDPWD") == -1)
		envp = add_oldpwd(envp);
    oldpwd = getcwd(oldpwd, 0);
	errno = 0;
	if (com->arg && com->arg[0] != '-')
		chdir(com->arg);
	else if (com->arg && com->arg[0] == '-')
	{
		i = search_key(envp, "OLDPWD");
		if (i != -1 && envp[i][6] == '=')
			chdir(envp[i] + 7);
		else
			write(1, "cd: OLDPWD not set\n", 19);
	}
	else
	{
		tmp = ft_getenv(envp, "HOME");
		if (tmp)
			chdir(tmp);
		else
			write(1, "cd: HOME not set\n", 17);
	}
	if (errno != 0 && com->arg)
	{
		write(1, "cd: ", 4);
		write(1, com->arg, ft_strlen(com->arg));
		write(1, ": ", 2);
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1);
	}
	pwd = getcwd(pwd, 0);
	if (ft_strncmp(oldpwd, pwd, ft_strlen(pwd)) || ft_strncmp(oldpwd, pwd, ft_strlen(oldpwd)))
	{
		com->arg = ft_strjoin("OLDPWD=", oldpwd);
		exp_command(com, envp);
		com->arg = ft_strjoin("PWD=", pwd);
		exp_command(com, envp);
	}
	// com->arg = tmp;
	return (envp);
}