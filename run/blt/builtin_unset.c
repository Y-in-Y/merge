/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:58:21 by ylee              #+#    #+#             */
/*   Updated: 2021/09/09 11:58:22 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env_list;

void	unset_first_list(void)
{
	t_env	*tmp;
	t_env	*unset;

	tmp = g_env_list;
	unset = tmp->next;
	free(tmp->name);
	free(tmp->value);
	tmp->name = unset->name;
	tmp->value = unset->value;
	tmp->next = unset->next;
	free(unset);
	env_list_to_arr();
}

void	run_unset(int check, char *name)
{
	t_env	*tmp;
	t_env	*unset;

	tmp = g_env_list;
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
		free(unset->name);
		free(unset->value);
		free(unset);
		env_list_to_arr();
	}
}

void	builtin_unset(t_all *a)
{
	char	*name;
	int		check;
	t_env	*tmp;

	if (!a)
		return ;
	name = a->arg[1];
	tmp = g_env_list;
	if (!name)
	{
		g_env_list->exit_code = 0;
		return ;
	}
	if (name[0] >= '0' && name[0] <= '9')
	{
		printf("env name cannot start num\n");
		g_env_list->exit_code = 1;
		return ;
	}
	check = ft_strncmp(tmp->name, name, ft_strlen(name));
	if (check == 1)
		unset_first_list();
	else
		run_unset(check, name);
	g_env_list->exit_code = 0;
}
