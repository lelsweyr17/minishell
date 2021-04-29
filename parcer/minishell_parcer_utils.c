#include "../headers/minishell.h"

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
				exit(0);
				// errormsg(17, "Function ft_strtrim() failed!");
			free(tmp);
			return (str);
		}
	}
	return (str);
}

/* UNUSED FUNCTIONS */
void	pars_delete_last_spaces(char **line)
{
	int	len;

	len = ft_strlen(*line);
	while ((*line)[len] == ' ' && len > 0)
		(*line)[len--] = '\0';
}

int	pars_check_slash(char *line, int i)
{
	/* // if (i == 0) **
	** 	errorfunc(line[i]); // если спецсимвол первый, вызывать ошибку syntax error... */
	if (line[i - 1] == '\\')
		return (1);
	return (0);
}
