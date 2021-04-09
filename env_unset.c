#include "minishell.h"

void	env_command(char **envp, t_command *com)
{
	int	i;
	int num_str;

	i = -1;
	while (envp[++i])
	{
		if (ft_strrchr(envp[i], '='))
		{
			write(1, envp[i], ft_strlen(envp[i]));
			write(1, "\n", 1);
		}
	}
}

int		search_key(char **envp, char *arg)
{
	int i;
	int len;

	i = 0;
	while (arg[i])
		i++;
	len = i;
	i = -1;
	while (envp[++i])
	{
		if (!(ft_strncmp(envp[i], arg, len)))
		{
			if (envp[i][len] == '=' || envp[i][len] == 0)
				return (i);
		}
	}
	return (-1);
}

char	**unset_command(t_command *com, char **envp)
{
	int i;
	int len;
	int num_str;

	i = 0;
	num_str = 0;
	len = array_size(envp);
	while (com->arg && com->arg[i] && com->arg[i] != '=')
		i++;
	if (com->arg && ft_strchr(com->arg, '='))
	{
		write_error("unset", com->arg, "invalid parameter name");
	}
	if (com->arg)
		num_str = search_key(envp, com->arg);
	if (num_str != -1)
		envp = delete_str(envp, len, com, num_str);
	return (envp);
}

char	**delete_str(char **envp, int size, t_command *com, int num_str)
{
	char **new;
	int i;
	int j;
	
	i = -1;
	j = -1;
	new = (char **)ft_calloc(size, sizeof(char *));
	while (++i < size)
		if (i != num_str)
			new[++j] = envp[i];
	return (new);
}