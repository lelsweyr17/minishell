#include "../../headers/processor.h"

void	save_pwd(t_proc *com)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (com->pwd && tmp)
		free(com->pwd);
	if (tmp)
		com->pwd = ft_strdup(tmp);
	free(tmp);
}
