#include "minishell.h"

int	echo_dollar(t_command *com, int i, char **envp)
{
	int		j;
	int		len;
	char	*s;

	if (com->arg[++i] == '?')
		ft_putnbr_fd(com->error, 1);
	j = -1;
	len = 0;
	while (com->arg[i + len] != ' ' && com->arg[i + len] && \
		com->arg[i + len] != '$' && com->arg[i + len] != '\n')
		len++;
	s = ft_substr(com->arg, i, len + 1);
	s[len++] = '=';
	while (envp[++j])
		if (!ft_strncmp(s, envp[j], len))
			break ;
	if (envp[j])
		write(1, envp[j] + len, ft_strlen(envp[j]) - len);
	return (i += len - 1);
}

void	echo_command(t_command *com, char **envp)
{
	int		i;
	int		j;

	i = 0;
	if (com->quote)
		write(1, com->arg, ft_strlen(com->arg));
	else
	{
		while (com->arg[i])
		{
			while (com->arg[i] && com->arg[i] != '$')
				write(1, &com->arg[i++], 1);
			if (com->arg[i] == '$')
				i = echo_dollar(com, i, envp);
		}
	}
	write(1, "\n", 1);
}

void	pwd_command(t_command *com)
{
	char	*a;

	a = NULL;
	a = getcwd(a, 0);
	write(1, a, ft_strlen(a));
	write(1, "\n", 1);
	// free(a);
}

void	cd_command(t_command *com, char **envp)
{
	chdir(com->arg);
	if (errno != 0)
	{
		write(1, "cd: ", 4);
		write(1, com->arg, ft_strlen(com->arg));
		write(1, ": ", 2);
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1);
	}
}

char	**unset_command(t_command *com, char **envp)
{
	int i = -1;
	int len;
	int num_str;

	len = array_size(envp);
	if (com->arg)
		num_str = export_equal_args(com, envp);
	if (com->arg && num_str != -1)
	{
		envp = delete_str(envp, len, com, num_str);
		export_sort(com, envp);
	}
	else
		export_sort(com, envp);
	return (envp);
}

char	**commands(t_command *com, char **envp)
{
	if (com->echo)
		echo_command(com, envp);
	else if (com->cd)
		cd_command(com, envp);
	else if (com->pwd)
		pwd_command(com);
	else if (com->exp)
		envp = exp_command(com, envp);
	else if (com->unset)
	    envp = unset_command(com, envp);
	else if (com->env)
		env_command(envp, com);
	// else if (com->exit)
	//     ...;
	return (envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_command	*com;

	com = (t_command *)ft_calloc(1, sizeof(t_command));
	// com->quote = 1;
	// com->echo = 1;
	// com->arg = "$LOGNAME  |  $LANG";
	// com->arg = "/Users/lelsweyr";
	// com->cd = 1;
	// com->exp = 1;
	// com->unset = 1;
	com->arg = "PWd=111";
	// envp = commands(com, envp);
	// com->cd = 0;
	// com->pwd = 1;
	com->exp = 0;
	// write(1, "\n", 1);
	com->env = 1;
	// com->arg = NULL;
	envp = commands(com, envp);
	return (0);
}
