/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 09:41:48 by ylee              #+#    #+#             */
/*   Updated: 2021/08/06 01:29:02 by ylee             ###   ########.fr       */
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
	str = (char *)malloc(sizeof(char) * (*str_len + 1));
	if (!str)
		return (0);
	str[*str_len] = '\0';
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

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		cnt;
	int		str_len;

	if (!s)
		return (0);
	cnt = count_word(s, c);
	result = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!result)
		return (0);
	result[cnt] = NULL;
	cnt = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			result[cnt] = put_word(&s, c, &str_len);
			if (!result[cnt])
				return (free_all(result, cnt));
			cnt++;
		}
	}
	return (result);
}
