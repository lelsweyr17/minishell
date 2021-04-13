#include "header_commands.h"

void	cd_minus(t_command *com, char **envp)
{
	int i;

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

void	cd_home(t_command *com, char **envp)
{
	char *tmp;

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

void	cd_errno(t_command *com, char **envp)
{
	write_error("cd", com->arg, strerror(errno));
	init_error(1, &com->error);
}

void	cd_with_arg(t_command *com, char **envp)
{
	chdir(com->arg);
	init_error(0, &com->error);
}

char	**cd_command(t_command *com, char **envp)
{
    char *oldpwd;
	char *pwd;

	oldpwd = NULL;
	pwd = NULL;
    oldpwd = getcwd(oldpwd, 0);
	errno = 0;
	if (com->arg && com->arg[0] != '-')
		cd_with_arg(com, envp);
	else if (com->arg && com->arg[0] == '-')
		cd_minus(com, envp);
	else
		cd_home(com, envp);
	if (errno != 0 && com->arg)
		cd_errno(com, envp);
	pwd = getcwd(pwd, 0);
	if (ft_strncmp(oldpwd, pwd, ft_strlen(pwd)) || ft_strncmp(oldpwd, pwd, ft_strlen(oldpwd)))
		envp = change_pwd(com, envp, pwd, oldpwd);
	free(oldpwd);
	free(pwd);
	return (envp);
}