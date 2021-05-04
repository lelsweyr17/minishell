#include "../headers/minishell.h"

int	break_n_cycle(t_all *all, char buf[1000], int len)
{
	if (!ft_strcmp(buf, "\n"))
		*buf = '\0';
	else if (!ft_strcmp(buf, "\3"))
	{
		ft_bzero(all->hist->cont, len);
		init_error(1, &all->proc->error);
	}
	else if (!ft_strcmp(buf, "\4") && len == 0)
	{
		all->p->ctrld = 1;
		write(1, "exit", 4);
	}
	else
		return (0);
	write(1, "\n", 1);
	return (1);
}

void	n_cycle(t_all *all, char buf[1000], t_p *p, t_dlist *hist)
{
	if (!ft_strcmp(buf, "\e[A") || !ft_strcmp(buf, "\e[B"))
		hist_moving(all, buf, &hist);
	else if (!ft_strcmp(buf, "\e[C") || !ft_strcmp(buf, "\e[D"))
		move_righ_left(all, buf, p->res);
	else if (break_n_cycle(all, buf, p->len))
		p->nl = 1;
	else if (!ft_strcmp(buf, "\34"))
		write(1, "^\\Quit: 3\n", 10);
	else if (!strcmp(buf, "\177") && p->len > 0 && p->res > 0)
	{
		tputs(cursor_left, 1, ft_iputchar);
		tputs(tigetstr("ed"), 1, ft_iputchar);
		(hist->cont)[--p->len] = '\0';
	}
	else if (*buf < 32 || *buf > 126)
		return ;
	else
	{
		write(1, buf, p->res);
		hist->cont = str_free(&hist->cont, ft_strjoin(hist->cont, buf));
	}
}

void	n_cycle_begin(t_all *all)
{
	char	buf[1000];

	ft_bzero(all->p, sizeof(t_p));
	while (!all->p->nl)
	{
		all->p->res = get_read(all, buf, all->p->res);
		n_cycle(all, buf, all->p, all->hist);
		all->p->len = ft_strlen(all->hist->cont);
	}
	all->input = all->hist->cont;
	termcap_on(all);
	if (isempty(all->hist->cont, 0))
		ft_bzero(all->hist->cont, all->p->len);
	else
	{
		hist_prep(all->hist, all->fn);
		executor(all);
		// exit (666);
	}
}

void	d_cycle(t_all *all)
{
	t_dlist	*hist;

	hist = all->hist;
	all->p->ctrld = 0;
	while (!all->p->ctrld)
	{
		termcap_off(all);
		if (!hist->cont || !isempty(hist->cont, 0))
			ft_dlstadd_back(&hist, ft_dlstnew(ft_strdup("")));
		while (hist->next)
			hist = hist->next;
		all->hist = hist;
		write(1, "::: ", 4);
		tputs(save_cursor, 1, ft_iputchar);
		n_cycle_begin(all);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_all	all;

	all.env = arrdup(envp);
	all.p = (t_p *)ft_calloc(1, sizeof(t_p));
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
	return (0);
}
