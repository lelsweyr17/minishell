#include "minishell.h"

void	*del(void *content)
{
	content = 0;
	free(content);
	return (0);
}

char	*str_free(char **line, char *tmp) // вторым аргументом отправляешь функцию которая возвращает указатель на строку # line = str_free(&line, ft_strjoin(line1, line2));
{
	free(*line);
	return (tmp);
}

void		parser(t_all *all) //, char **line)
{
	// int		len;
	// int		i;

	// i = 0;
	if (all->input[0] == '#')
		return ;
	pars_split_commands(all);
	pars_split_args(all);
	pars_get_command(all);
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
	// return ;
}

int			main(int argc, char *argv[], char *envp[])
{
	t_all	all;
	int		res;
	char	buf[1000];
	struct termios term;
	char	*term_name = "xterm-256color";
	t_com	*com;
	t_list	*tmp;
	t_dlist	*hist;
	t_dlist *empty;
	int		len;
	char	*copy;

	all.lst = 0;
	empty = 0;
	empty = ft_dlstnew(empty);
	len = 0;
	hist = 0;
	all.env = envp;
	if (!argc || !argv)
		exit(0);
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
	// term.c_lflag &= ~(ISIG);
	term.c_lflag &= ~(ICANON);
	// tcsetattr(1, TCSANOW, &term);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, term_name);
	// execve("/bin/bash", NULL, NULL);
	// term.c_cc[VMIN] = 1;
	// term.c_cc[VTIME] = 0;
	// write(1, "sh: ", 4);
	// char *ss = key_right;
	// char *ss = tgetstr("kr", 0);
	// hist = ft_dlstnew(all.input);
	copy = 0;
	ft_dlstadd_back(&hist, ft_dlstnew(ft_strdup("")));
	while (ft_strcmp(buf, "\4"))
	{
		if (((char *)hist->content)[0] != '\0')
			ft_dlstadd_back(&hist, ft_dlstnew(ft_strdup("")));
		while (hist->next)
			hist = hist->next;
		// all.input = ft_strdup("");
		write(1, "::: ", 4);
		tputs(save_cursor, 1, ft_iputchar);
		do
		{
            ft_memset(buf, 0, res);
			res = read(0, buf, 100);
			if (!ft_strcmp(buf, "\e[A") && hist->content)// && hist->prev)
			{
				tputs(restore_cursor, 1, ft_iputchar);
				tputs(tigetstr("ed"), 1, ft_iputchar);
				if (hist->prev)
					hist = hist->prev; // UP
				write(1, hist->content, ft_strlen(hist->content));
			}
			else if (!ft_strcmp(buf, "\e[B") && hist->next)
			{
				tputs(restore_cursor, 1, ft_iputchar);
				tputs(tigetstr("ed"), 1, ft_iputchar);
				hist = hist->next; // DOWN
				write(1, hist->content, ft_strlen(hist->content));
			}
			else if (!ft_strcmp(buf, "\e[C"))
			{
				continue ;
				// tputs(restore_cursor, 1, ft_iputchar);
				// tputs(tigetstr("ed"), 1, ft_iputchar);
			}
			else if (!ft_strcmp(buf, "\e[D"))
			{
				continue ;
				// tputs(restore_cursor, 1, ft_iputchar);
				// tputs(tigetstr("ed"), 1, ft_iputchar);
			}
			else if (!strcmp(buf, "\177") && len > 0 && res > 0)
			{
				tputs(cursor_left, 1, ft_iputchar);
				tputs(tigetstr("ed"), 1, ft_iputchar);
				((char *)hist->content)[--len] = '\0';
			}
			else if (!ft_strcmp(buf, "\3"))
			{
				write(1, "^C\n", 4);
				break ;
			}
			else if (!ft_strcmp(buf, "\34"))
			{
				write(1, "^\\Quit: 3\n", 10);
			}
			else if (ft_strcmp(buf, "\4") && strcmp(buf, "\177"))
			{
			    write(1, buf, res);
				if (!hist->next && !copy)
				{
					copy = ft_strdup(hist->content);
				}
				// all.input = str_free(&all.input, ft_strjoin(all.input, buf));
				hist->content = str_free((char **)&hist->content, ft_strjoin(hist->content, buf));
				len = ft_strlen(hist->content);
				if (!ft_strcmp(buf, "\n"))
					((char *)hist->content)[len - 1] = '\0';
			}
			if (!ft_strcmp(buf, "\4"))
			{
				write(1, "exit", 4);
				exit (0);
			}
		} while (ft_strcmp(buf, "\n") && ft_strcmp(buf, "\4"));
		all.input = (char *)hist->content;
		// all.input[len] = '\0';
		// term.c_lflag |= (ICANON);
		// term.c_lflag |= (ECHO);
        // all.input = "\"e\" \"c\\\"\"h\\\"o\\' '1\\'\n";
		// all.input = "ec\"\"H'O' \\' 5 \"#f\\\" ; | \\\\\" ' \\f\\' ; env";
		// all.input = "\"E\"c'h'O \' '\\dfa\"\'\"\\\"df\" | env";
		// all.input = "\n";
		// all.input = "echo bb cc; E\"c\"'h'O \"d\" '\\' ee ff\n";
		// all.input = "echo '-'\"n\" -nnnn -nnnf df";
		// all.input = "echo   -nn'n'    -nn  -n   -nnnnnnnf ldfj f                   aa55   \"ff\\'df\"  '\\ dfdf'   \n";
		// all.input = "echo df      fdfd \"\\\" | \\\\ l  \"";
		// all.input = "\\\\";
		// all.input = "fdfj $USER+sf fjf";
        if (!isnotempty(all.input))
		{
			write(1, "FUCK", 4);
			ft_memset(all.input, 0, len);
			free(all.input);
		}
		buf[0] = '\n';
		if (all.input[0] != '\0' && !ft_strcmp(buf, "\n") && *all.input != '\n')
			parser(&all);
		// exit (0);
		while (all.lst && *all.input != '\n')
		{
			com = all.lst->content;
			// ft_putendl_fd(com->line, 1);
			if (com->line)
				ft_lstdelone(all.lst, del(&com->line));
			ft_lstdelone(all.lst, del(&com));
			tmp = all.lst;
			all.lst = all.lst->next;
			free(tmp);
		}
	}
	write(1, "\n", 1);
	return (0);
}