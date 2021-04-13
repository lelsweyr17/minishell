#include "header_commands.h"

char	*ft_getenv(char **envp, char *key)
{
	int	i;
	int len;

	i = 0;
	while (key[i] != '=' && key[i])
		i++;
	len = i;
	i = -1;
	while (envp[++i])
	{
		if (!(ft_strncmp(envp[i], key, len)) && envp[i][len] == '=')
			return (envp[i] + len + 1);
	}
	return (0);
}