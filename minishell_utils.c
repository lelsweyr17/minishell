// #include "minishell_parser.h"
#include "minishell.h"

char			*strtrim_free(char *str)
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

int			pars_check_slash(char *line, int i)
{
	// if (i == 0)
	// 	errorfunc(line[i]); // если спецсимвол первый, вызывать ошибку syntax error...
	if (line[i - 1] == '\\')
		return (1);
	return (0);
}

int			pars_find_quotes(char *line, char *c, int i)
{
	while (line[++i] != '\n' && line[i] != *c);// && line[i] != '\\');
	// if (line[i] == '\\')
	// {
	// 	if (line[i] == '\\' && line[i + 1] == '\\')
	// 		i += 2;
	// }
	if (line[i] == *c)
	{
		*c = 0;
		// ft_putnbr_fd(i, 1);
		return (++i);
	}
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

t_com		*command(char *line, int start, int end)
{
	t_com	*com;

	com = malloc(sizeof(t_com));
	if (!com)
		errorfunction();
	// write(1, "aaa\n", 4);
	com->type = 0;
	com->pipsem = '\0';
	com->line = ft_substr(line, start, 1 + end - start);
	if (!com->line)
		errorfunction();
	com->line = strtrim_free(com->line);
	// write(1, "bbb\n", 4);
	return (com);
}

int			pars_split_commands(t_all *all, char *line)
{
	int		i;
	int		st;
	char	*c;
	char	cc;
	t_com	*com;
	t_list	*lst;

	i = 0;
	st = 0;
	cc = 0;
	lst = 0;
	// write(1, line, ft_strlen(line));
	while (all->input[i] != '\n')
	{
		// ft_bzero(&all->par, 8);
		c = ft_strchr("\"';|&", all->input[i]);
		// write(1, all->input, ft_strlen(all->input));
    	// printf("as");
		if (c)
		{
			cc = *c;
			if (cc == '\"' || cc == '\'')
			{
				i = pars_find_quotes(all->input, &cc, i);
				printf("%d\t%c\n", i, cc);
			}
			else if (cc == ';')
			{
				com = command(all->input, st, i - 1);
				// write(1, "WTF", 3);
				ft_lstadd_back(&lst, ft_lstnew(com));
				// write(1, "WTF2", 4);
				com->pipsem = cc;
				i++;
				st = i;
			}
			/*TODO Ctrl+D sempip infinite loop*/
			else if (cc == '|')
			{
				com = command(all->input, st, i - 1);
				ft_lstadd_back(&lst, ft_lstnew(com));
				com->pipsem = cc;
				i++;
				st = i;
			}
			else if (cc == '&')
				i++;
			// else if (cc == '\0')
			// 	i++;
		}
		else
			i++;
		if (all->input[i] == '\n')
		{
			com = command(all->input, st, i - 1);
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

void		pars_get_command(t_all *all)
{
	// t_list	*begin;
	t_com	*com;
	int		i;
	int		n;
	char	str[10];
	char	*commands[7];

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
		n = 0;
		while (n < 7)
		{
			// write(1, commands[n], ft_strlen(commands[n]));
			// write(1, str, ft_strlen(str));
			if (ft_strncmp(str, &commands[n++][0], i) == 0)
			{
				com->type = n;
				// write(1, str, i);
				printf("%s\t%d\n", str, i);
				// ft_putnbr_fd(i, 1);
				// write(1, "\n", 1);
				break ;
			}
			// else
			// 	break ;
		}
		printf("getcom\t_%s_\t_%d_\t_%c_%d\n", com->line, com->type, com->pipsem, i);
		all->lst = all->lst->next;
	}
	// n = 0;
	// while (commands[n] != '\0')
	// {
	// 	m = 0;
	// 	while(commands[m] != ' ')
	// 	{
	// 		ft_strncmp();
	// 		commands
	// 	}
	// }
	return ;
}
