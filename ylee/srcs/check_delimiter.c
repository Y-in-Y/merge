/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_delimiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 19:13:03 by ylee              #+#    #+#             */
/*   Updated: 2021/06/14 23:22:27 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_delimiter(char *argv, char *str)
{
	int	i;

	i = 0;
	if (!argv || !str)
		return (0);
	while (argv[i] && str[i])
	{
		if (argv[i] == str[i])
			i++;
		else
			return (0);
	}
	if (argv[i] != '\0' || str[i] != '\0')
		return (0);
	return (1);
}
