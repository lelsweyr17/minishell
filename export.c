#include "minishell.h"

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
			write(1, "\"", 1);
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

	i = -1;
	len = array_size(envp);
	num = (int *)ft_calloc(len + 1, sizeof(int));
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
	free(num);
}

char	**exp_command(t_command *com, char **envp)
{
	int	i;
	int	len;

	i = -1;
	len = array_size(envp);
	if (com->arg && (export_equal_args(com, envp)) == -1)
		envp = add_new_str(envp, len + 1, com);
	if (!com->arg)
		export_sort(com, envp);
	return (envp);
}
