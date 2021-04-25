#include "minishell.h"

t_com	*pars_command(char *line, int start, int end)
{
	t_com	*com;

	com = malloc(sizeof(t_com));
	if (!com)
		write(1, "ERRRRRRRRRRORRRRRRRRRRR\n", 24);
	com->type = 0;
	ft_bzero(&com->pipsem, 37);
	com->line = ft_substr(line, start, 1 + end - start);
	if (!com->line)
		write(1, "ERRRRRRRRRRORRRRRRRRRRR\n", 24);
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
	}
	if (!isprevempty(&all->input[i], i, all->par.i))
	// while (++i < all->par.i)
	// 	if (all->input[i] != ' ')
			return (0);
	if (begin)
		all->lst = begin;
	all->par.i = -1;
	pars_free(all);
	return (1);
}

void	pars_check_command(t_all *all, t_com *com)
{
	if (pars_check_prev_com(all))
		return ;
	com = pars_command(all->input, all->par.st, all->par.i - 1);
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
		{
			all->par.i = -1;
			pars_free(all);
		}
		return ;
	}
}

int	pars_check_redirects(t_all *all, char **line, char c, int i)
{
	// int	i;

	// i = all->par.i;
	if ((*line)[++i] == c)
		i++;
	if (!ft_strchr("<>", (*line)[i]) && !isempty(&(*line)[i], 1))
		return (i);
	else
	{
		pars_free(all);
		return (-1);
	}
}

int	pars_split_commands(t_all *all)
{
	char	*c;
	t_com	*com;

	c = 0;
	while (all->input[all->par.i] != '\0')
	{
		c = ft_strchr("\"'\\;|&#<>", all->input[all->par.i]);
		if (c)
		{
			if (*c == '\"' || *c == '\'')
				all->par.i = pars_find_quotes(&all->input, *c, all->par.i, 0);
			else if (*c == ';' || *c == '|')
				pars_check_command(all, com);
			else if (*c == '\\')
				all->par.i = pars_check_escape(all->input, all->par.i);
			else if (*c == '<' || *c == '>')
				all->par.i = pars_check_redirects(all, &all->input, *c, all->par.i);
			else if (*c == '#')
			{
				if (all->input[all->par.i - 1] == ' ')
				{
					com = pars_command(all->input, all->par.st, all->par.i - 1);
					ft_lstadd_back(&all->lst, ft_lstnew(com));
					break ;
				}
				else
					all->par.i++;
			}
			else if (*c == '&')
				all->par.i++;
		}
		else
			all->par.i++;
		if (all->par.i == -1)
		{
			write(1, "Syntax error!\n", 14);
			break ;
		}
		if (all->par.i == -2)
			break ;
		if (all->input[all->par.i] == '\0')
		{
			com = pars_command(all->input, all->par.st, all->par.i - 1);
			ft_lstadd_back(&all->lst, ft_lstnew(com));
		}
	}
	return (all->par.i);
}
