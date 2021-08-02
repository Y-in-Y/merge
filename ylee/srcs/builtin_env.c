#include "minishell.h"

extern t_env	*g_env_list;

void	builtin_env(t_all *a)
{
	t_env	*tmp;

	if (!a)
		return ;
	tmp = g_env_list;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}
