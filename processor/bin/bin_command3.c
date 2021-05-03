/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_command3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:38:22 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/03 20:54:21 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/processor.h"

char	*path_with_bin(char *path, char *com)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	i = -1;
	j = 0;
	len = ft_strlen(path) + ft_strlen(com) + 2;
	res = (char *)ft_calloc(len, sizeof(char));
	while (++i < (int)ft_strlen(path))
		res[i] = path[i];
	if (path[ft_strlen(path) - 1] != '/')
	{
		res[ft_strlen(path)] = '/';
		i++;
	}
	while (i < len)
		res[i++] = com[j++];
	res[i] = 0;
	return (res);
}

int	search_file_in_path(struct dirent *dir, t_proc *com, \
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

int	close_dir_if_file_is_found(int res, DIR *ptr)
{
	closedir(ptr);
	return (res);
}

int	find_bin_command(char **array, char *command, t_proc *com)
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
				if (res == 1 || res == 2)
					return (close_dir_if_file_is_found(res, ptr));
				dir = readdir(ptr);
			}
			closedir(ptr);
		}
	}
	return (0);
}

int	check_file_in_dir(char *path, char *command, t_proc *com)
{
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
			{
				closedir(ptr);
				return (1);
			}
			dir = readdir(ptr);
		}
		closedir(ptr);
	}
	return (0);
}
