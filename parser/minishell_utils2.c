#include "../headers/minishell.h"

void	sighandler(int signr)
{
	if (signr == 2)
	{
		ft_putendl_fd("", 2);
		g_err = 130;
	}
	else
	{
		ft_putendl_fd("Quit: 3", 2);
		g_err = 131;
	}
}

int	get_read(t_all *all, char *buf, int res)
{
	ft_memset(buf, 0, res);
	if (all->nl == 0)
	{
		all->res = read(0, buf, 999);
		if (all->res < 0)
			exit (0);
		buf[all->res] = '\0';
	}
	return (all->res);
}

void	pars_shift_array(char **args, int a)
{
	char	*tmp;

	tmp = args[a];
	while (args[a] != 0)
	{
		args[a] = args[a + 1];
		a++;
	}
	free(tmp);
}

int	pars_shift_line(char **line, int n)
{
	while ((*line)[n])
	{
		(*line)[n] = (*line)[n + 1];
		n++;
	}
	return (1);
}

char	*strtrim_free(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = str;
	while (tmp[i] != '\0')
	{
		if (tmp[i++] != ' ')
		{
			str = ft_strtrim(str, " ");
			if (!str)
				return (0);
			free(tmp);
			return (str);
		}
	}
	return (str);
}
