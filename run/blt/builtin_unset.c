#include "minishell.h"

extern t_env	*g_env_list;

void	builtin_unset(t_all *a)
{
	char	*name;
	int	check;
	t_env	*tmp;
	t_env	*unset;

	if (!a)
		return ;
	name = a->arg[1];
	tmp = g_env_list;
	check = ft_strncmp(tmp->name, name, ft_strlen(name));
	if (check == 1)
	{
		g_env_list = tmp->next;
		env_list_to_arr();
		return ;
	}
	while (tmp)
	{
		if (!tmp->next)
			break ;
		check = ft_strncmp(tmp->next->name, name, ft_strlen(name));
		if (check == 1)
			break ;
		tmp = tmp->next;
	}
	if (check == 1)
	{
		unset = tmp->next;
		tmp->next = tmp->next->next;
		free(unset);
		env_list_to_arr();
	}
}
