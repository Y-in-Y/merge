#include "minishell.h"

extern t_env	*g_env_list;

/*
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

*/

void	reset_std_fd(void)
{
	dup2(g_env_list->origin_stdin, 0);
	dup2(g_env_list->origin_stdout, 1);
}
char	*replace_upper_cmd(char *cmd)
{
	char	*new;
	int	i;

	if (!cmd)
		return (NULL);
	i = 0;
	new = ft_strdup(cmd);
	while (new[i])
	{
		if (new[i] >= 'A' && new[i] <= 'Z')
			new[i] = new[i] + 32;
		i++;
	}
	return (new);
}

void	run_blt(t_all *a)
{
//	int	new_std[2];
	int	cnt;
	char	*new_cmd;

//	new_std[0] = 0;
//	new_std[1] = 1;
//	if (a->pipe_cnt == 0)
//		new_std_fd(&new_std[0]);
	if (a->redir_list && a->redir_list->redir_flag != 0)
	{
		redir_connect(a->redir_list);
        rearrange_arg(a);
	}
	cnt = 0;
	new_cmd = replace_upper_cmd(a->cmd);
	free(a->cmd);
	a->cmd = new_cmd;
	run_blt_cmd(a);
/*
	if (a->pipe_cnt != 0 && is_blt <= 0)
		exit(1);
	else if (a->pipe_cnt != 0 && is_blt == 1)
		exit(0);
	else
*/
	reset_std_fd();
//	reset_std_fd(&new_std[0]);
//	error case 추가해야함
}
