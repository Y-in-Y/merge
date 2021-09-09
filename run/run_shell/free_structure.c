/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:59:48 by ylee              #+#    #+#             */
/*   Updated: 2021/09/09 11:59:50 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
