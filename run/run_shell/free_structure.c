#include "minishell.h"

extern t_env	*g_env_list;

void	free_struct(t_all *a)
{
	free(a->int_line_cut);
	free(a->arg);
	free(a->redir_list);
	if (a->next)
	{
		free_struct(a->next);
		free(a->next);
	}
}
