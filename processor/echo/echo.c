#include "../../headers/processor.h"

int	array_size(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
		i++;
	return (i);
}

void	echo_command(t_proc *com, char **envp, t_com *list)
{
	int		i;

	i = 0;
	while (com->arg && com->arg[i])
	{
		if (!ft_strncmp(com->arg, "$?", 3))
		{
			if (com->error >= 256)
				com->error /= 256;
			ft_putnbr_fd(com->error, 1);
			init_error(0, &com->error);
			i += 2;
		}
		while (com->arg[i] && (com->arg[i] != '$' && com->arg[i + 1] != '?'))
			write(1, &com->arg[i++], 1);
	}
	if (!list->n)
		write(1, "\n", 1);
}
