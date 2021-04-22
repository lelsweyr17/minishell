// #include "minishell_parser.h"
#include "minishell.h"

void	pars_delete_last_spaces(char **line)
{
	int	len;

	len = ft_strlen(*line);
	while ((*line)[len] == ' ' && len > 0)
		(*line)[len--] = '\0';
}

void	pars_shift_array(char **args, int a)
{
	char	*tmp;

	tmp = args[a];
	while (args[a] != 0)
	{
		args[a] = args[a + 1];
		a++;
	}
	free(tmp);
}

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

char	*strtrim_free(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = str;
	while (tmp[i] != '\0')
	{
		if (tmp[i++] != ' ')
		{
			if (!(str = ft_strtrim(str, " ")))
				exit(0);
				// errormsg(17, "Function ft_strtrim() failed!");
			free(tmp);
			return (str);
		}
	}
	return (str);
}

int	pars_check_slash(char *line, int i)
{
	// if (i == 0)
	// 	errorfunc(line[i]); // если спецсимвол первый, вызывать ошибку syntax error...
	if (line[i - 1] == '\\')
		return (1);
	return (0);
}

int	pars_shift_line(char **line, int n)
{
	// int	n;

	// n = i;
	// if ((*line)[n] == '\\' && (*line)[n + 1] == '\0')
	// {
	// 	write(1, "ERROR!\n", 7);
	// 	return (0);
	// }
	while ((*line)[n])
	{
		(*line)[n] = (*line)[n + 1];
		n++;
	}
	return (1);
}

char	*pars_get_env_var(char **line, int i)
{
	char	*envar;
	int		n;
	char	*env;
	char	*end;
	char	*new;

	n = i;
	while (ft_isalnum((*line)[i]) || (*line)[i] == '_')
		i++;
	envar = ft_strndup(&((*line)[n]), i - n);
	if (!envar)
		return (0);
	end = &(*line)[i];
	env = getenv(envar);
	if (!env)
		return (*line);
	char *tmp;
	env = ft_strjoin(env, end);
	(*line)[n - 1] = '\0';
	new = ft_strjoin(*line, env);
	free(env);
	free(envar);
	return (new);
}

int	pars_find_quotes(char **line, char c, int i, int delete_escape)
{
	if (delete_escape == 1 && (*line)[i] == c)
		i -= pars_shift_line(line, i);
	while ((*line)[++i] != '\n' && (*line)[i] != '\0' && (*line)[i] != c)
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
		else if (c == '\"' && delete_escape == 1 && (*line)[i] == '$')
		{
			*line = pars_get_env_var(line, ++i);
		}
	}
	if (delete_escape == 0 && (*line)[i] == c)
		return (++i);
	else if ((*line)[i] == '\0')
		return (-1);
	else if ((*line)[i] == '\n')
		(*line)[i] = ';';
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
			pars_echo_n(com);
			int m = 1;
			while (com->args[m + 1])
			{
				com->args[1] = str_free(&com->args[1], ft_strjoin(com->args[1], ft_strdup(" ")));
				com->args[1] = str_free(&com->args[1], ft_strjoin(com->args[1], com->args[m++ + 1]));
			}
		}
		all->lst = all->lst->next;
	}
	all->lst = begin;
	return ;
}

char	*pars_line_to_args(t_com *com, char **line, int *i)
{
	// int		i;
	char	*new;
	char	*c;
	// char	cc;

	// i = 0;
	new = *line;
	while ((*line)[*i] == ' ')
		*i += 1;
	// new = ft_strdup(*line);
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
			*line = pars_get_env_var(line, ++*i);
		else
			*i += 1;
	}
	// if (new != *line)
	// 	// free(*line);
	// free(new);
	new = ft_strndup(*line, *i);
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
			if (line != com->line)
				free(line);
			line = com->line;
			tmp = (char **)ft_calloc(2, sizeof(char *));
			*tmp = new;
			com->args = ft_arrjoin(com->args, tmp);
			free(tmp);
			free(tmp2);
		}
		int m = -1;
		while (com->args[++m])
			printf("args %d\t_%s_\n", m, com->args[m]);
		com->line = line;
		all->lst = all->lst->next;
	}
	all->lst = begin;
}
