/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_blt_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 19:45:04 by ylee              #+#    #+#             */
/*   Updated: 2021/08/09 19:47:33 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_blt_cmd(t_all *a)
{
	if (ft_strncmp(a->cmd, "echo", 5) == 1)
		builtin_echo(a);
	else if (ft_strncmp(a->cmd, "cd", 3) == 1)
		builtin_cd(a);
	else if (ft_strncmp(a->cmd, "pwd", 4) == 1)
		builtin_pwd(a);
	else if (ft_strncmp(a->cmd, "export", 7) == 1)
		builtin_export(a);
	else if (ft_strncmp(a->cmd, "unset", 6) == 1)
		builtin_unset(a);
	else if (ft_strncmp(a->cmd, "env", 4) == 1)
		builtin_env(a);
	else if (ft_strncmp(a->cmd, "exit", 5) == 1)
		builtin_exit(a);
	return ;
}
