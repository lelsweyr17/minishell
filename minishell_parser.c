// #include "minishell_parser.h"
#include "minishell.h"

void	pars_echo_del_n_str(t_com *com)
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

int	pars_get_env_var(char **line, int i, int n)
{
	char	*env;
	char	*end;
	char	*new;

	if (ft_isdigit((*line)[i++ + 1]))
	{
		pars_shift_line(line, n);
		pars_shift_line(line, n);
		return (n);
	}
	n++;
	if (!ft_isalnum((*line)[i]))
		return (i);
	while (ft_isalnum((*line)[i]) || (*line)[i] == '_')
		i++;
	new = ft_strndup(&((*line)[n]), i - n);
	if (!new)
		return (0);
	end = &(*line)[i];
	env = getenv(new);
	free(new);
	if (!env)
		return (n);
	char *tmp;
	env = ft_strjoin(env, end);
	(*line)[n - 1] = '\0';
	*line = str_free(line, ft_strjoin(*line, env));
	free(env);
	return (n);
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
					if ((*line)[i + 1] == '\\' || (*line)[i + 1] == '\"' || (*line)[i + 1] == '$')
						pars_shift_line(line, i);
					else
						i++;
			}
		}
		else if (c == '\"' && delete_escape == 1 && (*line)[i] == '$')
		{
			i = pars_get_env_var(line, i, i);
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
	ft_bzero(&com->pipsem, 37);
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

int	isprevnotempty(char *str, int begin, int last)
{
	while (begin < last && str[begin] != '\0')
	{
		if (str[begin] != ' ')
			return (1);
		begin++;
	}
	return (0);
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
	while (++i < all->par.i)
		if (all->input[i] != ' ')
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
	if (!isnotempty(&all->input[all->par.i], 1))
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



int	pars_split_commands(t_all *all)
{
	char	*c;
	t_com	*com;

	c = 0;
	while (all->input[all->par.i] != '\0')
	{
		c = ft_strchr("\"'\\;|&#", all->input[all->par.i]);
		if (c)
		{
			// cc = *c;
			if (*c == '\"' || *c == '\'')
				all->par.i = pars_find_quotes(&all->input, *c, all->par.i, 0);
			else if (*c == ';' || *c == '|')
				pars_check_command(all, com);
			else if (*c == '\\')
				all->par.i = pars_check_escape(all->input, all->par.i);
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
	// all->lst = lst;
	return (all->par.i);
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
			pars_echo_del_n_str(com);
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
	// char	*c;

	while ((*line)[*i] == ' ')
		*i += 1;
	s = *i;
	while ((*line)[*i] != '\0' && (*line)[*i] != ' ')
	{
		// c = ft_strchr("\"\\'", (*line)[*i]);
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
			*i = pars_get_env_var(line, *i, *i);
		else
			*i += 1;
	}
	new = ft_strndup(&(*line)[s], *i - s);
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
