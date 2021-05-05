#include "../headers/minishell.h"

int	isempty(char *str, int hash)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (hash == 1 && ((str[i] == ' ' && str[i + 1] == '#')
				|| str[0] == '#'))
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

void	pars_free_re(t_list *lst)
{
	t_re	*re;
	t_list	*tmp;

	while (lst != 0)
	{
		re = lst->content;
		free(re->fn);
		free(re);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void	pars_free(t_all *all)
{
	int		i;
	t_com	*com;
	t_list	*tmp;

	while (all->lst != 0)
	{
		com = all->lst->content;
		if (com->line)
			free(com->line);
		i = -1;
		while (com->args && com->args[++i] != '\0')
			free(com->args[i]);
		free(com->args);
		if (com->re != 0)
			pars_free_re(com->re);
		free(com);
		tmp = all->lst;
		all->lst = all->lst->next;
		free(tmp);
	}
}
