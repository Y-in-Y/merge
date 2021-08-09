/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 14:26:56 by ylee              #+#    #+#             */
/*   Updated: 2021/08/09 14:27:06 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_upper_cmd(char *cmd)
{
	int		i;

	i = 0;
//	printf("before cmd : %s\n", cmd);
	while (cmd[i])
	{
		if (cmd[i] >= 'A' && cmd[i] <= 'Z')
			*(&cmd[i]) = cmd[i] + 32;
		i++;
	}
//	printf("after cmd : %s\n", cmd);
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
    {
        if (cnt == 0)
			ret = 1;
        else
        {
            printf("command not found\n");
            ret = -1;
        }
    }
	else if (ft_strncmp(cmd, "unset", 6) == 1)
    {
        if (cnt == 0)
			ret = 1;
        else
        {
            printf("command not found\n");
            ret = -1;
        }
	}
    else if (ft_strncmp(cmd, "env", 4) == 1)
		ret = 1;
	else if (ft_strncmp(cmd, "exit", 5) == 1)
		ret = 1;
	else
		ret = 0;
	if (ret == 0)
		replace_upper_cmd(cmd);
	return (ret);
}

int	check_cmd(char *cmd)
{
	char	*for_check;
	int		ret;
	int		i;
	int		cnt;

	if (!cmd)
		return (-1);
	for_check = ft_strdup(cmd);
	if (!for_check)
		return (-1);
	i = 0;
	cnt = 0;
	while (for_check[i])
	{
		if (for_check[i] >= 'A' && for_check[i] <= 'Z')
		{
			for_check[i] = for_check[i] + 32;
			cnt++;
		}
		i++;
	}
	ret = is_cmd_blt(for_check, cnt);
	free(for_check);
	return (ret);
}
