/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:11:14 by inyang            #+#    #+#             */
/*   Updated: 2021/08/23 22:10:26 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_env	*g_env_list;

int	line_to_changed(char *line, int *changed, int i)
{
	while (line[++i])
	{
		if ((line[i] >= 'a' && line[i] <= 'z') || \
		(line[i] >= 'A' && line[i] <= 'Z'))
			changed[i] = 0;
		else if (line[i] == ' ' || line[i] == '\t')
			changed[i] = 2;
		else if (line[i] == '\"')
			i = d_quote(line, changed, i);
		else if (line[i] == '\'')
			i = s_quote(line, changed, i);
		else if (line[i] == '$')
			i = env_name(line, changed, i);
		else if (line[i] == '<' || line[i] == '>')
			i = redir_name(line, changed, i);
		else if (line[i] == '|')
			changed[i] = 8;
		else
			changed[i] = 9;
		if (i < 0)
			return (i);
	}
	return (0);
}

void	parsing(char *line, t_all *a)
{
	int		i;
	int		*changed;
	int		length;
	char	*new_line;

	length = px_strlen(line);
	changed = (int *)malloc(sizeof(int) * length);
	i = 0;
	while (i < length)
		changed[i++] = 1111111;
	struct_init(a);
	i = line_to_changed(line, changed, -1);
	if (i < 0)
		return ;
	i = 0;
	while (line[i])
	{
		if (changed[i] == 1111111)
			return ;
		i++;
	}
	new_line = cutting_int_line(line, &changed, a);
	changed_line_cut(changed, a);
	check_arguments(a);
	is_cmd_echo(a);
}
