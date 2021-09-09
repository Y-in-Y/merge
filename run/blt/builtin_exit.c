/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:57:59 by ylee              #+#    #+#             */
/*   Updated: 2021/09/09 11:58:01 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env_list;

void	builtin_exit(t_all *a)
{
	int		exit_arg;

	if (!a)
		return ;
	exit_arg = 0;
	reset_std_fd();
	printf("exit\n");
	if (!a->arg[1])
		exit(exit_arg);
	if (a->arg[1] && a->arg[2])
	{
		printf("exit: too many arguments\n");
		g_env_list->exit_code = 1;
		return ;
	}
	else if (a->arg[1] && !a->arg[2])
	{
		exit_arg = ft_atoi(a->arg[1]);
		if (exit_arg == -1)
		{
			printf("exit: %s: numeric argument required\n", a->arg[1]);
			exit(255);
		}
		exit(exit_arg);
	}
}
