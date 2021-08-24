#include "minishell.h"

extern t_env	*g_env_list;

void	builtin_echo(t_all *a)
{
	int		i;
	int		n_op;

	if (!a)
		return ;
	i = 0;
    n_op = a->echo_n_cnt;
	i = n_op + 1;
    while (a->arg[i])
	{
		printf("%s", a->arg[i]);
		if (a->arg[i + 1])
			printf(" ");
		i++;
	}
	if (n_op == 0)
		printf("\n");
}
