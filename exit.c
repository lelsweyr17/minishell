#include "header_commands.h"

int	ft_is_number(char *a)
{
	int	i;
	int	res;
	int	count;

	i = -1;
	res = 0;
	count = 1;
	while (a[++i])
	{
		if (ft_isdigit(a[i]))
		{
			res = res * count + (a[i] - '0');
			count = 10;
		}
		else
			return (-1);
	}
	return (res);
}

void	exit_command(t_command *com)
{
	int	i;
	int	res;

	i = -1;
	if (!com->arg)
	{
		write(1, "exit\n", 5);
		exit(com->error);
	}
	else if (com->arg && ft_strrchr(com->arg, ' '))
	{
		write_error("exit", NULL, "too many arguments");
		init_error(1, &com->error);
	}
	else
	{
		res = ft_is_number(com->arg);
		if (res != -1)
		{
			write(1, "exit\n", 5);
			exit(res % 256);
		}
		write_error("exit", com->arg, "numeric argument required");
		exit(255);
	}
}
