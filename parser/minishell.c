#include "../headers/minishell.h"

void	executor(t_all *all)
{
	if (isempty(all->input, 1))
		return ;
	ft_bzero(all->p, sizeof(t_p));
	all->lst = 0;
	all->delescape = 0;
	pars_split_commands(all);
	all->delescape = 1;
	pars_get_args(all);
	pars_free(all);
}

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
		exit (all->proc->error);
	}
	else
		return (0);
	write(1, "\n", 1);
	return (1);
}

void	n_cycle(t_all *all)
{
	char	buf[1000];

	ft_bzero(all->p, sizeof(t_p));
	all->end[0] = '\0';
	while (!all->p->nl)
	{
		all->p->res = get_read(all, buf, all->p->res);
		lineedit(all, buf, all->p, all->hist);
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
		if (!all->proc->error)
			g_err = 0;
		if (g_err)
			init_error(g_err, &all->proc->error);
		while (hist->next)
			hist = hist->next;
		all->hist = hist;
		write(1, "::: ", 4);
		tputs(save_cursor, 1, ft_iputchar);
		n_cycle(all);
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
