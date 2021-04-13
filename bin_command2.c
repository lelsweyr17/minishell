#include "header_commands.h"

char	*skip_spaces(char *str)
{
	int i;
	int j;
	int len;

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

char	*absolute_way_to_bin(char *line)
{
	char *str;

	str = line;
	return (str);
}

char	*relative_way_to_bin(char *line)
{
	char *str;
	char *pwd;

	str = line;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	line = path_with_bin(pwd, line);
	free(str);
	free(pwd);
	return (line);
}

int	check_bin_file(char *line, char **envp, t_command *com)
{
	int i;
	char *tmp;

	i = 0;
	line = skip_spaces(line);
	if (line[0] == '/')
		com->bin_exec.path = absolute_way_to_bin(line);
	else if (line[0] == '.' && line[1] == '/')
		com->bin_exec.path = relative_way_to_bin(line);
	else
		return (1);
	return (0);
}