#include "../../headers/processor.h"

void	init_error(int err, int *error)
{
	*error = err;
}

void	write_error(char *com, char *arg, char *comment)
{
	write(2, "minishell: ", 11);
	if (com)
	{
		write(2, com, ft_strlen(com));
		write(2, ": ", 2);
	}
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	if (comment)
		write(2, comment, ft_strlen(comment));
	write(2, "\n", 1);
}
