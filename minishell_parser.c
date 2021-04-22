// #include "minishell_parser.h"
#include "minishell.h"

void	pars_echo_n(t_com *com)
{
	int		a;
	int		i;
	char	**args;

	a = 1;
	com->n = 0;
	args = com->args;
	while (args[a] && args[a][0] == '-' && args[a][1] == 'n')
	{
		i = 1;
		while (args[a][i] == 'n')
			i++;
		if (args[a][i] == '\0' || args[a][i] == ' ')
		{
			com->n = 1;
			pars_shift_array(args, a);
			continue ;
		}
		else
			return ;
		a++;
	}
}

void	pars_get_env_dig(char **line, int i)
{
	pars_shift_line(line, --i);
	pars_shift_line(line, --i);
}

char	*pars_get_env_var(char **line, int i, int n)
{
	char	*env;
	char	*end;
	char	*new;

	i++;
	n++;
	while (ft_isalnum((*line)[i]) || (*line)[i] == '_')
		i++;
	new = ft_strndup(&((*line)[n]), i - n);
	if (!new)
		return (0);
	end = &(*line)[i];
	env = getenv(new);
	// write(1, "WHA_", 4);
	// write(1, env, ft_strlen(env));
	// write(1, "\n", 1);
	free(new);
	if (!env)
		return (*line);
	char *tmp;
	env = ft_strjoin(env, end);
	(*line)[n - 1] = '\0';
	new = ft_strjoin(*line, env);
	free(env);
	return (new);
}

int	pars_find_quotes(char **line, char c, int i, int delete_escape)
{
	if (delete_escape == 1 && (*line)[i] == c)
		i -= pars_shift_line(line, i);
	while ((*line)[++i] != '\0' && (*line)[i] != c)
	{
		if ((*line)[i] == '\\')
		{
			if (c == '\"')
			{
				if (delete_escape == 0)
					i++;
				else
				{
					if ((*line)[i + 1] == '\\' || (*line)[i + 1] == '\"' || (*line)[i + 1] == '$')
						pars_shift_line(line, i);
					else
						i++;
				}
			}
		}
		else if (c == '\"' && delete_escape == 1 && (*line)[i] == '$')// && i++)
		{
			*line = str_free(line, pars_get_env_var(line, i, i));
		}
	}
	if (delete_escape == 0 && (*line)[i] == c)
		return (++i);
	else if ((*line)[i] == '\0')
		return (-1);
	else if (delete_escape == 1 && (*line)[i] == c)
		pars_shift_line(line, i);
	return (i);
}

void		errorfunction()
{
	exit(666);
}

