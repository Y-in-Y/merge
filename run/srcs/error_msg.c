/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 18:17:14 by ylee              #+#    #+#             */
/*   Updated: 2021/08/24 18:17:15 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *str)
{
	if (ft_strncmp("cmd not found", str, ft_strlen(str)))
	{
		perror(str);
		exit(127);
	}
	perror(str);
	exit(1);
}
