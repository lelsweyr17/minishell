#include "../../headers/processor.h"

int	check_exec_file(t_proc *com, struct stat *buf, char *command)
{
	if (com->slesh)
	{
		write_error(command, NULL, "Not a directory");
		init_error(126, &com->error);
		free(buf);
		return (2);
	}
	free(buf);
	init_error(0, &com->error);
	return (1);
}

int	check_type_of_file(t_proc *com, char *command)
{
	struct stat	*buf;

	buf = (struct stat *)ft_calloc(1, sizeof(struct stat));
	lstat(com->bin_exec.path, buf);
	if (((buf->st_mode) & S_IFMT) == S_IFDIR)
		write_error(command, NULL, "is a directory");
	else if ((buf->st_mode) & S_IEXEC)
		return (check_exec_file(com, buf, command));
	else if ((buf->st_mode & S_IFMT) == S_IFREG)
		write_error(command, NULL, "Permission denied");
	else if (!check_file_in_dir(com->bin_exec.path, command, com))
	{
		free(buf);
		return (write_no_such_file_or_dir(com, command));
	}
	else
	{
		free(buf);
		init_error(0, &com->error);
		return (0);
	}
	init_error(126, &com->error);
	free(buf);
	return (2);
}

char	*tmp_command(char *command, t_proc *com)
{
	char	*command_tmp;
	int		i;

	command_tmp = command;
	i = ft_strlen(command_tmp) - 1;
	if (command_tmp[i] == '/')
	{
		com->slesh = 1;
		while (command_tmp[i] == '/')
			i--;
		command_tmp[i + 1] = 0;
	}
	command_tmp = from_up_to_low(command_tmp);
	return (command_tmp);
}

int	bin_command(t_proc *com, char **envp)
{
	int		i;
	char	*command_tmp;

	i = search_key(envp, "PATH");
	if (i != -1)
	{
		if (envp[i][4] == '=')
		{
			com->bin = ft_split(envp[i] + 5, ':');
			command_tmp = tmp_command(com->com, com);
			if (check_file_before_exec(com, command_tmp))
			{
				free(com->bin_exec.path);
				return (1);
			}
			else
				init_error(0, &com->error);
		}
	}
	else
	{
		write_command_not_found(com);
		return (1);
	}
	return (0);
}

void	execve_command(t_proc *com, char **arg, char **envp)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == 0)
	{
		envp = check_bin_minishell(com, envp);
		execve(com->bin_exec.path, arg, envp);
		if (errno)
		{
			write_error(com->com, NULL, strerror(errno));
			exit(1);
		}
		else
			init_error(0, &com->error);
	}
	else if (pid < 0)
	{
		write_error(com->com, NULL, strerror(errno));
		init_error(1, &com->error);
	}
	waitpid(pid, &com->error, WUNTRACED);
	if (com->bin_exec.path)
		free(com->bin_exec.path);
}
