#include "minishell.h"

char	**add_new_str(char **envp, int size, t_command *com)
{
	char	**new;
	int		i;

	i = -1;
	new = (char **)ft_calloc(size + 1, sizeof(char *));
	while (++i < size - 1)
		new[i] = envp[i];
	new[i] = com->arg;
	new[i + 1] = 0;
	return (new);
}

int	export_equal_args(t_command *com, char **envp)
{
	int	i;
	int	len;

	i = 0;
	while (com->arg[i] && com->arg[i] != '=')
		i++;
	len = i;
	i = -1;
	while (envp[++i])
	{
		if (!(ft_strncmp(envp[i], com->arg, len)))
		{
			if ((com->arg[len] == '=' && envp[i][len] != '=') || \
				(com->arg[len] == '=' && envp[i][len] == '=') )
				envp[i] = com->arg;
			return (i);
		}
	}
	return (-1);
}