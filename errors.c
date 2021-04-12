#include "minishell.h"

void	init_error(int err, int *error)
{
	*error = err;
}

void	write_error(char *com, char *arg, char *comment)
{
	write(1, "minishell: ", 11);
	if (com)
	{
		write(1, com, ft_strlen(com));
		write(1, ": ", 2);
	}
	if (arg)
	{
		write(1, arg, ft_strlen(arg));
		write(1, ": ", 2);
	}
	if (comment)
		write(1, comment, ft_strlen(comment));
	write(1, "\n", 1);
}
