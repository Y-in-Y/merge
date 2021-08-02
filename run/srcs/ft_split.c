/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 09:41:48 by ylee              #+#    #+#             */
/*   Updated: 2021/06/11 15:35:18 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_word(char const *s, char c)
{
	int		idx;
	int		cnt;

	cnt = 0;
	idx = 0;
	while (s[idx])
	{
		while (s[idx] && s[idx] == c)
			idx++;
		if (s[idx] && s[idx] != c)
		{
			while (s[idx] && s[idx] != c)
				idx++;
			cnt++;
		}
	}
	return (cnt);
}

static char	*put_word(char const **s, char c, int *str_len)
{
	char	*str;

	*str_len = 0;
	while (*(*s + *str_len) && *(*s + *str_len) != c)
		*str_len = *str_len + 1;
	str = (char *)ft_calloc(*str_len + 1, sizeof(char));
	if (!str)
		return (0);
	ft_strlcpy(str, *s, *str_len + 1);
	*s = *s + *str_len;
	return (str);
}

static char	**free_all(char **result, int cnt)
{
	while (cnt >= 0)
	{
		free(result[cnt]);
		cnt--;
	}
	free(result);
	result = NULL;
	return (result);
}

char		**ft_split(char const *s, char c)
{
	char	**result;
	int		cnt;
	int		str_len;

	if (!s)
		return (0);
	cnt = count_word(s, c);
	result = (char **)ft_calloc(cnt + 1, sizeof(char *));
	if (!result)
		return (0);
	cnt = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			if (!(result[cnt++] = put_word(&s, c, &str_len)))
			{
				free_all(result, --cnt);
				return (0);
			}
		}
	}
	return (result);
}
