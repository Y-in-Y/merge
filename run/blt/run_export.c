/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 01:04:54 by ylee              #+#    #+#             */
/*   Updated: 2021/09/02 01:51:34 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env_list;

void	change_env_value(t_env *tmp, int check, char *name, char *value)
{
	if (check == 1)
	{
		free(tmp->value);
		tmp->value = ft_strdup(value);
	}
	else if (!tmp->next && check == 0)
	{
		tmp->next = (t_env *)malloc(sizeof(t_env));
		tmp = tmp->next;
		tmp->name = name;
		tmp->value = value;
		tmp->origin = NULL;
		tmp->next = NULL;
	}
}

void	run_export(char	*name, char *value)
{
	t_env	*tmp;
	int		check;

	if (!value)
		return ;
	tmp = g_env_list;
	check = 0;
	while (tmp && check == 0)
	{
		check = ft_strncmp(tmp->name, name, ft_strlen(name));
		if (check == 1)
			break ;
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	change_env_value(tmp, check, name, value);
	env_list_to_arr();
}
