/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 19:13:03 by ylee              #+#    #+#             */
/*   Updated: 2021/06/11 15:57:19 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *str1, char *str2)
{
	int		len1;
	int		len2;
	int		i;
	char	*result;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	result[len1 + len2] = '\0';
	i = 0;
	while (i < len1)
	{
		result[i] = str1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		result[len1 + i] = str2[i];
		i++;
	}
	return (result);
}
