#include "header_commands.h"

void	null_flags(t_command *com)
{
	com->echo_n = 0;
	com->no_quotes = 0;
	com->arg = 0;
	com->double_quotes = 0;
	com->quote = 0;
	com->bin = 0;
	com->com = 0;
	com->bin_exec.path = 0;
	com->ex_port = 0;
	com->slesh = 0;
}

char	*arg_res(char **res, t_command *com)
{
	int		i;
	char	*tmp;
	char	*arg;

	i = 0;
	arg = (char *)ft_calloc(1, sizeof(char));
	arg[0] = 0;
	if (com->echo_n)
		i++;
	while (res[++i])
	{
		arg = ft_strjoin(arg, res[i]);
		if (res[i + 1])
			arg = ft_strjoin(arg, " ");
	}
	if (!ft_strlen(arg))
	{
		free(arg);
		arg = NULL;
	}
	return (arg);
}

char	**add_oldpwd(char **envp)
{
	int		i;
	int		size;
	char	**tmp;

	i = -1;
	size = array_size(envp);
	tmp = envp;
	envp = (char **)ft_calloc(size + 2, sizeof(char *));
	envp[size] = NULL;
	while (tmp[++i])
		envp[i] = ft_strdup(tmp[i]);
	if (search_key(envp, "OLDPWD") == -1)
		envp[i++] = ft_strdup("OLDPWD");
	envp[i] = NULL;
	return (envp);
}

void	com_export(t_command *com, char **envp)
{
	int	len;
	int	i;

	i = -1;
	len = array_size(envp);
	com->ex_port = (char **)ft_calloc(len + 1, sizeof(char *));
	com->ex_port[len] = NULL;
	while (++i < len)
		com->ex_port[i] = envp[i];
}

void	prepare_function(t_command *com, char **envp, char **res)
{
	null_flags(com);
	com_export(com, envp);
	if (res && res[1] && !(ft_strncmp(res[1], "-n", 3)))
		com->echo_n = 1;
	com->arg = arg_res(res, com);
}
