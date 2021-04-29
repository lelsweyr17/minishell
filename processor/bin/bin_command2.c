#include "../../headers/processor.h"

char	*skip_spaces(char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(str) - 1;
	while (str[i] <= 32)
		i++;
	while (str[len] <= 32)
		len--;
	while (i <= len)
		str[j++] = str[i++];
	str[j] = 0;
	return (str);
}

char	*relative_way_to_bin(char *line)
{
	char	*str;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	str = path_with_bin(pwd, line);
	free(pwd);
	return (str);
}

int	absolute_or_relative_path(char *line, t_proc *com)
{
	int		i;

	i = 0;
	line = skip_spaces(line);
	if (line[0] == '/')
	{
		com->bin_exec.path = ft_strdup(line);
		return (1);
	}
	else if (line[0] == '.' && line[1] == '/')
	{
		com->bin_exec.path = relative_way_to_bin(line);
		return (1);
	}
	else
		com->bin_exec.path = NULL;
	return (0);
}
