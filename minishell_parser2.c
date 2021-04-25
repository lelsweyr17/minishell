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

char	*pars_get_next_arg(t_com *com, char **line, int *i, int s)
{
	char	*new;

	while ((*line)[*i] != '\0' && (*line)[*i] != ' ')
	{
		if ((*line)[*i] == '\\')
			*i += pars_shift_line(line, *i);
		else if ((*line)[*i] == '\"')
			*i = pars_find_quotes(line, '\"', *i, 1);
		else if ((*line)[*i] == '\'')
			*i = pars_find_quotes(line, '\'', *i, 1);
		else if ((*line)[*i] == '>')
			*i += 1; // = pars_redirects(com, line, *i);
		else if ((*line)[*i] == '<')
		{
			*i += 1;
		}
		else if ((*line)[*i] == '$')
			*i = pars_dollar(line, *i, *i);
		else
			*i += 1;
	}
	new = ft_strndup(&(*line)[s], *i - s);
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
		com->args = ft_arrjoin(com->args, tmp);
		if (com->type == 0)
			pars_get_com(com);
		free(tmp);
		free(tmp2);
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
		com->args = ft_calloc(1, sizeof(char **));
		pars_split_args(com);
		int	m = -1;
		while (com->args[++m])
			printf("args %d\t_%s_\n", m, com->args[m]);
		all->lst = all->lst->next;
	}
	all->lst = begin;
}
