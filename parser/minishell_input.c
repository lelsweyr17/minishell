#include "../headers/minishell.h"

void	hist_moving(t_all *all, char buf[1000], t_dlist **hist)
{
	if (!ft_strcmp(buf, "\e[A") && all->hist->prev)
	{
		tputs(restore_cursor, 1, ft_iputchar);
		tputs(clr_eos, 1, ft_iputchar);
		all->hist = all->hist->prev;
		write(1, all->hist->cont, ft_strlen(all->hist->cont));
		all->p->len = ft_strlen(all->hist->cont);
		all->p->pos = all->p->len;
	}
	else if (!ft_strcmp(buf, "\e[B") && all->hist->next)
	{
		tputs(restore_cursor, 1, ft_iputchar);
		tputs(clr_eos, 1, ft_iputchar);
		all->hist = all->hist->next;
		write(1, all->hist->cont, ft_strlen(all->hist->cont));
		all->p->len = ft_strlen(all->hist->cont);
		all->p->pos = all->p->len;
	}
	*hist = all->hist;
	buf[0] = '\0';
}

char	*linemovingright(t_all *all, char buf[1000], int res)
{
	if (all->p->pos < all->p->len)
	{
		if (!ft_strcmp(buf, "\e[C"))
		{
			tputs(cursor_right, 1, ft_iputchar);
			all->p->pos++;
		}
		else if (!ft_strncmp(buf, "\5", 1) || !ft_strcmp(buf, "\e[F"))
		{
			while (all->p->pos != all->p->len)
			{
				all->p->pos++;
				tputs(cursor_right, 1, ft_iputchar);
			}
		}
	}
	return (str_free(&all->end, ft_strdup(&all->hist->cont[all->p->pos])));
}

char	*linemovingleft(t_all *all, char buf[1000], int res)
{
	if (all->p->pos > 0)
	{
		if (!ft_strcmp(buf, "\e[D"))
		{
			tputs(cursor_left, 1, ft_iputchar);
			all->p->pos--;
		}
		else if (!ft_strncmp(buf, "\1", 1) || !ft_strcmp(buf, "\e[H"))
		{
			tputs(restore_cursor, 1, ft_iputchar);
			all->p->pos = 0;
			all->end = str_free(&all->end, ft_strdup(all->hist->cont));
		}
	}
	return (str_free(&all->end, ft_strdup(&all->hist->cont[all->p->pos])));
}

char	*linemovebywords(t_all *all, char buf[1000], int res)
{
	if (all->p->pos < all->p->len && !ft_strcmp(buf, "\ef"))
	{
		while (all->p->pos != all->p->len)
		{
			all->p->pos++;
			tputs(cursor_right, 1, ft_iputchar);
			if (ft_isalnum(all->hist->cont[all->p->pos - 1])
				&& !ft_isalnum(all->hist->cont[all->p->pos]))
				break ;
		}
	}
	else if (all->p->pos > 0 && !ft_strcmp(buf, "\eb"))
	{
		while (all->p->pos != 0)
		{
			all->p->pos--;
			tputs(cursor_left, 1, ft_iputchar);
			if (!ft_isalnum(all->hist->cont[all->p->pos - 1])
				&& ft_isalnum(all->hist->cont[all->p->pos]))
				break ;
		}
	}
	return (str_free(&all->end, ft_strdup(&all->hist->cont[all->p->pos])));
}

void	lineedit(t_all *all, char buf[1000], t_p *p, t_dlist *hist)
{
	if (!ft_strcmp(buf, "\e[A") || !ft_strcmp(buf, "\e[B"))
		hist_moving(all, buf, &hist);
	else if (!ft_strcmp(buf, "\e[C") || !ft_strncmp(buf, "\5", 1)
		|| !ft_strcmp(buf, "\e[F"))
		all->end = linemovingright(all, buf, p->res);
	else if (!ft_strcmp(buf, "\e[D") || !ft_strncmp(buf, "\1", 1)
		|| !ft_strcmp(buf, "\e[H"))
		all->end = linemovingleft(all, buf, p->res);
	else if (!ft_strcmp(buf, "\ef") || !ft_strcmp(buf, "\eb"))
		all->end = linemovebywords(all, buf, p->res);
	else if (break_n_cycle(all, buf, p->len))
		p->nl = 1;
	else if (!strcmp(buf, "\177") && p->len > 0 && p->pos > 0)
		backspase(all, p);
	else if (!strcmp(buf, "\e[3~") && hist->cont[p->pos] != '\0')
		deletebutton(all, p);
	else if (*buf < 32 || *buf > 126)
		return ;
	else
		hist->cont = lineinput(all, buf, p, hist->cont);
}
