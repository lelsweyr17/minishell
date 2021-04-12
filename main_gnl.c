#include "minishell.h"

char	**build_in_commands(t_command *com, char **envp)
{
	if (com->echo)
		echo_command(com, envp);
	else if (com->cd)
		envp = cd_command(com, envp);
	else if (com->pwd)
		pwd_command(com);
	else if (com->exp)
		envp = exp_command(com, envp);
	else if (com->unset)
	    envp = unset_command(com, envp);
	else if (com->env)
		env_command(envp, com);
	else if (com->exit)
	    exit_command(com);
	// else
	// 	execve_command(com, envp);
	return (envp);
}

int    ft_putchar(int c)
{
    return (write(1, &c, 1));
}

void	sign_flags(char *a, t_command *com)
{
	if (!(ft_strncmp(a, "echo", 5)))
		com->echo = 1;
	else if (!(ft_strncmp(a, "cd", 3)))
		com->cd = 1;
	else if (!(ft_strncmp(a, "pwd", 4)))
		com->pwd = 1;
	else if (!(ft_strncmp(a, "export", 7)))
		com->exp = 1;
	else if (!(ft_strncmp(a, "unset", 6)))
		com->unset = 1;
	else if (!(ft_strncmp(a, "env", 4)))
		com->env = 1;
	else if (!(ft_strncmp(a, "exit", 5)))
		com->exit = 1;
	else
	{
		com->com = ft_strdup(a);
		// write_error(a, NULL, "command not found");
		// init_error(127, &com->error);
	}
}

void	free_array(char **array)
{
	int i;

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
	int i;
	t_command	*com;
	char		*line;
	char **res;

	com = (t_command *)ft_calloc(1, sizeof(t_command));
	envp = add_oldpwd(envp);
	i = -1;
	while (write(1, "ʕ•ᴥ•ʔ -> ", 18) && (i = get_next_line(0, &line)))
	{
		if (i == -1)
			break ;
		prepare_function(com, envp, line);
		envp = build_in_commands(com, envp);
		char **arg = ft_split(line, ' ');
		if (!bin_command(com, envp) && com->com)
			execve_command(com, arg, envp);
		// free(line);
		// if (com->com)
			// free(com->com);
		if (arg)
			free_array(arg);
		// free(com->arg);
	}
	free(com);
	return (0);
}
