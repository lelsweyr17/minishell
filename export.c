#include "minishell.h"

int	array_size(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
		i++;
	return (i);
}

void	export_output(t_command *com)
{
	int	i;
	int	j;

	i = -1;
	while (com->ex_port[++i])
	{
		write(1, "declare -x ", 11);
		j = 0;
		while (com->ex_port[i][j] != '=' && com->ex_port[i][j])
			write(1, &com->ex_port[i][j++], 1);
		if (com->ex_port[i][j] == '=')
		{
			write(1, "=\"", 2);
			j++;
			com->ex_port[i] += j;
			write(1, com->ex_port[i], ft_strlen(com->ex_port[i]));
			write(1, "\"", 2);
		}
		write(1, "\n", 1);
	}
}

void	array_swap_upper_key(t_command *com, int *num, int len)
{
	int		i;
	int		j;
	int		tmp;
	char	*tmpf;

	i = -1;
	while (++i < len)
	{
		j = i + 1;
		while (--j > 0 && num[j - 1] >= num[j])
		{
			tmp = num[j - 1];
			num[j - 1] = num[j];
			num[j] = tmp;
			tmpf = com->ex_port[j - 1];
			com->ex_port[j - 1] = com->ex_port[j];
			com->ex_port[j] = tmpf;
		}
	}
}

void	export_sort(t_command *com, char **envp)
{
	int	i;
	int	j;
	int	len;
	int	count;
	int	*num;

	len = array_size(envp);
	com->ex_port = (char **)ft_calloc(len, sizeof(char *));
	num = (int *)ft_calloc(len, sizeof(int));
	i = -1;
	while (++i < len)
		com->ex_port[i] = envp[i];
	i = -1;
	while (++i < len)
	{
		j = -1;
		count = 0;
		while (envp[++j])
			count += ft_strncmp(envp[i], envp[j], ft_strlen(envp[i]) + 1);
		num[i] = count + len;
	}
	array_swap_upper_key(com, num, len);
	export_output(com);
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
	new[i + 1] = NULL;
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
	if (com->unset && com->arg[i] == '=')
	{
		write(1, "unset: ", 7);
		write(1, com->arg, ft_strlen(com->arg));
		write(1, ": invalid parameter name\n", 25);
		exit(0);
	}
	i = -1;
	while (envp[++i])
	{
		if (!(ft_strncmp(envp[i], com->arg, len)) && envp[i][len] == '=')
		{
			envp[i] = com->arg;
			return (i);
		}
	}
	return (-1);
}

char	**exp_command(t_command *com, char **envp)
{
	int	i;
	int	len;

	i = -1;
	len = array_size(envp);
	if (com->arg && (export_equal_args(com, envp)) == -1)
	{
		envp = add_new_str(envp, len + 1, com);
		export_sort(com, envp);
	}
	else
		export_sort(com, envp);
	return (envp);
}
