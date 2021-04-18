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

int	search_file_in_path(struct dirent *dir, t_command *com, \
	char *str, char *command)
{
	if (!(ft_strncmp(dir->d_name, command, ft_strlen(command) + 1)))
	{
		com->bin_exec.path = path_with_bin(str, command);
		if (com->slesh)
		{
			write_error(command, NULL, "Not a directory");
			init_error(126, &com->error);
			return (2);
		}
		return (1);
	}
	return (0);
}

int	find_bin_command(char **array, char *command, t_command *com)
{
	int				res;
	int				i;
	DIR				*ptr;
	struct dirent	*dir;

	i = -1;
	while (array[++i])
	{
		ptr = opendir(array[i]);
		if (ptr)
		{
			dir = readdir(ptr);
			while (dir)
			{
				res = search_file_in_path(dir, com, array[i], command);
				if (res == 1)
					return (1);
				if (res == 2)
					return (2);
				dir = readdir(ptr);
			}
			closedir(ptr);
		}
	}
	return (0);
}

char	*from_up_to_low(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] >= 'A' && arg[i] <= 'Z')
			arg[i] += 32;
	}
	return (arg);
}

int	check_file_in_dir(char *path, char *command, t_command *com)
{
	int				i;
	DIR				*ptr;
	struct dirent	*dir;

	if (!com->bin_exec.path)
		return (1);
	ptr = opendir(path);
	if (ptr)
	{
		dir = readdir(ptr);
		while (dir)
		{
			if (!(ft_strncmp(dir->d_name, command, ft_strlen(command) + 1)))
				return (1);
			dir = readdir(ptr);
		}
		closedir(ptr);
	}
	return (0);
}
