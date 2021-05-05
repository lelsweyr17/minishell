#include "../headers/minishell.h"

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
		return (-10);
	else if (all->delescape == 1 && (*line)[i] == c)
		pars_shift_line(line, i);
	return (i);
}
