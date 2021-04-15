#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void	close_fds(int i, int **fd, int last)
{
	int j;
	int k;

	j = -1;
	k = -1;
	while (++j < i)
	{
		if (++k < (i - 1))
			close(fd[k][0]);
		close(fd[j][1]);
	}
	if (i == last)
		close(fd[i - 1][1]);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_num;
	int		i;
	int		**fd;
	int		stdin_0;
	int		stdout_1;
	pid_t	pid[2];
	char	*com_1;
	char	*com_2;
	int		status;
	int		options;
	char	*argv1[2] = {"top", NULL};
	char	*argv2[3] = {"grep", "ps", NULL};
	
	stdin_0 = dup(0);
	stdout_1 = dup(1);
	com_1 = "/usr/bin/top";
	com_2 = "/usr/bin/grep";
	pipe_num = 1;
	i = -1;
	fd = (int **)calloc(pipe_num, sizeof(int *));
	while (++i < pipe_num)
	{
		fd[i] = (int *)calloc(2, sizeof(int));
		pipe(fd[i]);
	}
	i = -1;
	while (++i <= pipe_num)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			if (i == 0)
			{
				dup2(fd[i][1], 1);
				execve(com_1, argv1, envp);
			}
			else if (i == pipe_num)
			{
				close_fds(i, fd, pipe_num);
				dup2(fd[i - 1][0], 0);
				execve(com_2, argv2, envp);
			}
			else
			{
				close_fds(i, fd, pipe_num);
				dup2(fd[i - 1][0], 0);
				dup2(fd[i][1], 1);
				execve(com_2, argv2, envp);
			}
		}
	}
	i = -1;
	while (++i <= pipe_num)
	{
		waitpid(pid[i], &status, 0);
		if (i == 0)
			close(fd[i][1]);
		else if (i == pipe_num)
			close(fd[i - 1][0]);
		else
		{
			close(fd[i - 1][0]);
			close(fd[i][1]);
		}
	}
	return (0);
}