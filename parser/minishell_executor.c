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

int	get_read(t_all *all, char *buf, int res)
{
	ft_memset(buf, 0, res);
	if (all->nl == 0)
	{
		all->res = read(0, buf, 999);
		if (all->res < 0)
			exit (0);
		buf[all->res] = '\0';
		// all->el = all->res;
	}
	// all->nl = 0;
	// if (all->res > 1)
	// {
	// 	while (!all->nl && buf[all->el] != '\0')// && buf[all->el] != '\n') //all->el < 999 && 
	// 	{
	// 		if (buf[all->el] == '\n')
	// 		{
	// 			buf[all->el] = '\0';
	// 			all->p->nl = 1;
	// 			all->nl = &buf[all->el + 1];
	// 			// break ;
	// 		}
	// 		all->el++;
	// 	}
	// 	// if (all->nl)
	// 	// {

	// 	// }
	// }
	return (all->res);
}

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

void	move_righ_left(t_all *all, char buf[1000], int res)
{
	if (!ft_strcmp(buf, "\e[C") && all->p->pos < all->p->len)
	{
		tputs(cursor_right, 1, ft_iputchar);
		all->p->pos++;
		all->end = str_free(&all->end, ft_strdup(&all->hist->cont[all->p->pos]));
	}
	else if (!ft_strcmp(buf, "\e[D") && all->p->pos > 0)
	{
		tputs(cursor_left, 1, ft_iputchar);
		all->p->pos--;
		all->end = str_free(&all->end, ft_strdup(&all->hist->cont[all->p->pos]));
	}
	else if (!ft_strncmp(buf, "\1", 1) || !ft_strcmp(buf, "\e[H"))
	{
		tputs(restore_cursor, 1, ft_iputchar);
		all->p->pos = 0;
		all->end = str_free(&all->end, ft_strdup(all->hist->cont));
	}
	else if ((!ft_strncmp(buf, "\5", 1) || !ft_strcmp(buf, "\e[F")) && all->p->pos < all->p->len)
	{
		while (all->p->pos != all->p->len)
		{
			all->p->pos++;
			tputs(cursor_right, 1, ft_iputchar);
		}
		all->end[0] = '\0';
	}
	else if (!ft_strcmp(buf, "\ef") && all->p->pos < all->p->len)
	{
		while (all->p->pos != all->p->len)
		{
			all->p->pos++;
			tputs(cursor_right, 1, ft_iputchar);
			if (ft_isalnum(all->hist->cont[all->p->pos - 1]) && !ft_isalnum(all->hist->cont[all->p->pos]))
				break ;
		}
		all->end = str_free(&all->end, ft_strdup(&all->hist->cont[all->p->pos]));
	}
	else if (!ft_strcmp(buf, "\eb") && all->p->pos > 0)
	{
		while (all->p->pos != 0)
		{
			all->p->pos--;
			tputs(cursor_left, 1, ft_iputchar);
			if (!ft_isalnum(all->hist->cont[all->p->pos - 1]) && ft_isalnum(all->hist->cont[all->p->pos]))
				break ;
		}
		all->end = str_free(&all->end, ft_strdup(&all->hist->cont[all->p->pos]));
	}
}
