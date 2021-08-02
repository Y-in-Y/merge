#include "minishell.h"

void	new_std_fd(int *new_fd)
{
	new_fd[0] = dup(0);
	new_fd[1] = dup(1);
}

void	reset_std_fd(int *new_fd)
{
	dup2(new_fd[0], 0);
	dup2(new_fd[1], 1);
	close(new_fd[0]);
	close(new_fd[1]);
}

void	run_blt(t_all *a)
{
	int	new_std[2];
	int	cnt;
	int	is_blt;

	new_std[0] = 0;
	new_std[1] = 1;
	if (a->pipe_cnt == 0)
	{
		new_std_fd(&new_std[0]);
//		printf("new std fd : %d, %d\n", new_std[0], new_std[1]);
	}
	if (a->redir_list && a->redir_list->redir_flag != 0)
	{
		redir_connect(a->redir_list);
        rearrange_arg(a);
	}
	cnt = 0;
//	printf("old cmd : %s, cnt : %d\n", a->cmd, cnt);
	check_cmd_upper(a->cmd, &cnt);
//	printf("new cmd : %s, cnt : %d\n", a->cmd, cnt);
	is_blt = check_cmd(a, cnt, &new_std[0]);
	if (a->pipe_cnt != 0 && is_blt <= 0)
		exit(1);
	else if (a->pipe_cnt != 0 && is_blt == 1)
		exit(0);
	else
		reset_std_fd(&new_std[0]);
}
