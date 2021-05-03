#include "../headers/minishell.h"

int	pars_get_env_value(char **line, char **env, int n, int i)
{
	char	*end;
	int		len;

	if (!*env)
		return (n);
	end = &(*line)[i];
	len = ft_strlen(*env);
	*env = ft_strjoin(*env, end);
	(*line)[n - 1] = '\0';
	*line = str_free(line, ft_strjoin(*line, *env));
	free(*env);
	return (n + len - 1);
}

int	pars_dollar_spec(t_all *all, char **line, int n)
{
	int		i;
	char	*tmp;
	char	*env;

	i = n;
	if ((*line)[n] == '$')
		env = ft_strdup("The cake is a lie!");
	else
	{
		if (all->proc->error > 255)
			all->proc->error /= 256;
		env = ft_itoa(all->proc->error);
	}
	tmp = env;
	n = pars_get_env_value(line, &env, n, ++i);
	free(tmp);
	return (n);
}

int	pars_dollar_get_var(t_all *all, char **line, int i, int n)
{
	char	*env;
	char	*tmp;
	int		len;

	while (ft_isalnum((*line)[i]) || (*line)[i] == '_')
		i++;
	tmp = ft_strndup(&((*line)[n]), i - n);
	if (!tmp)
		return (0);
	env = ft_getenv(all->env, tmp);
	if (!env)
	{
		len = ft_strlen(tmp) + 1;
		n--;
		while (len--)
			pars_shift_line(line, n);
	}
	else
		n = pars_get_env_value(line, &env, n, i);
	free(tmp);
	return (n);
}

int	pars_dollar(t_all *all, char **line, int i, int n)
{
	if (ft_isdigit((*line)[i++ + 1]))
	{
		pars_shift_line(line, n);
		pars_shift_line(line, n);
		return (n);
	}
	n++;
	if ((*line)[n] == '?' || (*line)[n] == '$')
		n = pars_dollar_spec(all, line, n);
	else if (!ft_isalnum((*line)[n]))
		return (n);
	else if (ft_isalnum((*line)[i]) || (*line)[i] == '_')
		n = pars_dollar_get_var(all, line, i, n);
	return (n);
}

int	pars_find_pair_quote(t_all *all, char **line, char c, int i)
{
	while ((*line)[i] != '\0' && (*line)[i] != c)
	{
		if ((*line)[i] == '\\')
		{
			if (c == '\"')
			{
				if (all->delescape == 1 && ((*line)[i + 1] == '\\'
					|| (*line)[i + 1] == '\"' || (*line)[i + 1] == '$'))
					pars_shift_line(line, i);
				else
					i++;
			}
		}
		else if (c == '\"' && all->delescape == 1 && (*line)[i] == '$')
		{
			i = pars_dollar(all, line, i, i);
			if (((*line)[i] == '\"' || (*line)[i] == '$') && all->delescape == 1)
				continue ;
		}
		i++;
	}
	return (i);
}

int	pars_find_quotes(t_all *all, char **line, char c, int i)
{
	if (all->delescape == 1 && (*line)[i] == c)
		i -= pars_shift_line(line, i);
	i++;
	i = pars_find_pair_quote(all, line, c, i);
	if (all->delescape == 0 && (*line)[i] == c)
		return (++i);
	else if ((*line)[i] == '\0')
		return (-1);
	else if (all->delescape == 1 && (*line)[i] == c)
		pars_shift_line(line, i);
	return (i);
}
