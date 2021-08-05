#include "minishell.h"

extern t_env	*g_env_list;

void	only_pipe(t_all *a, int i, int **fd)
{
	if (!a || i < 0 || !fd)
		exit(0);
	if (i > 0)
		pipefd_to_stdin(fd[i - 1]);
	if (i < a->pipe_cnt)
		pipefd_to_stdout(fd[i]);
}

void	child_process(t_all *a, int i, int **fd)
{
	t_all	*thispage;
	t_list	*tmp;
	int		check;
	int		j;

	j = 0;
	thispage = a;
	while (j < i)
	{
		thispage = thispage->next;
		j++;
	}
	thispage->pipe_cnt = 1;
	tmp = thispage->redir_list;
	if (tmp && tmp->redir_flag != 0)
        rearrange_arg(thispage);
	only_pipe(a, i, fd);
	check = check_blt_func(thispage->cmd);
	if (check == 1)
		run_blt(thispage);
	else if (check == 0)
		run_execve_cmd(thispage);
}
