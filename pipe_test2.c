#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void	close_fds(int i, int **fd, int last)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		if (j < (i - 1))
			close(fd[j][0]);
		close(fd[j][1]);
	}
	while (++j <= last)
	{
		if (j == last)
			close(fd[j - 1][0]);
		else
		{
			close(fd[j - 1][0]);
			close(fd[j][1]);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_num;
	int		i;
	int		**fd;
	int		stdin_0;
	int		stdout_1;
	int		*pid;
	char	*com_1;
	char	*com_2;
	char	*com_3;
	int		status;
	int		options;
	char	*argv1[3] = {"ls", "-la", NULL};
	char	*argv2[2] = {"cat", NULL};
	char	*argv3[3] = {"grep", "pipe_test2.c", NULL};
	
	stdin_0 = dup(0);
	stdout_1 = dup(1);
	com_1 = "/bin/ls";
	com_2 = "/bin/cat";
	com_3 = "/usr/bin/grep";
	pipe_num = 2;
	i = -1;
	fd = (int **)calloc(pipe_num + 1, sizeof(int *));
	pid = (int *)calloc(pipe_num + 1, sizeof(int));
	while (++i < pipe_num)
	{
		fd[i] = (int *)calloc(2, sizeof(int));
		pipe(fd[i]);
	}
	fd[i] = NULL;
	i = -1;
	while (++i <= pipe_num)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			if (i == 0)
			{
				close_fds(i, fd, pipe_num);
				dup2(fd[i][1], 1);
				execve(com_1, argv1, envp);
			}
			else if (i == pipe_num)
			{
				close_fds(i, fd, pipe_num);
				dup2(fd[i - 1][0], 0);
				execve(com_3, argv3, envp);
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
		waitpid(pid[i], NULL, 0);
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
	i = -1;
	while (++i <= pipe_num)
		free(fd[i]);
	free(fd);
	free(pid);
	dup2(stdin_0, 0);
	dup2(stdout_1, 1);
	return (0);
}