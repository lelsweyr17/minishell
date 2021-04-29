#include "../headers/minishell.h"

t_com	*pars_get_command(t_all *all, int start, int end)
{
	t_com	*com;

	com = ft_calloc(1, sizeof(t_com));
	if (!com)
		all->par.i = -1;
	ft_bzero(com, sizeof(com));
	com->line = ft_substr(all->input, start, 1 + end - start);
	if (!com->line)
		all->par.i = -1;
	com->line = str_free(&com->line, ft_strtrim(com->line, " "));
	return (com);
}

int	pars_check_escape(char *input, int i)
{
	while (input[i] == '\\' && input[i + 1] != '\0')
		i += 2;
	if (input[i] == '\\' && input[i + 1] == '\0')
		return (-1);
	return (i);
}

int	pars_check_prev_com(t_all *all)
{
	t_list	*begin;
	t_com	*com;
	int		i;

	begin = 0;
	i = -1;
	if (all->lst)
	{
		begin = all->lst;
		while (all->lst->next)
			all->lst = all->lst->next;
		com = all->lst->content;
		i = com->place;
		all->lst = begin;
	}
	if (!isprevempty(all->input, i, all->par.i))
		return (0);
	if (begin)
		all->lst = begin;
	all->par.i = -1;
	return (1);
}

void	pars_check_command(t_all *all)
{
	t_com	*com;

	if (pars_check_prev_com(all))
		return ;
	com = pars_get_command(all, all->par.st, all->par.i - 1);
	ft_lstadd_back(&all->lst, ft_lstnew(com));
	com->pipsem = all->input[all->par.i];
	com->place = all->par.i;
	all->par.i++;
	all->par.st = all->par.i;
	if (isempty(&all->input[all->par.i], 1))
	{
		if (all->input[all->par.i - 1] == ';')
			all->par.i = -2;
		else if (all->input[all->par.i - 1] == '|')
			all->par.i = -1;
		return ;
	}
}

int	pars_check_redirects(t_all *all, char **line, char c, int i)
{
	// int	i;

	// i = all->par.i;
	if (isprevempty(*line, 0, i) == 2)
		return (-1);
	if ((*line)[++i] == c)
		i++;
	if (!ft_strchr("<>", (*line)[i]) && !isempty(&(*line)[i], 1))
		return (i);
	else
		return (-1);
}

void	pars_hash(t_all *all)
{
	t_com	*com;

	if (all->input[all->par.i - 1] == ' ')
	{
		com = pars_get_command(all, all->par.st, all->par.i - 1);
		ft_lstadd_back(&all->lst, ft_lstnew(com));
		all->par.i = -2;
	}
	else
		all->par.i++;
}

int	pars_split_commands(t_all *all)
{
	char	*c;
	t_com	*com;

	c = 0;
	while (all->input[all->par.i] != '\0' && all->par.i >= 0)
	{
		c = ft_strchr("\"'\\;|&#<>", all->input[all->par.i]);
		if (c)
		{
			if (*c == '\"' || *c == '\'')
				all->par.i = pars_find_quotes(&all->input, *c, all->par.i, 0);
			else if (*c == ';' || *c == '|')
				pars_check_command(all);
			else if (*c == '\\')
				all->par.i = pars_check_escape(all->input, all->par.i);
			else if (*c == '<' || *c == '>')
				all->par.i = pars_check_redirects(all, &all->input, *c, all->par.i);
			else if (*c == '#')
				pars_hash(all);
			else if (*c == '&')
				all->par.i++;
		}
		else
			all->par.i++;
		if (all->par.i == -1)
		{
			pars_free(all);
			write(1, "Syntax error!\n", 14);
		}
		if (all->par.i >= 0 && all->input[all->par.i] == '\0')
		{
			com = pars_get_command(all, all->par.st, all->par.i - 1);
			ft_lstadd_back(&all->lst, ft_lstnew(com));
		}
	}
	return (all->par.i);
}