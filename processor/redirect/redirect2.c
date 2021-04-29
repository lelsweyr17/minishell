#include "../../headers/processor.h"

void	redirect_pipe_condition(char **env, char **arg, t_proc *com, \
	t_com *list)
{
	if (list->re)
		redirect_operator(com, env, list);
	else
		pipe_command(env, list->args, com, list);
}
