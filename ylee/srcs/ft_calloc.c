/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 10:09:31 by ylee              #+#    #+#             */
/*   Updated: 2021/06/11 15:40:41 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*result;

	i = 0;
	result = (char *)malloc(sizeof(char) * size * count);
	if (!result)
		return (0);
	while (i < (size * count))
	{
		result[i] = 0;
		i++;
	}
	return ((void *)result);
}
