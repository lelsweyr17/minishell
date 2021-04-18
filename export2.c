#include "header_commands.h"

int	ft_is_str(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}

char	**add_new_str(char **envp, int size, t_command *com, char *arg)
{
	char	**new;
	int		i;

	i = -1;
	new = (char **)ft_calloc(size + 1, sizeof(char *));
	while (++i < size - 1)
		new[i] = envp[i];
	new[i] = arg;
	new[i + 1] = 0;
	return (new);
}

char	**export_add_new_object(char **envp, t_command *com, char *str)
{
	int	i;
	int	k;
	int	arg_len;
	int	len;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	arg_len = i;
	k = search_key(envp, str);
	len = array_size(envp);
	if (k == -1)
		envp = add_new_str(envp, len + 1, com, str);
	else if (k >= 0 && str[arg_len] == '=')
		envp[k] = str;
	return (envp);
}

char	*get_dollar_arg(char *arg, int *start, int flag)
{
	int		i;
	char	*new;
	char	*str;
	char	*tmp;
	char	*str_env;

	tmp = ft_strdup(arg);
	str = NULL;
	new = NULL;
	*start = 0;
	while (tmp && tmp[i] != '=' && tmp[i])
		i++;
	if (!flag)
		*start = i;
	tmp[i] = 0;
	str_env = getenv(tmp);
	if (str_env)
		str = ft_strdup(str_env);
	if (str)
		new = ft_strjoin(str, arg + *start);
	else
		new = ft_strdup(arg + *start);
	if (str)
		free(str);
	free(tmp);
	return (new);
}

char	**export_dollar(char *arg, t_command *com, char **envp, int flag)
{
	int		i;
	char	*str;
	int		start;

	i = 0;
	str = NULL;
	str = get_dollar_arg(arg, &start, flag);
	if (str && ft_strlen(str))
	{
		if (!ft_is_str(str))
		{
			str = change_arg_for_unset(str);
			write_error("export", str, "not a valid identifier");
			init_error(1, &com->error);
		}
		else
			envp = export_add_new_object(envp, com, str);
	}
	else
		export_sort(com, envp);
	return (envp);
}

char	**exp_command(t_command *com, char **envp, char **args)
{
	int	i;

	i = 0;
	if (com->arg)
	{
		i = -1;
		while (args[++i])
		{
			com->arg = args[i];
			if (com->arg[0] == '$' && com->arg[1])
			{
				if (ft_isdigit(com->arg[1]))
					envp = export_dollar(com->arg + 2, com, envp, 1);
				else
					envp = export_dollar(com->arg + 1, com, envp, 0);
			}
			else if (!ft_is_str(com->arg))
			{
				com->arg = change_arg_for_unset(com->arg);
				write_error("export", com->arg, "not a valid identifier");
				init_error(1, &com->error);
			}
			else
				envp = export_add_new_object(envp, com, com->arg);
		}
	}
	else
		export_sort(com, envp);
	return (envp);
}
