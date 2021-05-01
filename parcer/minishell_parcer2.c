#include "../headers/minishell.h"

void	pars_redirects_type(t_re *re, char *line, int *i)
{
	re->type = 1;
	if (line[*i] == '<')
		re->type++;
	if (line[*i] == line[*i + 1] && (*i)++)
		re->type += 2;
	(*i)++;
	while (line[*i] == ' ')
		(*i)++;
}

void	pars_redirects(t_all *all, t_com *com, char **line, int *i)
{
	t_re	*re;
	t_list	*begin;
	int		s;

	re = ft_calloc(1, sizeof(t_re));
	if (!re)
		com->type = -1; /* SOME KIND OF STUPIDITY */
	ft_lstadd_back(&com->re, ft_lstnew(re));
	if (!com->re)
		com->type = -1; /* SOME KIND OF STUPIDITY */
	pars_redirects_type(re, *line, i);
	begin = com->re;
	while (com->re->next)
		com->re = com->re->next;
	s = *i;
	re = com->re->content;
	while ((*line)[*i] != '\0' && (*line)[*i] != ' ')
		pars_line(all, line, i);
	re->fn = ft_strndup(&(*line)[s], *i - s);
	com->re = begin;
}

char	*pars_get_next_arg(t_all *all, t_com *com, char **line, int *i)
{
	int		s;
	char	*new;

	s = *i;
	new = 0;
	while ((*line)[*i] != '\0' && (*line)[*i] != ' ' && (*line)[*i]
		!= '<' && (*line)[*i] != '>')
		pars_line(all, line, i);
	if (ft_strchr("<>", (*line)[*i]))
		pars_redirects(all, com, line, i);
	else
		new = ft_strndup(&(*line)[s], *i - s);
	return (new);
}

void	pars_split_args(t_all *all, t_com *com)
{
	int		i;
	char	*new;
	char	**tmp;
	char	**tmp2;

	i = 0;
	while (com->line[i] != '\0')
	{
		tmp2 = com->args;
		while (com->line[i] == ' ')
			i++;
		new = pars_get_next_arg(all, com, &com->line, &i);
		if (new)
		{
			tmp = (char **)ft_calloc(2, sizeof(char *));
			*tmp = new;
			com->args = ft_arrjoin(com->args, tmp);
			free(tmp2);
			free(tmp);
		}
		if (com->type == 0)
			pars_get_com(com);
	}
	if (com->type == 1)
		pars_echo(com);
}

/* PRINTF int m */
void	pars_get_args(t_all *all, t_proc *proc)
{
	t_com	*com;
	t_list	*begin;
	t_list	*send;

	begin = all->lst;
	send = all->lst;
	while (all->lst)
	{
		com = all->lst->content;
		com->args = (char **)ft_calloc(1, sizeof(char *));
		pars_split_args(all, com);
		int	m = -1;
		while (com->args[++m])
			printf("args %d\t_%s_\n", m, com->args[m]);
		if (com->pipsem == ';' || com->pipsem == 0)
		{
			all->env = processor(all->env, send, all->proc);
			send = all->lst;
			while (send != all->lst)
				send = send->next;
			send = send->next;
		}
		all->lst = all->lst->next;
	}
	all->lst = begin;
}
