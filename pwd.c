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

char    *str_free(char **line, char *tmp)
{
    free(*line);
    return (tmp);
}

char	**change_pwd(t_command *com, char **envp, char *pwd, char *oldpwd)
{
	char *tmp;
	int k;
	int l;
	int len;

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
