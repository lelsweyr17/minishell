#include "../headers/minishell.h"

void	sig_int(int i)
{
	ft_putendl_fd("", 2);
}

void	sig_quit(int i)
{
	ft_putendl_fd("Quit: 3", 2);
}
