#include "header_commands.h"

char	**build_in_commands(t_command *com, char **envp, char **arg)
{
	if (!(ft_strncmp(arg[0], "echo", 5)))
		echo_command(com, envp);
	else if (!(ft_strncmp(arg[0], "cd", 3)))
		envp = cd_command(com, envp);
	else if (!(ft_strncmp(arg[0], "pwd", 4)))
		pwd_command(com);
	else if (!(ft_strncmp(arg[0], "export", 7)))
		envp = exp_command(com, envp, arg + 1);
	else if (!(ft_strncmp(arg[0], "unset", 6)))
		envp = unset_command(com, envp, arg + 1);
	else if (!(ft_strncmp(arg[0], "env", 4)))
		env_command(envp, com);
	else if (!(ft_strncmp(arg[0], "exit", 5)))
		exit_command(com);
	else
		com->com = ft_strdup(arg[0]);
	return (envp);
}

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	if (array)
	{
		while (array[++i])
			free(array[i]);
		free(array);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int			i;
	t_command	*com;
	char		*line;
	char		**res;
	char		**arg;

	com = (t_command *)ft_calloc(1, sizeof(t_command));
	envp = add_oldpwd(envp);
	i = -1;
	while (write(1, "ʕ•ᴥ•ʔ -> ", 18) && (i = get_next_line(0, &line)))
	{
		if (i == -1)
			break ;
		arg = ft_split(line, ' ');
		prepare_function(com, envp, arg);
		envp = build_in_commands(com, envp, arg);
		if (com->com && !bin_command(com, envp))
			execve_command(com, arg, envp);
		line = NULL;
		free(line);
		// if (com->com)
		// 	free(com->com);
		// if (arg)
		// 	free_array(arg);
		// free(com->arg);
	}
	free(com);
	return (0);
}
