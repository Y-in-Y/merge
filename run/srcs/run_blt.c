/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_blt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 18:17:24 by ylee              #+#    #+#             */
/*   Updated: 2021/08/24 18:17:26 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env_list;

void	reset_std_fd(void)
{
	dup2(g_env_list->origin_stdin, 0);
	dup2(g_env_list->origin_stdout, 1);
}

char	*replace_upper_cmd(char *cmd)
{
	char	*new;
	int		i;

	if (!cmd)
		return (NULL);
	i = 0;
	new = ft_strdup(cmd);
	while (new[i])
	{
		if (new[i] >= 'A' && new[i] <= 'Z')
			new[i] = new[i] + 32;
		i++;
	}
	return (new);
}

void	run_blt(t_all *a)
{
	int		cnt;
	char	*new_cmd;

	if (a->redir_list && a->redir_list->redir_flag != 0)
	{
		redir_connect(a->redir_list);
		rearrange_arg(a);
	}
	cnt = 0;
	new_cmd = replace_upper_cmd(a->cmd);
	free(a->cmd);
	a->cmd = new_cmd;
	run_blt_cmd(a);
	reset_std_fd();
}
