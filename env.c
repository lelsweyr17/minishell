#include "minishell.h"

char	*upper_case(char *a)
{
	int i;
	char *arg;

	i = -1;
	arg = (char *)ft_calloc(ft_strlen(a) + 1, sizeof(char));
	while (a[++i])
	{
		if (a[i] >= 'a' && a[i] <= 'z')
			arg[i] = a[i] - 32;
		else
			arg[i] = a[i];
	}
	return (arg);
}

void	print_env_with_tmp_arg(t_command *com, char **envp, int num_str)
{
	int i;
	int flag;
	int len;

	i = 0;
	flag = 0;
	while (com->arg[i] && com->arg[i] != '=')
		i++;
	len = i;
	i = -1;
	while (envp[++i])
	{
		if (!(ft_strncmp(envp[i], upper_case(com->arg), len + 1)))
		{
			write(1, upper_case(com->arg), ft_strlen(com->arg));
			flag = 1;
		}
		else
			write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 1);
	}
	if (!flag)
	{
		write(1, com->arg, ft_strlen(com->arg));
		write(1, "\n", 1);
	}
}

void	pwd_case(char *arg, char **envp, int num_str, t_command *com)
{
	int i;

	i = -1;
	if (arg[0] == 'P' && arg[1] == 'W' && arg[2] == 'D' && arg[3] == '=')
		print_env_with_tmp_arg(com, envp, num_str);
	else
	{
		while (envp[++i])
		{
			write(1, envp[i], ft_strlen(envp[i]));
			write(1, "\n", 1);
		}
		write(1, arg, ft_strlen(arg));
		write(1, "\n", 1);
	}

}

void	env_command(char **envp, t_command *com)
{
	int	i;
	int num_str;

	i = -1;
	if (com->arg)
	{
        if (!(ft_strrchr(com->arg, '=')) && (ft_strncmp(upper_case(com->arg), "PWD", 4)))
        {
            write(1, "env: ", 5);
            write(1, com->arg, ft_strlen(com->arg));
            write(1, ": No such file or directory\n", 28);
        }
		else if (!(ft_strncmp(upper_case(com->arg), "PWD", 4)))
			pwd_command(com);
		else if (ft_strncmp(upper_case(com->arg), "PWD", 4) && (ft_strrchr(com->arg, '=')))
			pwd_case(com->arg, envp, num_str, com);
		else
			print_env_with_tmp_arg(com, envp, num_str);
	}
	while (envp[++i] && !com->arg)
	{
		write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 1);
	}
}

char	**delete_str(char **envp, int size, t_command *com, int num_str)
{
	char **new;
	int i;
	int j;
	
	i = -1;
	j = -1;
	new = (char **)ft_calloc(size, sizeof(char *));
	while (++i < size)
		if (i != num_str)
			new[j++] = envp[i];
	j = -1;
	// free(envp);
	return (new);
}