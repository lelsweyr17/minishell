#include "minishell.h"

int	isnotempty(char *str, int hash)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (hash == 1 && ((str[i] == ' ' && str[i + 1] == '#') || str[0] == '#'))
			return (0);
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
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

	while (all->lst != 0)
	{
		com = all->lst->content;
		// ft_putendl_fd(com->line, 1);
		if (com->line)
			free(com->line);
		int m = -1;
		while (com->args && com->args[++m] != '\0')
			free(com->args[m]);
		free(com->args);
		free(com);
		tmp = all->lst;
		all->lst = all->lst->next;
		free(tmp);
	}
}
