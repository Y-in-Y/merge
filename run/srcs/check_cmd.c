/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 14:26:56 by ylee              #+#    #+#             */
/*   Updated: 2021/08/24 18:14:48 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export_unset(int cnt)
{
	if (cnt == 0)
		return (1);
	else
	{
		printf("command not found\n");
		return (-1);
	}
	return (0);
}

int	is_cmd_blt(char *cmd, int cnt)
{
	int	ret;

	ret = -1;
	if (ft_strncmp(cmd, "echo", 5) == 1)
		ret = 1;
	else if (ft_strncmp(cmd, "cd", 3) == 1)
		ret = 1;
	else if (ft_strncmp(cmd, "pwd", 4) == 1)
		ret = 1;
	else if (ft_strncmp(cmd, "export", 7) == 1)
		return (check_export_unset(cnt));
	else if (ft_strncmp(cmd, "unset", 6) == 1)
		return (check_export_unset(cnt));
	else if (ft_strncmp(cmd, "env", 4) == 1)
		ret = 1;
	else if (ft_strncmp(cmd, "exit", 5) == 1)
		ret = 1;
	else
		ret = 0;
	return (ret);
}

int	check_cmd(t_all *a)
{
	char	*for_check;
	int		ret;
	int		i;
	int		cnt;

	if (!a || (a->pipe_cnt == 0 && !a->cmd))
		return (-1);
	if (!a->cmd && a->pipe_cnt != 0)
		return (0);
	for_check = ft_strdup(a->cmd);
	if (!for_check)
		return (-1);
	i = -1;
	cnt = 0;
	while (for_check[++i])
	{
		if (for_check[i] >= 'A' && for_check[i] <= 'Z')
		{
			for_check[i] = for_check[i] + 32;
			cnt++;
		}
	}
	ret = is_cmd_blt(for_check, cnt);
	free(for_check);
	return (ret);
}