t_com	*pars_command(char *line, int start, int end)
{
	t_com	*com;

	com = malloc(sizeof(t_com));
	if (!com)
		errorfunction();
	com->type = 0;
	com->pipsem = '\0';
	com->line = ft_substr(line, start, 1 + end - start);
	if (!com->line)
		errorfunction();
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

int	pars_split_commands(t_all *all)
{
	int		i;
	int		st;
	char	*c;
	// char	cc;
	t_com	*com;
	t_list	*lst;

	i = 0;
	st = 0;
	c = 0;
	lst = 0;
	while (all->input[i] != '\0')
	{
		c = ft_strchr("\"'\\;|&#", all->input[i]);
		if (c)
		{
			// cc = *c;
			if (*c == '\"' || *c == '\'')
				i = pars_find_quotes(&all->input, *c, i, 0);
			else if (*c == ';' || *c == '|')
			{
				com = pars_command(all->input, st, i - 1);
				ft_lstadd_back(&lst, ft_lstnew(com));
				com->pipsem = *c;
				i++;
				st = i;
			}
			else if (*c == '\\')
				i = pars_check_escape(all->input, i);
			else if (*c == '#')
			{
				if (all->input[i - 1] == ' ')
				{
					com = pars_command(all->input, st, i - 1);
					ft_lstadd_back(&lst, ft_lstnew(com));
					break ;
				}
				else
					i++;
			}
			else if (*c == '&')
				i++;
		}
		else
			i++;
		if (i == -1)
		{
			write(1, "Syntax error!\n", 14);
			break ;
		}
		if (all->input[i] == '\0')
		{
			com = pars_command(all->input, st, i - 1);
			ft_lstadd_back(&lst, ft_lstnew(com));
		}
	}
	all->lst = lst;
	return (i);
}

void	pars_get_command(t_all *all)
{
	t_com	*com;
	int		i;
	int		n;
	char	str[10];
	char	*commands[7];
	t_list	*begin;

	begin = all->lst;
	commands[0] = "echo";
	commands[1] = "cd";
	commands[2] = "pwd";
	commands[3] = "export";
	commands[4] = "unset";
	commands[5] = "env";
	commands[6] = "exit";
	while (all->lst)
	{
		i = 0;
		com = all->lst->content;
		while (com->line[i] != ' ' && com->line[i] != '\0' && i < 9)
		{
			str[i] = ft_tolower(com->line[i]);
			str[++i] = '\0';
		}
		n = -1;
		while (n < 6)
		{
			if (ft_strcmp(str, &commands[++n][0]) == 0)
			{
				com->type = powf(2, n);
				break ;
			}
			else
				com->type = 128;
		}
		printf("getcom\t_%s_\t_%d_\t_%c_%d\n", com->line, com->type, com->pipsem, i);
		if (com->type == 1)
		{
			char	*space;
			space = ft_strdup(" ");
			pars_echo_n(com);
			int m = 1;
			while (com->args[m + 1])
			{
				com->args[1] = str_free(&com->args[1], ft_strjoin(com->args[1], space));
				com->args[1] = str_free(&com->args[1], ft_strjoin(com->args[1], com->args[m++ + 1]));
			}
			free(space);
		}
		all->lst = all->lst->next;
	}
	all->lst = begin;
	return ;
}

char	*pars_line_to_args(t_com *com, char **line, int *i)
{
	int		s;
	char	*new;
	char	*c;
	// char	cc;

	// i = 0;
	// new = *line;
	while ((*line)[*i] == ' ')
		*i += 1;
	// new = ft_strdup(*line);
	s = *i;
	while ((*line)[*i] != '\0' && (*line)[*i] != ' ')
	{
		c = ft_strchr("\"\\'", (*line)[*i]);
		// if (c)
			// cc = *c;
		if ((*line)[*i] == '\\')
			*i += pars_shift_line(line, *i);
		else if ((*line)[*i] == '\"')
			*i = pars_find_quotes(line, '\"', *i, 1);
		else if ((*line)[*i] == '\'')
			*i = pars_find_quotes(line, '\'', *i, 1);
		else if ((*line)[*i] == '>')
		{
			*i += 1;
		}
		else if ((*line)[*i] == '<')
		{
			*i += 1;
		}
		else if ((*line)[*i] == '$')
			*line = str_free(line, pars_get_env_var(line, *i, *i));
		else
			*i += 1;
	}
	// if (new != *line)
	// 	// free(*line);
	// free(new); /* WHY NOT FREED? */
	new = ft_strndup(&(*line)[s], *i);
	// free(*line);
	// *line += i;
	return (new);
}

void	pars_split_args(t_all *all)
{
	t_com	*com;
	int		i;
	char	*new;
	char	**tmp;
	char	**tmp2;
	t_list	*begin;
	char	*line;

	begin = all->lst;
	while (all->lst)
	{
		i = 0;
		com = all->lst->content;
		line = com->line;
		com->args = ft_calloc(1, sizeof(char **));
		while (com->line[i] != '\0')
		{
			// printf("ent: %s\n", com->line);
			tmp2 = com->args;
			new = pars_line_to_args(com, &com->line, &i);
			// if (line != com->line)
			// 	free(line);
			// line = com->line;
			tmp = (char **)ft_calloc(2, sizeof(char *));
			*tmp = new;
			com->args = ft_arrjoin(com->args, tmp);
			free(tmp);
			free(tmp2);
		}
		int m = -1;
		while (com->args[++m])
			printf("args %d\t_%s_\n", m, com->args[m]);
		// com->line = line;
		all->lst = all->lst->next;
	}
	all->lst = begin;
}
