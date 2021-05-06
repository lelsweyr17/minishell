#include "../headers/minishell.h"

int	pars_check_escape(char *input, int i)
{
	while (input[i] == '\\' && input[i + 1] != '\0')
		i += 2;
	if (input[i] == '\\' && input[i + 1] == '\0')
		return (-10);
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
	if (isprevempty(all->input, i, all->p->i))
		return (0);
	return (1);
}

void	pars_check_command(t_all *all)
{
	t_com	*com;

	if (pars_check_prev_com(all))
	{
		com = pars_get_command(all, all->p->st, all->p->i - 1);
		ft_lstadd_back(&all->lst, ft_lstnew(com));
		com->pipsem = all->input[all->p->i];
		com->place = all->p->i;
		all->p->i++;
		all->p->st = all->p->i;
	}
	else
	{
		if (all->input[all->p->i] == ';')
			all->p->i = -4;
		else if (all->input[all->p->i] == '|')
			all->p->i = -3;
	}
	if (all->p->i >= 0 && isempty(&all->input[all->p->i], 1))
	{
		if (all->input[all->p->i - 1] == ';')
			all->p->i = -2;
		else if (all->input[all->p->i - 1] == '|')
			all->p->i = -3;
	}
}

int	pars_check_redirects(t_all *all, char **line, char c, int i)
{
	if (isprevempty(*line, 0, i) != 2)
	{
		if ((*line)[++i] == c)
			i++;
		if (!ft_strchr("<>", (*line)[i]) && !isempty(&(*line)[i], 1))
			return (i);
	}
	if (isempty(&(*line)[i], 1))
		return (-5);
	else if ((*line)[i] == '>')
		return (-6);
	else
		return (-7);
}

void	pars_syntax_error(t_all *all)
{
	pars_free(all);
	write(1, "minishell: ", 11);
	if (all->p->i == -3)
		write(1, "syntax error near unexpected token `|'\n", 39);
	else if (all->p->i == -4)
		write(1, "syntax error near unexpected token `;'\n", 39);
	else if (all->p->i == -5)
		write(1, "syntax error near unexpected token `newline'\n", 45);
	else if (all->p->i == -6)
		write(1, "syntax error near unexpected token `>'\n", 39);
	else if (all->p->i == -7)
		write(1, "syntax error near unexpected token `<'\n", 39);
	else if (all->p->i == -8)
		write(1, "syntax error near unexpected token `('\n", 39);
	else if (all->p->i == -9)
		write(1, "syntax error near unexpected token `)'\n", 39);
	else if (all->p->i == -11)
		write(1, "syntax error near unexpected token `&&'\n", 40);
	else if (all->p->i == -12)
		write(1, "syntax error near unexpected token `||'\n", 40);
	else
		write(1, "syntax error near unexpected token\n", 36);
	init_error(258, &all->proc->error);
	g_err = 258;
}
