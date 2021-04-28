#include "minishell.h"

int	isempty(char *str, int hash)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (hash == 1 && ((str[i] == ' ' && str[i + 1] == '#') || str[0] == '#'))
			return (1);
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	isprevempty(char *str, int begin, int last)
{
	while (begin < --last)
	{
		if (str[last] == '<' || str[last] == '>')
			return (2);
		if (str[last] != ' ')
			return (0);
	}
	return (1);
}

char	*str_free(char **line, char *tmp)
{
	if (*line != tmp)
		free(*line);
	return (tmp);
}

void	pars_free(t_all *all)
{
	t_com	*com;
	t_list	*tmp;
	t_re 	*re;

	while (all->lst != 0)
	{
		com = all->lst->content;
		// ft_putendl_fd(com->line, 1);
		if (com->line)
			free(com->line);
		int m = -1;
		while (com->args && com->args[++m] != '\0')
			free(com->args[m]);
		while (com->re != 0)
		{
			re = com->re->content;
			free(re->fn);
			tmp = com->re;
			com->re = com->re->next;
			free(tmp);
		}
		free(com->args);
		free(com);
		tmp = all->lst;
		all->lst = all->lst->next;
		free(tmp);
	}
}
