#include "../../headers/processor.h"

int	build_in_check_error(char *build_in, char *arg, t_proc *com, t_com *list)
{
	int	len;

	len = ft_strlen(build_in);
	if (list->type != 128 && arg[len] == '/')
	{
		write_error(arg, NULL, "No such file or directory");
		init_error(127, &com->error);
		return (1);
	}
	if (list->type != 128 && arg[len] <= 32)
	{
		write_error(arg, NULL, "command not found");
		init_error(127, &com->error);
		return (1);
	}
	return (0);
}

int	check_build_in_with_slesh(char *arg, t_proc *com, t_com *list)
{
	int		i;
	int		len;
	char	*build_in[8];

	i = -1;
	build_in[0] = "echo";
	build_in[1] = "cd";
	build_in[2] = "pwd";
	build_in[3] = "export";
	build_in[4] = "unset";
	build_in[5] = "env";
	build_in[6] = "exit";
	build_in[7] = NULL;
	while (build_in[++i])
	{
		if (build_in_check_error(build_in[i], arg, com, list))
			return (1);
	}
	return (0);
}
