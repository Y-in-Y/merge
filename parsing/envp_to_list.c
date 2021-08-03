/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 00:06:29 by ylee              #+#    #+#             */
/*   Updated: 2021/08/04 00:06:31 by ylee             ###   ########.fr       */
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
		list->exit_code = 0;
		list->name = ft_strdup(env);
		list->value = ft_strdup(&env[i + 1]);
		list->origin = NULL;
		list->next = NULL;
	}
	else
		return (0);
	return (list);
}
