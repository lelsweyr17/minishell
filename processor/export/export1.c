#include "../../headers/processor.h"

void	export_output(t_proc *com)
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

void	array_swap_upper_key(t_proc *com, int *num, int len)
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

void	export_sort(t_proc *com, char **envp)
{
	int	i;
	int	j;
	int	len;
	int	count;

	i = -1;
	len = array_size(envp);
	com->tmp = (int *)ft_calloc(len + 1, sizeof(int));
	while (++i < len)
	{
		j = -1;
		count = 0;
		while (envp[++j])
		{
			com->tmpp = ft_strncmp(envp[i], envp[j], ft_strlen(envp[i]) + 1);
			if (com->tmpp > 0)
				count++;
			else if (com->tmpp < 0)
				count--;
		}
		com->tmp[i] = count;
	}
	array_swap_upper_key(com, com->tmp, len);
	export_output(com);
	free(com->tmp);
}
