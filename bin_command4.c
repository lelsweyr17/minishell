#include "header_commands.h"

void	write_command_not_found(t_command *com)
{
	write_error(com->com, NULL, "command not found");
	init_error(127, &com->error);
}

int	check_file_before_exec(char **envp, t_command *com, char *command_tmp)
{
	int	flag;
	int	check;
	int	find;

	flag = 0;
	if (!(absolute_or_relative_path(command_tmp, envp, com)))
		find = find_bin_command(com->bin, from_up_to_low(command_tmp), com);
	if (find == 2)
		flag = 1;
	if (find != 2)
		check = check_type_of_file(envp, com, com->com);
	if (check == 2)
		flag = 1;
	if (!find && !check)
	{
		write_command_not_found(com);
		flag = 1;
	}
	if (flag)
	{
		free_array(com->bin);
		return (1);
	}
	free_array(com->bin);
	return (0);
}
