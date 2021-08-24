/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_blt_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 18:16:46 by ylee              #+#    #+#             */
/*   Updated: 2021/08/24 18:16:48 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_blt_func(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 1)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 1)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 4) == 1)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 1)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 1)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 1)
		return (1);
	else if (ft_strncmp(cmd, "exit", 5) == 1)
		return (1);
	return (0);
}
