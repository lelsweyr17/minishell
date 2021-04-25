#include "minishell.h"

/* PRINTF */
void	pars_cmp_com(t_com *com, char **commands)
{
	int		i;
	int		n;
	char	str[10];

	i = -1;
	while (com->args[0][++i] != '\0' && i < 9)
		str[i] = ft_tolower(com->args[0][i]);
	str[i] = '\0';
	n = -1;
	while (n < 6 && com->type == 0)
		if (ft_strncmp(str, commands[++n], i) == 0)
			com->type = 1 << n;
	if (com->type == 0)
		com->type = 1 << ++n;
	printf("getcom\t_%s_\t_%d_\t_%c_%d\n", com->line, com->type, com->pipsem, i);
}

int	pars_get_com(t_com *com)
{
	char	*commands[7];

	commands[0] = "echo";
	commands[1] = "cd";
	commands[2] = "pwd";
	commands[3] = "export";
	commands[4] = "unset";
	commands[5] = "env";
	commands[6] = "exit";
	pars_cmp_com(com, commands);
	return (com->type);
}

void	pars_redirects(t_com *com, char *line, int *i)
{
	t_re	*re;

	re = ft_calloc(1, sizeof(t_re));
	if (!re)
		com->type = -1; /* SOME KIND OF STUPIDITY */
	ft_lstadd_back(&com->re, ft_lstnew(re));
	if (!com->re)
		com->type = -1; /* SOME KIND OF STUPIDITY */
	re->type = 1;
	if (line[*i] == '<')
		re->type++;
	if (line[*i] == line[*i + 1] && *i++)
		re->type += 2;
	while (line[*i] == ' ')
		*i += 1;
}

void	pars_line(char **line, int *i)
{
	if ((*line)[*i] == '\\')
		*i += pars_shift_line(line, *i);
	else if ((*line)[*i] == '\"')
		*i = pars_find_quotes(line, '\"', *i, 1);
	else if ((*line)[*i] == '\'')
		*i = pars_find_quotes(line, '\'', *i, 1);
	else if ((*line)[*i] == '$')
		*i = pars_dollar(line, *i, *i);
	else
		*i += 1;
}

char	*pars_get_next_arg(t_com *com, char **line, int *i, int s)
{
	char	*new;
	t_re	*re;

	while ((*line)[*i] != '\0' && (*line)[*i] != ' ' && (*line)[*i] != '<' && (*line)[*i] != '>')
		pars_line(line, i);
	new = ft_strndup(&(*line)[s], *i - s);
	if (*new == '\0' && ft_strchr("<>", (*line)[*i]))
	{
		// free(new);
		pars_redirects(com, *line, i);
		s = *i;
		re = com->re->content;
		while ((*line)[*i] != '\0' && (*line)[*i] != ' ')
			pars_line(line, i);
		re->fn = ft_strndup(&(*line)[s], *i - s);
		write(1, re->fn, ft_strlen(re->fn));
	}
	return (new);
}

void	pars_split_args(t_com *com)
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
		new = pars_get_next_arg(com, &com->line, &i, i);
		tmp = (char **)ft_calloc(2, sizeof(char *));
		*tmp = new;
		if (*new != '\0')
		{
			com->args = ft_arrjoin(com->args, tmp);
			free(tmp2);
		}
		free(tmp);
		if (com->type == 0)
			pars_get_com(com);
	}
	if (com->type == 1)
		pars_echo_n(com);
}

/* PRINTF int m */
void	pars_get_args(t_all *all)
{
	t_com	*com;
	t_list	*begin;
	char	*line;

	begin = all->lst;
	while (all->lst)
	{
		com = all->lst->content;
		line = com->line;
		com->args = (char **)ft_calloc(1, sizeof(char *));
		pars_split_args(com);
		int	m = -1;
		while (com->args[++m])
			printf("args %d\t_%s_\n", m, com->args[m]);
		all->lst = all->lst->next;
	}
	all->lst = begin;
}
