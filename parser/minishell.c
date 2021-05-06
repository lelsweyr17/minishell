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

void	backspase(t_all *all, t_p *p)
{
	int	i;

	i = 0;
	tputs(cursor_left, 1, ft_iputchar);
	tputs(clr_eos, 1, ft_iputchar);
	pars_shift_line(&all->hist->cont, --p->pos);
	p->len--;
	write(1, all->end, ft_strlen(all->end));
	while (i++ < p->len - p->pos)
		tputs(cursor_left, 1, ft_iputchar);
}

void	deletebutton(t_all *all, t_p *p)
{
	int	i;

	i = 0;
	tputs(clr_eos, 1, ft_iputchar);
	pars_shift_line(&all->hist->cont, p->pos);
	pars_shift_line(&all->end, 0);
	p->len--;
	write(1, all->end, ft_strlen(all->end));
	while (i++ < p->len - p->pos)
		tputs(cursor_left, 1, ft_iputchar);
}

void	lineinput(t_all *all, char buf[1000], t_p *p, t_dlist *hist)
{
	if (all->end[0] != '\0')
	{
		hist->cont[p->pos] = '\0';
		p->pos += p->res;
		hist->cont = str_free(&hist->cont, ft_strjoin(hist->cont, &buf[all->nl]));
		hist->cont = str_free(&hist->cont, ft_strjoin(hist->cont, all->end));
		p->len = ft_strlen(hist->cont);
		tputs(restore_cursor, 1, ft_iputchar);
		tputs(clr_eos, 1, ft_iputchar);
		write(1, hist->cont, p->len);
		int i = 0;
		while(i++ < p->len - p->pos)
			tputs(cursor_left, 1, ft_iputchar);
	}
	else
	{
		write(1, buf, p->res);
		hist->cont = str_free(&hist->cont, ft_strjoin(hist->cont, &buf[all->nl]));
	}
	p->len = ft_strlen(hist->cont);
	if (all->end[0] == '\0')
		p->pos = p->len;
}

void	n_cycle(t_all *all, char buf[1000], t_p *p, t_dlist *hist)
{
	if (!ft_strcmp(buf, "\e[A") || !ft_strcmp(buf, "\e[B"))
		hist_moving(all, buf, &hist);
	else if (!ft_strcmp(buf, "\e[C") || !ft_strcmp(buf, "\e[D") || !ft_strncmp(buf, "\1", 1) || !ft_strcmp(buf, "\e[H") || !ft_strncmp(buf, "\5", 1) || !ft_strcmp(buf, "\e[F") || !ft_strcmp(buf, "\eb") || !ft_strcmp(buf, "\ef"))
		move_righ_left(all, buf, p->res);
	else if (break_n_cycle(all, buf, p->len))
		p->nl = 1;
	else if (!strcmp(buf, "\177") && p->len > 0 && p->pos > 0)
		backspase(all, p);
	else if (!strcmp(buf, "\e[3~") && hist->cont[p->pos] != '\0')
		deletebutton(all, p);
	else if (*buf < 32 || *buf > 126)
		return ;
	else
		lineinput(all, buf, p , hist);
}

void	n_cycle_begin(t_all *all)
{
	char	buf[1000];

	ft_bzero(all->p, sizeof(t_p));
	all->end[0] = '\0';
	while (!all->p->nl)
	{
		all->p->res = get_read(all, buf, all->p->res);
		n_cycle(all, buf, all->p, all->hist);
	}
	all->input = all->hist->cont;
	termcap_on(all);
	if (isempty(all->hist->cont, 0))
		ft_bzero(all->hist->cont, all->p->len);
	else
	{
		hist_prep(all->hist, all->fn);
		executor(all);
	}
}

void	d_cycle(t_all *all)
{
	t_dlist	*hist;

	hist = all->hist;
	all->p->ctrld = 0;
	all->nl = 0;
	g_err = 0;
	while (!all->p->ctrld)
	{
		termcap_off(all);
		if (!hist->cont || !isempty(hist->cont, 0))
			ft_dlstadd_back(&hist, ft_dlstnew(ft_strdup("")));
		if (g_err)
			init_error(g_err, &all->proc->error);
		g_err = 0;
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
	all.end = ft_strdup("");
	signal(SIGINT, &sighandler);
	signal(SIGQUIT, &sighandler);
	if (!argc || !argv)
		exit(0);
	termcap(&all);
	hist_file(&all);
	d_cycle(&all);
	return (0);
}
