#include "../../headers/processor.h"

void	cd_errno(t_proc *com)
{
	write_error("cd", com->arg, strerror(errno));
	init_error(1, &com->error);
}

void	cd_with_arg(t_proc *com)
{
	chdir(com->arg);
	init_error(0, &com->error);
}

void	cd_in_current_dir(t_proc *com, int *flag)
{
	*flag = 1;
	init_error(0, &com->error);
}
