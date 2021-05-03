#include "libft.h"

char	**arrdup(char **envp)
{
	int		i;
	char	**env;

	i = -1;
	env = (char **)ft_calloc(array_size(envp) + 1, sizeof(char *));
	while (envp[++i])
		env[i] = ft_strdup(envp[i]);
	env[i] = NULL;
	return (env);
}
