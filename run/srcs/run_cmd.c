/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 18:17:39 by ylee              #+#    #+#             */
/*   Updated: 2021/08/24 18:17:41 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env_list;

void	run_cmd(t_all *thispage)
{
	int		is_builtin;

	is_builtin = check_cmd(thispage->cmd);
	if (is_builtin == 0)
		run_execve_cmd(thispage);
}
