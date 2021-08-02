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
	printf("echo_n_cnt : %d, n_op : %d, i : %d\n", a->echo_n_cnt, n_op, i);
	i = 0;
	while (a->arg && a->arg[i])
	{
		printf("a->arg[%d] : %s\n", i, a->arg[i]);
		i++;
	}
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
