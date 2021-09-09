/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 21:14:05 by ylee              #+#    #+#             */
/*   Updated: 2021/08/24 21:14:13 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env_list;

void	make_process(t_all *a, int cmd_cnt, int **fd, pid_t *pid)
{
	int	i;

	i = 0;
	while (i < cmd_cnt)
	{
		if (i < cmd_cnt - 1 && pipe(fd[i]) < 0)
			error_msg("pipe error");
		pid[i] = fork();
		if (pid[i] < 0)
			error_msg("fork error");
		else if (pid[i] == 0)
		{
			child_process(a, i, fd);
			exit(0);
		}
		else if (i > 0)
		{
			close(fd[i - 1][0]);
			close(fd[i - 1][1]);
		}
		i++;
	}
}

void	after_fork(int cmd_cnt, pid_t *pid, int **fd)
{
	int	i;
	int	state;

	i = 0;
	while (i < cmd_cnt)
	{
		waitpid(pid[i], &state, 0);
		i++;
	}
	i = 0;
	while (i < cmd_cnt)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
	free(pid);
	if (WIFEXITED(state))
		g_env_list->exit_code = WEXITSTATUS(state);
	else if (WIFSIGNALED(state))
		g_env_list->exit_code = WTERMSIG(state) + 128;
	else
		g_env_list->exit_code = 0;
	exit(g_env_list->exit_code);
}

void	multipipe(t_all *a)
{
	int		cmd_cnt;
	pid_t	*pid;
	int		**fd;
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
	make_process(a, cmd_cnt, fd, pid);
	after_fork(cmd_cnt, pid, fd);
}
