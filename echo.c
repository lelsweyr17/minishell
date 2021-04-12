#include "minishell.h"

int	array_size(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
		i++;
	return (i);
}

int	echo_dollar(t_command *com, int i, char **envp)
{
	int		j;
	int		len;
	char	*s;

	j = -1;
	len = 0;
	if (com->arg[++i] == '?')
	{
		ft_putnbr_fd(com->error, 1);
		init_error(0, &com->error);
	}
	while (com->arg[i + len] != ' ' && com->arg[i + len] && \
		com->arg[i + len] != '$' && com->arg[i + len] != '\n')
		len++;
	if (len == 0)
	{
		write(1, "$", 1);
		init_error(0, &com->error);
	}
	s = ft_substr(com->arg, i, len + 1);
	s[len++] = '=';
	while (envp[++j])
		if (!ft_strncmp(s, envp[j], len))
			break ;
	if (envp[j])
	{
		write(1, envp[j] + len, ft_strlen(envp[j]) - len);
		init_error(0, &com->error);
	}
	free(s);
	return (i += len - 1);
}

void	echo_command(t_command *com, char **envp)
{
	int		i;
	int		j;

	i = 0;
	if (com->quote)
		write(1, com->arg, ft_strlen(com->arg));
	else
	{
		while (com->arg && com->arg[i])
		{
			while (com->arg[i] && com->arg[i] != '$')
				write(1, &com->arg[i++], 1);
			if (com->arg[i] == '$')
				i = echo_dollar(com, i, envp);
		}
	}
    if (!com->echo_n)
	    write(1, "\n", 1);
}
