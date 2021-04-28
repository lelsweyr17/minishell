#include "minishell.h"

void	pars_echo_n(t_com *com)
{
	int		a;
	int		i;
	char	**args;

	a = 1;
	com->n = 0;
	args = com->args;
	while (args[a] && args[a][0] == '-' && args[a][1] == 'n')
	{
		i = 1;
		while (args[a][i] == 'n')
			i++;
		if (args[a][i] == '\0' || args[a][i] == ' ')
		{
			com->n = 1;
			pars_shift_array(args, a);
			continue ;
		}
		else
			return ;
		a++;
	}
}

void	pars_echo(t_com *com)
{
	char	*space;
	char	**args;
	int		m;

	m = 1;
	args = com->args;
	space = ft_strdup(" ");
	pars_echo_n(com);
	while (args[m + 1])
	{
		args[1] = str_free(&args[1], ft_strjoin(args[1], space));
		args[1] = str_free(&args[1], ft_strjoin(args[1], args[m++ + 1]));
	}
	free(space);
}

/* PRINTF */
void	pars_cmp_com(t_com *com, char **commands)
{
	int		i;
	int		n;
	char	str[10];

	i = -1;
	while (com->args[0][++i] != '\0' && i < 9)
		str[i] = ft_tolower(com->args[0][i]);
	str[i] = '\0';
	n = -1;
	while (++n < 7 && com->type == 0)
		if (ft_strncmp(str, commands[n], ft_strlen(commands[n])) == 0)
			com->type = 1 << n;
	if (com->type == 0)
		com->type = 1 << n;
	// printf("\ngetcom\t_%s_\t_%d_\t_%c_%d\n", com->line, com->type, com->pipsem, i);
}

int	pars_get_com(t_com *com)
{
	char	*commands[7];

	commands[0] = "echo";
	commands[1] = "cd";
	commands[2] = "pwd";
	commands[3] = "export";
	commands[4] = "unset";
	commands[5] = "env";
	commands[6] = "exit";
	pars_cmp_com(com, commands);
	return (com->type);
}

void	pars_line(char **line, int *i)
{
	if ((*line)[*i] == '\\')
		*i += pars_shift_line(line, *i);
	else if ((*line)[*i] == '\"')
		*i = pars_find_quotes(line, '\"', *i, 1);
	else if ((*line)[*i] == '\'')
		*i = pars_find_quotes(line, '\'', *i, 1);
	else if ((*line)[*i] == '$')
		*i = pars_dollar(line, *i, *i);
	else
		*i += 1;
}
