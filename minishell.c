#include "minishell.h"

char	**arrdup(char **envp)
{
	int		i;
	char	**env;

	i = -1;
	env = (char **)ft_calloc(array_size(envp) + 1, sizeof(char *));
	while (envp[++i])
		env[i] = ft_strdup(envp[i]);
	env[i] = NULL;
	return (env);
}

void		parser(t_all *all)
{
	if (isempty(all->input, 1))
		return ;
	ft_bzero(&all->par, sizeof(all->par));
	all->lst = 0;
	pars_split_commands(all);
	pars_get_args(all);
	
}

void	hist_prep(t_dlist *hist, char *tmp, char *input)
{
	if (hist->next)
	{
		if (tmp)
			free(tmp);
		hist->content = ft_strdup(hist->dup);
	}
	while (hist->next)
		hist = hist->next;
	hist->dup = ft_strdup(input);
	free(input);
	hist->content = ft_strdup(hist->dup);
}

int			main(int argc, char *argv[], char *envp[])
{
	t_all	all;
	int		res;
	char	buf[1000];
	// char	*bf;
	struct termios term;
	// t_com	*com;
	t_dlist	*hist;
	// t_dlist *empty;
	int		len;
	char	*tmp;

	all.lst = 0;
	// empty = 0;
	// empty = ft_dlstnew(empty);
	len = 0;
	hist = 0;
	all.env = arrdup(envp);
	if (!argc || !argv)
		exit(0);
    tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	// term.c_lflag &= ~(ISIG);
	term.c_lflag &= ~(ICANON);
	// tcsetattr(1, TCSANOW, &term);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, getenv("TERM"));
	// execve("/bin/bash", NULL, NULL);
	// term.c_cc[VMIN] = 1;
	// term.c_cc[VTIME] = 0;
	// write(1, "sh: ", 4);
	// char *ss = key_right;
	// char *ss = tgetstr("kr", 0);
	// hist = ft_dlstnew(all.input);
	ft_dlstadd_back(&hist, ft_dlstnew(ft_strdup("")));
	while (ft_strcmp(buf, "\4"))
	{
		len = 0;
		if (!isempty(hist->content, 0))// && hst == 0)
			ft_dlstadd_back(&hist, ft_dlstnew(ft_strdup("")));
		while (hist->next)
			hist = hist->next;
		// all.input = ft_strdup("");
		write(1, "::: ", 4);
		tputs(save_cursor, 1, ft_iputchar);
		do
		{
			// if (!ft_strchr(buf, '\n'))
				ft_memset(buf, 0, res);
			// bf = buf;
			res = read(0, buf, 100);
			// buf[res] = '\0';
			// bf = ft_strchr(buf, '\n')
			// if (*bf == '\n')
			// 	*bf = '\0';
			// res = get_next_line(0, &buf);
			if (!ft_strcmp(buf, "\e[A"))// && hist->prev) // "\e[A"
			{
				if (hist->prev)
				{
					tputs(restore_cursor, 1, ft_iputchar);
					tputs(tigetstr("ed"), 1, ft_iputchar);
					hist = hist->prev; // UP
					write(1, hist->content, ft_strlen(hist->content));
				}
				ft_bzero(buf, res + 1);
			}
			else if (!ft_strcmp(buf, "\e[B")) // "\e[B"
			{
				if (hist->next)
				{
					tputs(restore_cursor, 1, ft_iputchar);
					tputs(tigetstr("ed"), 1, ft_iputchar);
					hist = hist->next; // DOWN
					write(1, hist->content, ft_strlen(hist->content));
				}
				ft_bzero(buf, res + 1);
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
			else if (!strcmp(buf, "\177") && len > 0 && res > 0) // "\177" BACKSPACE
			{
				tputs(cursor_left, 1, ft_iputchar);
				tputs(tigetstr("ed"), 1, ft_iputchar);
				(hist->content)[--len] = '\0';
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
				hist->content = str_free(&hist->content, ft_strjoin(hist->content, buf));
				if (hist->next == 0)
					tmp = hist->content;
			}
			len = ft_strlen(hist->content);
			if (!ft_strcmp(buf, "\n"))
				(hist->content)[len - 1] = '\0';
			if (!ft_strcmp(buf, "\4"))
			{
				write(1, "exit", 4);
				exit (0);
			}
		} while (ft_strcmp(buf, "\n") && ft_strcmp(buf, "\4"));
		// write(1, "TEMP: ", 6);
		// write(1, tmp, ft_strlen(tmp));
		// ft_putnbr_fd(len, 1);
		// write(1, "\n", 1);
		all.input = ft_strdup(hist->content); /* is there ft_strdup() need? */
		free(hist->content);
		if (isempty(hist->content, 0))
		{
			write(1, "EMPTY\n", 6);
			// ft_memset(all.input, 0, len);
			ft_memset(hist->content, 0, len);
		}
// 		write(1, "VHOD:_", 6);
// 		write(1, all.input, ft_strlen(all.input));
// 		write(1, "_\n", 2);
		// all.input[len] = '\0';
		// term.c_lflag |= (ICANON);
		// term.c_lflag |= (ECHO);
        // all.input = "\"e\" \"c\\\"\"h\\\"o\\' '1\\'\n";
		// all.input = "ec\"\"H'O' \\' 5 \"#f\\\" ; | \\\\\" ' \\f\\' ; env";
		// all.input = "\"E\"c'h'O \' '\\dfa\"\'\"\\\"df\" | env";
		// all.input = "\n";
		// all.input = "echo bb cc; E\"c\"'h'O \"d\" '\\' ee ff\n";
		// all.input = "echo '-'\"n\" -nnnn -nnnf df";
		// all.input = "echo   -nn'n'    -nn  -n   -nnnnnnnf ldfj f      aa55   \"ff\\'df\"  '\\ dfdf'   \n";
		// all.input = "echo df      fdfd \"\\\" | \\\\ l  \"";
		// all.input = "\\\\";
		// all.input = "fdfj $USER+sf fjf";
		// all.input = "echo $USER $trt";
		// all.input = "echo $USER ; ";
		// all.input = "echo $TERM$USER$PWD ; \\";
		// all.input= "\\'";
		// all.input= "\\'\\"; // TODO
		// all.input = "echo $USER+$PWD";
		// all.input = "echo $q";
		// all.input = "echo 11 22 33";
		// all.input = "echo 1 ; echo 2";
		// all.input = "echo>2";
		// all.input = "echo $USER ;";
		// all.input = "as ;  ;";
		// all.input = "a >> 1 b > 2 c";
		// all.input = "1;2;3;4;5;6";
		// all.input = "echo $R";
		// buf[0] = '\n';
		if (all.input[0] != '\0' && *all.input != '\n')// && !ft_strcmp(buf, "\n"))
			parser(&all);
		hist_prep(hist, tmp, all.input);
		pars_free(&all);
		// exit (0);
	}
	write(1, "\n", 1);
	return (0);
}