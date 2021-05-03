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
	int	nl;

	nl = 0;
	ft_memset(buf, 0, res);
	res = read(0, buf, 999);
	if (res < 0)
		exit (0);
	buf[res] = '\0';
	// while (nl <= 999 && buf[nl] != '\0')
	// {
	// 	if (buf[nl] == '\n')
	// 	{
	// 		buf[nl] = '\0';
	// 	}
	// }
	return (res);
}

void	hist_moving(t_all *all, char buf[1000], t_dlist **hist)
{
	if (!ft_strcmp(buf, "\e[A") && all->hist->prev)
	{
		tputs(restore_cursor, 1, ft_iputchar);
		tputs(tigetstr("ed"), 1, ft_iputchar);
		all->hist = all->hist->prev;
		write(1, all->hist->cont, ft_strlen(all->hist->cont));
	}
	else if (!ft_strcmp(buf, "\e[B") && all->hist->next)
	{
		tputs(restore_cursor, 1, ft_iputchar);
		tputs(tigetstr("ed"), 1, ft_iputchar);
		all->hist = all->hist->next;
		write(1, all->hist->cont, ft_strlen(all->hist->cont));
	}
	*hist = all->hist;
	buf[0] = '\0';
}

void	move_righ_left(t_all *all, char buf[1000], int res)
{
	// char	*end;

	if (!ft_strcmp(buf, "\e[C")) // RIGHT 
	{
		buf[0] = '\0';
		return ;
		// tputs(restore_cursor, 1, ft_iputchar);
		// tputs(tigetstr("ed"), 1, ft_iputchar);
	}
	else if (!ft_strcmp(buf, "\e[D")) // LEFT
	{
		buf[0] = '\0';
		return ;
		// tputs(restore_cursor, 1, ft_iputchar);
		// tputs(tigetstr("ed"), 1, ft_iputchar);
	}
	else if (!ft_strncmp(buf, "\5", 1)) // \1 HOME \5 END
	{
		ft_bzero(buf, res + 1);
		return ;
	}
}
