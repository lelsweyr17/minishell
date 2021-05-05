#include "../headers/minishell.h"

t_com	*pars_get_command(t_all *all, int start, int end)
{
	t_com	*com;

	com = ft_calloc(1, sizeof(t_com));
	if (!com)
		all->p->i = -1;
	ft_bzero(com, sizeof(com));
	com->line = ft_substr(all->input, start, 1 + end - start);
	if (!com->line)
		all->p->i = -1;
	com->line = str_free(&com->line, ft_strtrim(com->line, " "));
	if (!com->line)
		all->p->i = -1;
	return (com);
}

void	pars_hash(t_all *all)
{
	t_com	*com;

	if (all->input[all->p->i - 1] == ' ')
	{
		com = pars_get_command(all, all->p->st, all->p->i - 1);
		ft_lstadd_back(&all->lst, ft_lstnew(com));
		all->p->i = -2;
	}
	else
		all->p->i++;
}

void	pars_spec_sym(t_all *all, char *c)
{
	if (*c == '\"' || *c == '\'')
		all->p->i = pars_find_quotes(all, &all->input, *c, all->p->i);
	else if (*c == ';' || *c == '|')
		pars_check_command(all);
	else if (*c == '\\')
		all->p->i = pars_check_escape(all->input, all->p->i);
	else if (*c == '<' || *c == '>')
		all->p->i = pars_check_redirects(all, &all->input, *c, all->p->i);
	else if (*c == '#')
		pars_hash(all);
	else if (*c == '(')
		all->p->i++;
	else if (*c == ')')
		all->p->i++;
	else if (*c == '&')
		all->p->i++;
}
		
int	pars_split_commands(t_all *all)
{
	char	*c;
	t_com	*com;

	c = 0;
	while (all->input[all->p->i] != '\0' && all->p->i >= 0)
	{
		c = ft_strchr("\"'\\;|&#<>", all->input[all->p->i]);
		if (c)
			pars_spec_sym(all, c);
		else
			all->p->i++;
		if (all->p->i <= -3)
			pars_syntax_error(all);
		if (all->p->i >= 0 && all->input[all->p->i] == '\0')
		{
			com = pars_get_command(all, all->p->st, all->p->i - 1);
			ft_lstadd_back(&all->lst, ft_lstnew(com));
		}
	}
	return (all->p->i);
}
