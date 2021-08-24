/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 18:17:46 by ylee              #+#    #+#             */
/*   Updated: 2021/08/24 18:17:48 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env    *g_env_list;

char    **path_dir(void)
{
	char    *path;
	char    **dir;
	int     i;

	path = find_env_value("PATH");
	if (!path)
		error_msg("cannot find PATH env");
	dir = ft_split(path, ':');
	if (!dir)
		error_msg("cannot split path");
	return (dir);
}

void	run_execve_cmd(t_all *a)
{
	char    **dir;
	char    *tmp;
	char    *cmd;

	dir = path_dir();
	if (a->redir_list && a->redir_list->redir_flag != 0)
	{
		redir_connect(a->redir_list);
        rearrange_arg(a);
	}
	while (dir && *dir)
	{
		tmp = ft_strjoin(*dir, "/");
		cmd = ft_strjoin(tmp, a->cmd);
		free(tmp);
		execve(cmd, a->arg, g_env_list->origin);
		free(cmd);
		dir++;
	}
	execve(a->cmd, a->arg, g_env_list->origin);
	error_msg("cmd not found");
}
