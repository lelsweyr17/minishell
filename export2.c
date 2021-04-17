#include "header_commands.h"

int	ft_is_str(char *str)
{
	int i;

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

char	**exp_command(t_command *com, char **envp, char **args)
{
	int k;
	int	i;
	int	len;
	int arg_len;

	i = 0;
	if (com->arg)
	{
		while (com->arg[i] && com->arg[i] != '=')
			i++;
		arg_len = i;
		i = -1;
		while (args[++i])
		{
			com->arg = args[i];
			if (!ft_is_str(com->arg))
			{
				com->arg = change_arg_for_unset(com->arg);
				write_error("export", com->arg, "not a valid identifier");
				init_error(1, &com->error);
			}
			else
			{
				k = search_key(envp, com->arg);
				len = array_size(envp);
				if (k == -1)
					envp = add_new_str(envp, len + 1, com);
				else if (k >= 0 && com->arg[arg_len] == '=')
					envp[k] = com->arg;
			}
		}
	}
	else
		export_sort(com, envp);
	return (envp);
}