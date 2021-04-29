#include "../../headers/processor.h"

void	shlvl_pointer_change(int *shlvl)
{
	if (*shlvl < 999 && *shlvl >= 0)
		*shlvl += 1;
	else if (*shlvl == 999)
		*shlvl = 0;
	else if (*shlvl < 0)
		*shlvl = -1;
	else
	{
		write(2, "minishell: warning: shell level (", 33);
		ft_putnbr_fd((*shlvl + 1), 2);
		write(2, ") too high, resetting to 1\n", 28);
		*shlvl = 1;
	}
}

char	**add_new_arg_shlvl(int shlvl, char **envp, int i)
{
	char	*tmp;
	char	*tmp2;

	if (shlvl == 0)
	{
		envp[i][5] = '=';
		envp[i][6] = 0;
	}
	else if (shlvl == -1)
	{
		envp[i][5] = '=';
		envp[i][6] = '0';
		envp[i][7] = 0;
	}
	else
	{
		tmp = ft_itoa(shlvl);
		tmp2 = ft_strjoin("SHLVL=", tmp);
		envp = export_add_new_object(envp, tmp2);
		free(tmp);
		free(tmp2);
	}
	return (envp);
}

char	**change_shlvl(char **envp)
{
	int		i;
	int		shlvl;
	char	*str;

	i = search_key(envp, "SHLVL");
	str = envp[i] + 6;
	if (ft_is_number(str))
		shlvl = ft_atoi(str);
	else
		shlvl = 0;
	shlvl_pointer_change(&shlvl);
	envp = add_new_arg_shlvl(shlvl, envp, i);
	return (envp);
}

char	**change_oldpwd(char **envp)
{
	int	i;

	i = search_key(envp, "OLDPWD");
	if (i != -1)
		envp[i][6] = 0;
	else
		envp = add_oldpwd(envp);
	return (envp);
}

char	**check_bin_minishell(t_proc *com, char **env)
{
	char	*a;

	a = com->bin_exec.path + ft_strlen(com->bin_exec.path) - 9;
	if (!(ft_strncmp(a, "minishell", 10)))
	{
		env = change_shlvl(env);
		env = change_oldpwd(env);
	}
	return (env);
}
