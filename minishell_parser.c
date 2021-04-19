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

int	pars_shift_line(char **line, int i)
{
	int	n;

	n = i;
	if ((*line)[i] == '\\')
		i += 2;
	while ((*line)[n] != '\0')
	{
		(*line)[n] = (*line)[n + 1];
		n++;
	}
	return (i - 1);
}

int	pars_find_quotes(char **line, char c, int i, int delete_escape)
{
	if (delete_escape == 1 && (*line)[i] == c)
		i = pars_shift_line(line, i);
	while ((*line)[++i] != '\n' && (*line)[i] != '\0' && (*line)[i] != c)
	{
		if ((*line)[i] == '\\')
		{
			if (c == '\"')
			{
				if (delete_escape == 0)
					i++;
				else if ((*line)[i + 1] == '\\')
					pars_shift_line(line, i);
			}
		}
	}
	if (delete_escape == 1 && (*line)[i] == c)
		pars_shift_line(line, i);
	if ((*line)[i] == c)
		return (++i);
	return (i); // error
}

void		errorfunction()
{
	exit(666);
}

// int			pars_env_param(char *line, char **envp)
// {
// }

// int			pars_pipe(char *line, int i)
// {
// }

// int			pars_semicolon(char *line, int i)
// {
// }

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
	// cc = 0;
	lst = 0;
	// write(1, line, ft_strlen(line));
	while (all->input[i] != '\0')// && *c != '#')
	{
		// ft_bzero(&all->par, 8);
		c = ft_strchr("\"'\\;|&#", all->input[i]);
		// write(1, all->input, ft_strlen(all->input));
		// printf("as");
		if (c)
		{
			// cc = *c;
			if (*c == '\"' || *c == '\'')
			{
				i = pars_find_quotes(&all->input, *c, i, 0);
				ft_putnbr(i);
				write(1, c, 1);
				// printf("%d\t%c\n", i, *c);
			}
			else if (*c == ';')
			{
				com = pars_command(all->input, st, i - 1);
				// write(1, "WTF", 3);
				ft_lstadd_back(&lst, ft_lstnew(com));
				// write(1, "WTF2", 4);
				com->pipsem = *c;
				i++;
				st = i;
			}
			/*TODO Ctrl+D sempip infinite loop*/
			else if (*c == '|')
			{
				com = pars_command(all->input, st, i - 1);
				ft_lstadd_back(&lst, ft_lstnew(com));
				com->pipsem = *c;
				i++;
				st = i;
			}
			else if (*c == '\\' && all->input[i + 1] != '\0')
				i += 2;
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
		if (all->input[i] == '\0')
		{
			// all->input[i] = '\0';
			com = pars_command(all->input, st, i - 1);
			// write(1, "WTF3", 4);
			ft_lstadd_back(&lst, ft_lstnew(com));
			// write(1, "WTF4", 4);
		}
		// if (all->par.sem || all->par.pip)
		// {
		// 	write(1, "sempip", 6);
		// 	st = i;
		// }
	}
	all->lst = lst;
	
	// if (lst)
	// { 
	// 	// write(1, "tt\n", 1);
	// 	while (lst)
	// 	{
	// 		write(1, "WTF5", 4);
	// 		com = lst->content;
	// 		write(1, "WTF6", 4);
	// 		ft_putendl_fd(com->line, 1);
	// 		lst = lst->next;
	// 	}
	// }
	// printf("EXT %d\n", i);
	return (i);
}

void	pars_get_command(t_all *all)
{
	// t_list	*begin;
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
		// printf("getcom\t_%s_\t_%d_\t_%c_\n", com->line, com->type, com->pipsem);
		while (com->line[i] != ' ' && com->line[i] != '\0' && i < 9)
		{
			// if (com->line[i] > 96 && com->line[i] < 123)
			str[i] = ft_tolower(com->line[i]);
			str[++i] = '\0';
		}
		// write(1, com->line, ft_strlen(com->line));
		// write(1, str, i);
		// ft_putnbr_fd(i, 1);
		n = -1;
		while (n < 6)
		{
			// write(1, commands[n], ft_strlen(commands[n]));
			// write(1, str, ft_strlen(str));
			if (ft_strcmp(str, &commands[++n][0]) == 0)
			{
				com->type = powf(2, n);
				printf("%s\t%d\n", str, i);
				// ft_putnbr_fd(i, 1);
				// write(1, "\n", 1);
				break ;
			}
			else
				com->type = 128;
		}
		printf("getcom\t_%s_\t_%d_\t_%c_%d\n", com->line, com->type, com->pipsem, i);
		if (com->type == 1)
		{
			pars_echo_n(com);
			printf("ECHO %d\t_%s_\n", 0, com->args[0]);
			int m = 1;
			while (com->args[m + 1])
			{
				printf("ECHO %d\t_%s_\n", 1, com->args[1]);
				com->args[1] = str_free(&com->args[1], ft_strjoin(com->args[1], com->args[m++ + 1]));
				// m++;
			}
			printf("ECHO FINAL %d\t_%s_\n", 1, com->args[1]);
		}
		all->lst = all->lst->next;
	}
		all->lst = begin;
	return ;
}

char	*pars_line_to_args(t_com *com, char **line)
{
	int		i;
	char	*new;
	// char	*c;
	// char	cc;

	i = 0;
	new = 0;
	while ((*line)[i] == ' ')
		*line += 1;
	while ((*line)[i] != '\0')// && (*line)[i] != ' ')
	{
		// c = ft_strchr("\"'", (*line)[i]);
		// if (c)
			// cc = *c;
		if ((*line)[i] == '\\')
			i = pars_shift_line(line, i);
		else if ((*line)[i] == '\"')
			i = pars_find_quotes(line, '\"', i, 1);
		else if ((*line)[i] == '\'')
			i = pars_find_quotes(line, '\'', i, 1);
		else if ((*line)[i] == '>')
		{
			i++;
		}
		else if ((*line)[i] == '<')
		{
			i++;
		}
		else
			i++;
		if ((*line)[i] == ' ')
		{
			i += 1;
			break ;
		}
	}
	new = ft_strndup(*line, i);
	// new = str_free(&new, ft_strtrim(new, &cc));
	*line += i;
	return (new);
}

void	pars_split_args(t_all *all)
{
	t_com	*com;
	int		i;
	char	*new;
	char	**tmp;
	t_list	*begin;
	char	*line;

	begin = all->lst;
	while (all->lst)
	{
		i = 0;
		com = all->lst->content;
		line = com->line;
		// while (com->line[i] != ' ' && com->line[i++] != '\0');
		com->args = ft_calloc(1, sizeof(char **));
		// com->args[0] = pars_line_to_args(com);//, &com->line);
		// com->line += i;
		while (*com->line != '\0') //&& com->type != 1)
		{
			printf("ent: %s\n", com->line);
			new = pars_line_to_args(com, &com->line);
			tmp = (char **)ft_calloc(2, sizeof(char *));
			*tmp = new;
			com->args = ft_arrjoin(com->args, tmp);
		}
		// while (com->args[0][i] != '\0')
		// 	com->args[0][i++] = '\0';
		int m = -1;
		while (com->args[++m])
			printf("args %d\t_%s_\n", m, com->args[m]);
		// com->line = 0;
		com->line = line;
		all->lst = all->lst->next;
	}
	all->lst = begin;
}
