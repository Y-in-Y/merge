#include "minishell.h"

extern t_env	*g_env_list;

void	run_cmd(t_all *thispage)
{
	int		is_builtin;

	is_builtin = builtin_cmd_check(thispage);
//	printf("this cmd (%s) is builtin? %d \n", thispage->cmd, is_builtin);
	if (is_builtin == 0)
        run_execve_cmd(thispage);
}
