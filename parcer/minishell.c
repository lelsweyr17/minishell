#include "../headers/minishell.h"

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

void		executor(t_all *all)
{
	if (isempty(all->input, 1))
		return ;
	ft_bzero(&all->par, sizeof(all->par));
	all->lst = 0;
	all->delescape = 0;
	pars_split_commands(all);
	all->delescape = 1;
	pars_get_args(all, all->proc);
	// free(all->proc);
}

void	n_cycle(t_all *all, int *ctrld)
{
	int		res;
	int		len;
	char	buf[1000];
	// char	*bf;
	t_dlist	*hist;

	hist = all->hist;
	res = 0;
	len = 0;
	while (1)
	{
		// if (!ft_strchr(buf, '\n'))
			ft_memset(buf, 0, res);
		// bf = buf;
		res = read(0, buf, 999);
		buf[res] = '\0';
		// write(1, buf, res); /* UNCOMMENT TO SEE SIGNALS */
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
			// ft_bzero(buf, res + 1);
		}
		else if (!ft_strcmp(buf, "\t"))
		{
			ft_bzero(buf, res + 1);
			continue ;
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
			// ft_bzero(buf, res + 1);
		}
		else if (!ft_strcmp(buf, "\e[C"))
		{
			ft_bzero(buf, res + 1);
			continue ;
			// tputs(restore_cursor, 1, ft_iputchar);
			// tputs(tigetstr("ed"), 1, ft_iputchar);
		}
		else if (!ft_strcmp(buf, "\e[D"))
		{
			ft_bzero(buf, res + 1);
			continue ;
			// tputs(restore_cursor, 1, ft_iputchar);
			// tputs(tigetstr("ed"), 1, ft_iputchar);
		}
		else if (!ft_strcmp(buf, "\033"))
		{
			ft_bzero(buf, res + 1);
			continue ;
		}
		// else if (!ft_strcmp(buf, "\e[H"))
		// {

		// }
		else if (!strcmp(buf, "\177") && len > 0 && res > 0) // "\177" BACKSPACE
		{
			tputs(cursor_left, 1, ft_iputchar);
			tputs(tigetstr("ed"), 1, ft_iputchar);
			(hist->content)[--len] = '\0';
		}
		else if (!ft_strcmp(buf, "\3"))
		{
			ft_bzero(hist->content, len);
			write(1, "\n", 1);
			break ;
		}
		else if (!ft_strcmp(buf, "\34"))
		{
			write(1, "^\\Quit: 3\n", 10);
		}
		else if (!ft_strcmp(buf, "\4") && len == 0)
		{
			*ctrld = 1;
			write(1, "exit", 4);
			break ;
		}
		else if (ft_strcmp(buf, "\4") && strcmp(buf, "\177"))
		{
			write(1, buf, res);
			hist->content = str_free(&hist->content, ft_strjoin(hist->content, buf));
		}
		len = ft_strlen(hist->content);
		if (!ft_strcmp(buf, "\n"))
		{
			(hist->content)[len - 1] = '\0';
			break ;
		}
	}
	all->input = hist->content; // do not forget to uncomment!
	termcap_on(all);
	if (isempty(hist->content, 0))
		ft_bzero(hist->content, len);
	else
	{
		hist_prep(hist, all->fn);
		executor(all);
		pars_free(all);
	}
}

void	d_cycle(t_all *all)
{
	int		ctrld;
	t_dlist	*hist;

	ctrld = 0;
	hist = all->hist;
	while (!ctrld)
	{
		termcap_off(all);
		if (!hist->content || !isempty(hist->content, 0))
			ft_dlstadd_back(&hist, ft_dlstnew(ft_strdup("")));
		while (hist->next)
			hist = hist->next;
		all->hist = hist;
		write(1, "ʕ•ᴥ•ʔ -> ", 18);
		tputs(save_cursor, 1, ft_iputchar);
		n_cycle(all, &ctrld);

		// all->input = "\"e\" \"c\\\"\"h\\\"o\\' '1\\'\n";
		// all->input = "ec\"\"H'O' \\' 5 \"#f\\\" ; | \\\\\" ' \\f\\' ; env";
		// all->input = "\"E\"c'h'O \' '\\dfa\"\'\"\\\"df\" | env";
		// all->input = "\n";
		// all->input = "echo bb cc; E\"c\"'h'O \"d\" '\\' ee ff\n";
		// all->input = "echo '-'\"n\" -nnnn -nnnf df";
		// all->input = "echo   -nn'n'    -nn  -n   -nnnnnnnf ldfj f      aa55   \"ff\\'df\"  '\\ dfdf'   \n";
		// all->input = "echo df      fdfd \"\\\" | \\\\ l  \"";
		// all->input = "\\\\";
		// all->input = "fdfj $USER+sf fjf";
		// all->input = "echo $USER $trt";
		// all->input = "echo $USER ; ";
		// all->input = "echo $TERM$USER$PWD ; \\";
		// all->input= "\\'";
		// all->input= "\\'\\"; // TODO
		// all->input = "echo $USER+$PWD";
		// all->input = "echo $q";
		// all->input = "echo 11 22 33";
		// all->input = "echo 1 ; echo 2";
		// all->input = "echo>2";
		// all->input = "echo $USER ;";
		// all->input = "as ;  ;";
		// all->input = "a >> 1 b > 2 c";
		// all->input = "1;2;3;4;5;6";
		// all->input = "echo $R";
		// all->input = "echo $USER ; ls";
		// all->input = "echo asdf ; ls | cat -e ;echo $HOME";
		// all->input = "echo \"\\\\$HOME \\\\\\$HOME \\\\\\\\$HOME $HOME $HOME $HOME\"";
		
		// if (all->input[0] != '\0' && *all->input != '\n')
		// {
		// 	executor(all);
		// 	pars_free(all);
		// }
		// write(1, "FUCK\n", 5);
		// exit (666);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_all	all;

	all.env = arrdup(envp);
	all.proc = (t_proc *)ft_calloc(1, sizeof(t_proc));
	envp = all.env;
	if (!argc || !argv)
		exit(0);
	termcap(&all);
	// execve("/bin/bash", NULL, NULL);
	// term.c_cc[VMIN] = 1;
	// term.c_cc[VTIME] = 0;
	// write(1, "sh: ", 4);
	// char *ss = key_right;
	// char *ss = tgetstr("kr", 0);
	hist_file(&all);
	d_cycle(&all);
	write(1, "\n", 1);
	return (0);
}