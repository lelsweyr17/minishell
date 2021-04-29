#include "../../headers/processor.h"

void	env_command(char **envp)
{
	int	i;

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
