#include "minishell.h"

void	*del(void *content)
{
	// content = 0;
	free(content);
	return (0);
}

char	*strjoin_free(char **line, char *ln)
{
	char				*tmp;

	tmp = ft_strjoin(*line, ln);
	free(*line);
	*line = tmp;
	return (*line);
}

void		parser(t_all *all) //, char **line)
{
	// int		len;
	// int		i;

	// i = 0;
	pars_split_commands(all, all->input);
	
	// // printf("p %d i %d line %s\n", len, i, *line);
	// while ((all->input)[i] != '\n')
	// {
	// 	// printf("i %d %c\n", i, (*line)[i]);
	// 	if ((all->input)[i++] == 34)
	// 		write(1, "SS\n", 3);
	// }
	// // write(1, "nn", 2);
	// // ft_putnbr_fd(i, 1);
	// // write(1, &(*line)[i], 1);
	// write(1, "nothingtodo\n", 12);
	return ;
}

int			main(int argc, char *argv[], char *envp[])
{
	t_all	all;
	int		res;
	char	buf[1000];
	struct termios term;
	char	*term_name = "xterm-256color";
	t_com	*com;

    // ft_putnbr(ft_strlen(*envp));
	// write(1, &ft_strlen(envp), 200);
	// while (*envp)
	// {
	// 	write(1, *envp, ft_strlen(*envp));
	// 	write(1, "\n", 1);
	// 	envp++;
	// }
	// line = NULL;
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, term_name);
	// term.c_cc[VMIN] = 1;
	// term.c_cc[VTIME] = 0;
	// write(1, "sh: ", 4);
	// char *ss = key_right;
	// char *ss = tgetstr("kr", 0);
	while (ft_strcmp(buf, "\4"))
	{
		all.input = ft_strdup("");
		write(1, "::: ", 4);
		tputs(save_cursor, 1, ft_iputchar);
		do
		{
			res = read(0, buf, 100);
			// gnl = get_next_line(0, &line);
			// printf("%d", res);
			// line[res] = 0;
			// if (gnl > 0)
			// parser(envp, line);
			if (!ft_strcmp(buf, "\e[A"))
			{
				tputs(restore_cursor, 1, ft_iputchar);
				tputs(tigetstr("ed"), 1, ft_iputchar);
				write(1, "prev", 4);
			}
			else if (!ft_strcmp(buf, "\e[B"))
			{
				tputs(restore_cursor, 1, ft_iputchar);
				tputs(tigetstr("ed"), 1, ft_iputchar);
				write(1, "next", 4);
			}
			else if (!strcmp(buf, "\177"))
			{
				tputs(cursor_left, 1, ft_iputchar);
				tputs(tgetstr("dc", 0), 1, ft_iputchar);
			}
			else if (ft_strcmp(buf, "\4"))
			{
				write(1, buf, res);
				// write(1, "asdf", 4);
				all.input = strjoin_free(&all.input, buf);
				// write(1, &line, ft_strlen(all.line));
			}
			if (!ft_strcmp(buf, "\4"))
			{
				write(1, "exit", 4);
				// exit (0);
			}
		} while (ft_strcmp(buf, "\n") && ft_strcmp(buf, "\4"));
		parser(&all); //, &all.input);
		// write(1, "shit", 4);
		while (all.lst)
		{
			com = all.lst->content;
			ft_putendl_fd(com->line, 1);
			// if (com->line)
			ft_lstdelone(all.lst, del(com->line));
			// ft_lstdelone(all.lst, del(com->comm));
			ft_lstdelone(all.lst, del(com));
			all.lst = all.lst->next;
		}
		if (all.input)
		{
			// history(all.input);
			free(all.input);
		}
	}
	write(1, "\n", 1);
	return (0);
}