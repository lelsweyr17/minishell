#include "../headers/minishell.h"

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

char	*lineinput(t_all *all, char buf[1000], t_p *p, char *cont)
{
	int	i;

	i = 0;
	if (all->end[0] != '\0')
	{
		cont[p->pos] = '\0';
		p->pos += p->res;
		cont = str_free(&cont, ft_strjoin(cont, &buf[all->nl]));
		cont = str_free(&cont, ft_strjoin(cont, all->end));
		p->len = ft_strlen(cont);
		tputs(restore_cursor, 1, ft_iputchar);
		tputs(clr_eos, 1, ft_iputchar);
		write(1, cont, p->len);
		while (i++ < p->len - p->pos)
			tputs(cursor_left, 1, ft_iputchar);
	}
	else
	{
		write(1, buf, p->res);
		cont = str_free(&cont, ft_strjoin(cont, &buf[all->nl]));
	}
	p->len = ft_strlen(cont);
	if (all->end[0] == '\0')
		p->pos = p->len;
	return (cont);
}
