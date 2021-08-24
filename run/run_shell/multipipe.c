#include "minishell.h"

extern t_env	*g_env_list;

void	multipipe(t_all *a)
{
	int		cmd_cnt;
	pid_t	*pid;
	int		**fd;
	int		state;
	int		i;

	cmd_cnt = a->pipe_cnt + 1;
	pid = (pid_t *)malloc(sizeof(pid_t) * cmd_cnt);
	fd = (int **)malloc(sizeof(int *) * cmd_cnt);
	i = 0;
	while (i < cmd_cnt)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	i = 0;
	if (pipe(fd[i]) < 0)
		error_msg("pipe error");
	pid[i] = fork();
	if (pid[i] < 0)
		error_msg("fork error");
	if (i == 0 && pid[i] == 0)
		child_process(a, i, fd); //first cmd
	else
	{
		i = 1;
		while (i < cmd_cnt - 1)
		{
			if (pipe(fd[i]) < 0)
				error_msg("pipe error");
			pid[i] = fork();
			if (pid[i] < 0)
				error_msg("fork error");
			if (pid[i] == 0)
				break ;
			close(fd[i - 1][0]);
			close(fd[i - 1][1]);
			i++;
		}
		if (i < cmd_cnt - 1 && pid[i] == 0)
			child_process(a, i, fd); // 2 ~ (last - 1) cmd
		else
		{
			if (i != cmd_cnt - 1)
				error_msg("unknown error check multipipe");
			pid[i] = fork();
			if (pid[i] < 0)
				error_msg("fork error");
			if (pid[i] == 0)
				child_process(a, i, fd); // last cmd
			else
			{
				close(fd[i - 1][0]);
				close(fd[i - 1][1]);
				i = 0;
				while (i < cmd_cnt)
				{
					waitpid(pid[i], &state, 0);
					i++;
				}
			}
		}
	}
	i = 0;
	while (i < cmd_cnt)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
	free(pid);
}
