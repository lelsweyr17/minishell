#include "../../headers/processor.h"

char	*new_arg_for_export(char *str, char *arg, int *start)
{
	char	*new;

	if (str)
		new = ft_strjoin(str, arg + *start);
	else
		new = ft_strdup(arg + *start);
	return (new);
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
	i = 0;
	while (tmp && tmp[i] != '=' && tmp[i])
		i++;
	if (!flag)
		*start = i;
	tmp[i] = 0;
	str_env = getenv(tmp);
	if (str_env)
		str = ft_strdup(str_env);
	new = new_arg_for_export(str, arg, start);
	if (str)
		free(str);
	free(tmp);
	return (new);
}

char	**export_dollar(char *arg, t_proc *com, char **envp, int flag)
{
	char	*str;
	int		start;

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
			envp = export_add_new_object(envp, str);
	}
	else
		export_sort(com, envp);
	if (str)
		free(str);
	return (envp);
}
