#include "minishell.h"

extern t_env	*g_env_list;

void	builtin_exit(t_all *a)
{
	int		exit_arg;

	if (!a)
		return ;
//	if (a->pipe_cnt == 0)
//		reset_std_fd(new_fd);
	exit_arg = 0;
	reset_std_fd();
	printf("exit\n");
	if (!a->arg[1])
		exit(exit_arg);
	if (a->arg[1] && a->arg[2])
	{
		printf("exit: too many arguments\n");
		g_env_list->exit_code = 1;
		return ;
	}
	else if (a->arg[1] && !a->arg[2])
	{
		exit_arg = ft_atoi(a->arg[1]);
		if (exit_arg == -1)
		{
			printf("exit: %s: numeric argument required\n", a->arg[1]);
			exit(255);
		}
		exit(exit_arg);
	}
}
