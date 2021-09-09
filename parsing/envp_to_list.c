/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:56:39 by ylee              #+#    #+#             */
/*   Updated: 2021/09/09 11:56:42 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_env	*envp_to_list(char *env)
{
	t_env	*list;
	int		i;

	list = (t_env *)malloc(sizeof(t_env));
	if (!list)
		return (0);
	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			break ;
		i++;
	}
	if (env[i] == '=')
	{
		env[i] = '\0';
		list->name = ft_strdup(env);
		list->value = ft_strdup(&env[i + 1]);
		list->origin = NULL;
		list->next = NULL;
	}
	else
		return (0);
	return (list);
}
