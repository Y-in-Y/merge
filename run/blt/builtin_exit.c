#include "minishell.h"

extern t_env	*g_env_list;

void	builtin_exit(t_all *a)
{
	if (!a)
		return ;
//	if (a->pipe_cnt == 0)
//		reset_std_fd(new_fd);
	reset_std_fd();
	printf("exit\n");
	exit(0);
}
