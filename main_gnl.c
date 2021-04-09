#include "minishell.h"

int		ft_is_number(char *a)
{
	int i;
	int res;
	int count;

	i = -1;
	res = 0;
	count = 1;
	while (a[++i])
	{
		if (ft_isdigit(a[i]))
		{
			res = res * count + (a[i] - '0');
			count = 10;
		}
		else
			return (-1);
	}
	return (res);
}

void	exit_command(t_command *com)
{
	int i;
	int res;

	i = -1;
	if (!com->arg)
	{
		write(1, "exit\n", 5);
		exit(errno);
	}
	else if (com->arg && ft_strrchr(com->arg, ' '))
	{
		write (1, "exit: too many arguments\n", 25);
	}
	else
	{
		res = ft_is_number(com->arg);
		if (res != -1)
		{
			write(1, "exit\n", 5);
			printf("%d\n", res);
			exit(res % 256);
		}
		else
		{
			write(1, "exit: ", 7);
			write(1, com->arg, ft_strlen(com->arg));
			write(1, ": numeric argument required\n", 28);
			exit(255);
		}
	}
}

char	**commands(t_command *com, char **envp)
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
		write(1, a, ft_strlen(a));
		write(1, ": command not found\n", 20);
	}
}

void	null_flags(t_command *com)
{
	com->echo = 0;
	com->echo_n = 0;
	com->cd = 0;
	com->pwd = 0;
	com->env = 0;
	com->exp = 0;
	com->unset = 0;
	com->error = 0;
	com->exit = 0;
	com->no_quotes = 0;
	com->arg = 0;
	com->double_quotes = 0;
	com->quote = 0;
	com->arg = 0;
}

char	*arg_res(char **res, t_command *com)
{
	int i;
	char *arg;

	i = 0;
	arg = (char *)ft_calloc(1, sizeof(char));
	arg[0] = 0;
	if (com->echo_n)
		i++;
	while (res[++i])
	{
		arg = ft_strjoin(arg, res[i]);
		if (res[i + 1])
			arg = ft_strjoin(arg, " ");
	}
	if (!ft_strlen(arg))
	{
		free(arg);
		arg = NULL;
	}
	return (arg);
}

char	**add_oldpwd(char **envp)
{
	int i;
	int size;
	char **tmp;

	i = -1;
	size = array_size(envp);
	tmp = envp;
	envp = (char **)ft_calloc(size + 1, sizeof(char *));
	envp[size] = NULL;
	while (tmp[++i])
		envp[i] = tmp[i];
	envp[i] = "OLDPWD";
	return (envp);
}

void	com_export(t_command *com, char **envp)
{
	int len;
	int i;

	i = -1;
	len = array_size(envp);
	com->ex_port = (char **)ft_calloc(len + 1, sizeof(char *));
	com->ex_port[len] = NULL;
	while (++i < len)
		com->ex_port[i] = envp[i];
}

int	main(int argc, char **argv, char **envp)
{
	int i;
	int j;
	t_command	*com;
	char		*line;
	char **res;
	int len;

	com = (t_command *)ft_calloc(1, sizeof(t_command));
	envp = add_oldpwd(envp);
	j = -1;
	i = -1;
	write(1, "ʕ•ᴥ•ʔ -> ", 18);
	while ((i = get_next_line(0, &line)))
	{
		null_flags(com);
		com_export(com, envp);
		if (i == -1)
			break ;
		res = ft_split(line, ' ');
		sign_flags(res[0], com);
		if (res && res[1] && !(ft_strncmp(res[1], "-n", 3)))
			com->echo_n = 1;
		com->arg = arg_res(res, com);
		envp = commands(com, envp);
		free(line);
		free(com->ex_port);
		write(1, "ʕ•ᴥ•ʔ -> ", 18);
	}
	free(com);
	return (0);
}
