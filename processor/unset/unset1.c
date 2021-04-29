#include "../../headers/processor.h"

int	search_key(char **envp, char *arg)
{
	int	i;
	int	len;

	i = 0;
	while (arg[i] && arg[i] != '=')
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

char	**unset_dollar(char *arg, t_proc *com, char **envp, int flag)
{
	int		i;
	int		len;
	int		num_str;
	char	*str;
	int		start;

	i = 0;
	num_str = 0;
	str = NULL;
	str = get_dollar_arg(arg, &start, flag);
	if (str && ft_strchr(str, '='))
		write_invalid_parameter_name(com);
	else if (str && ft_strlen(str))
		envp = unset_delete_condition(envp, str, com);
	if (str)
		free(str);
	return (envp);
}

char	**unset_command(t_proc *com, char **envp, char **args)
{
	int	i;
	int	len;
	int	num_str;

	i = 0;
	num_str = 0;
	len = array_size(envp);
	if (!com->arg)
		return (envp);
	while (com->arg && com->arg[i] && com->arg[i] != '=')
		i++;
	if (com->arg[0] == '$' && com->arg[1])
		envp = arg_dollar_conditions(envp, com);
	else if (com->arg && ft_strchr(com->arg, '='))
		write_invalid_parameter_name(com);
	else if (com->arg)
	{
		i = -1;
		while (args[++i])
			envp = unset_delete_condition(envp, args[i], com);
	}
	return (envp);
}

char	**delete_str(char **envp, int size, int num_str)
{
	char	**new;
	int		i;
	int		j;

	i = -1;
	j = -1;
	new = (char **)ft_calloc(size, sizeof(char *));
	while (++i < size)
		if (i != num_str)
			new[++j] = envp[i];
	free(envp[num_str]);
	free(envp);
	return (new);
}
