#include "minishell.h"

void	pars_echo_del_n_str(t_com *com)
{
	int		a;
	int		i;
	char	**args;

	a = 1;
	com->n = 0;
	args = com->args;
	while (args[a] && args[a][0] == '-' && args[a][1] == 'n')
	{
		i = 1;
		while (args[a][i] == 'n')
			i++;
		if (args[a][i] == '\0' || args[a][i] == ' ')
		{
			com->n = 1;
			pars_shift_array(args, a);
			continue ;
		}
		else
			return ;
		a++;
	}
}

void	pars_echo_n(t_com *com)
{
	char	*space;
	char	**args;
	int		m;

	m = 1;
	args = com->args;
	space = ft_strdup(" ");
	pars_echo_del_n_str(com);
	while (args[m + 1])
	{
		args[1] = str_free(&args[1], ft_strjoin(args[1], space));
		args[1] = str_free(&args[1], ft_strjoin(args[1], args[m++ + 1]));
	}
	free(space);
}

int	pars_get_env_value(char **line, char **env, int n, int i)
{
	char	*end;

	if (!*env)
		return (n);
	end = &(*line)[i];
	*env = ft_strjoin(*env, end);
	(*line)[n - 1] = '\0';
	*line = str_free(line, ft_strjoin(*line, *env));
	free(*env);
	return (n);
}

int	pars_dollar(char **line, int i, int n)
{
	char	*env;
	char	*new;

	if (ft_isdigit((*line)[i++ + 1]))
	{
		pars_shift_line(line, n);
		pars_shift_line(line, n);
		return (n);
	}
	n++;
	if (!ft_isalnum((*line)[n]))
		return (n);
	while (ft_isalnum((*line)[i]) || (*line)[i] == '_')
		i++;
	new = ft_strndup(&((*line)[n]), i - n);
	if (!new)
		return (0);
	env = getenv(new);
	free(new);
	pars_get_env_value(line, &env, n, i);
	return (n);
}

int	pars_find_quotes(char **line, char c, int i, int delescape)
{
	if (delescape == 1 && (*line)[i] == c)
		i -= pars_shift_line(line, i);
	while ((*line)[++i] != '\0' && (*line)[i] != c)
	{
		if ((*line)[i] == '\\')
		{
			if (c == '\"')
			{
				if (delescape == 1 && ((*line)[i + 1] == '\\'
					|| (*line)[i + 1] == '\"' || (*line)[i + 1] == '$'))
					pars_shift_line(line, i);
				else
					i++;
			}
		}
		else if (c == '\"' && delescape == 1 && (*line)[i] == '$')
			i = pars_dollar(line, i, i);
	}
	if (delescape == 0 && (*line)[i] == c)
		return (++i);
	else if ((*line)[i] == '\0')
		return (-1);
	else if (delescape == 1 && (*line)[i] == c)
		pars_shift_line(line, i);
	return (i);
}
