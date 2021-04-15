#include "header_commands.h"

char	*path_with_bin(char *path, char *com)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	i = -1;
	j = 0;
	len = ft_strlen(path) + 1 + ft_strlen(com) + 1;
	res = (char *)ft_calloc(len, sizeof(char));
	res[ft_strlen(path)] = '/';
	while (++i < ft_strlen(path))
		res[i] = path[i];
	while (i++ < len)
		res[i] = com[j++];
	return (res);
}

int	find_bin_command(char **array, char *command, t_command *com)
{
	int				start;
	int				i;
	DIR				*ptr;
	struct dirent	*dir;

	i = -1;
	com->bin_exec.path = "1";
	while (array[++i])
	{
		ptr = opendir(array[i]);
		if (ptr)
		{
			dir = readdir(ptr);
			while (dir)
			{
				if (!(ft_strncmp(dir->d_name, command, ft_strlen(command) + 1)))
				{
					com->bin_exec.path = path_with_bin(array[i], command);
					return (1);
				}
				dir = readdir(ptr);
			}
			closedir(ptr);
		}
	}
	return (0);
}

char	*from_up_to_low(char *arg)
{
	int i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i]>= 'A' && arg[i] <= 'Z')
			arg[i] += 32;
	}
	return (arg);
}

int	bin_command(t_command *com, char **envp)
{
	int		i;
	int		j;
	char	*arg;

	i = search_key(envp, "PATH");
	if (i != -1)
	{
		if (envp[i][4] == '=')
		{
			com->bin = ft_split(envp[i] + 5, ':');		// move from PATH="/...." to "/...."
			// printf("%d\n", find_bin_command(com->bin, from_up_to_low(com->com), com));
			// printf("%d\n", check_bin_file(from_up_to_low(com->com), envp, com));
			if (!find_bin_command(com->bin, from_up_to_low(com->com), com) && \
			(check_bin_file(from_up_to_low(com->com), envp, com) == 1))
			{
				write_error(com->com, NULL, "command not found");
				init_error(127, &com->error);
				free_array(com->bin);
				return (1);
			}
			else if (check_bin_file(from_up_to_low(com->com), envp, com) == 2)
			{
				write_error(com->com, NULL, "No such file or directory");
				init_error(127, &com->error);
				free_array(com->bin);
				return (1);
			}
			else
				init_error(0, &com->error);
			free_array(com->bin);
		}
	}
	else
	{
		write_error(com->com, NULL, "command not found");
		init_error(127, &com->error);
		return (1);
	}
	return (0);
}

void	execve_command(t_command *com, char **arg, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
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
	wait(&pid);
	if (com->bin_exec.path)
		free(com->bin_exec.path);
}
