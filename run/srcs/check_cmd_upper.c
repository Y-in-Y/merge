/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_upper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 18:14:55 by ylee              #+#    #+#             */
/*   Updated: 2021/08/24 18:14:57 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_cmd_upper(char *cmd, int *cnt)
{
	int		i;
	int		len;
	char	*result;

	if (!cmd)
		return (0);
	len = ft_strlen(cmd);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	i = 0;
    *cnt = 0;
	while (cmd[i])
	{
		if (cmd[i] >= 'A' && cmd[i] <= 'Z')
		{
            cmd[i] = cmd[i] + 32;
            *cnt = *cnt + 1;
        }
		i++;
	}
	return (0);
}
