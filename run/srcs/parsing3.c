/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:11:14 by inyang            #+#    #+#             */
/*   Updated: 2021/07/07 06:13:22 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing(char *line, t_all *start)
{
/*
	int		pipe_cnt;
	char	*line_cut;
	int		*int_line_cut;
	char	**argv;
	char	*cmd;
	t_list	*redir_list;
*/
	t_all	*a;
	t_all	*b;
	char	*tmp;
	int		i;

	if (!line || !start)
		return (0);

//case 1
//echo “test $PWD ‘$PWD’ cat | ls -al” | cat << ylee
	a = (t_all *)malloc(sizeof(t_all));
	if (!a)
		return (0);
	b = (t_all *)malloc(sizeof(t_all));
	if (!b)
		return (0);
	a->pipe_cnt = 1;
	a->line_cut = "echo \"test $PWD \'$PWD\' cat | ls -al\"";
	tmp = "00002311111555511555511111111111113";
	i = 0;
	while (tmp[i])
		i++;
	a->int_line_cut = (int *)malloc(sizeof(int) * i);
	i = 0;
	while (tmp[i])
	{
		a->int_line_cut[i] = tmp[i] - '0';
		i++;
	}
	a->argv = (char **)malloc(sizeof(char *) * 3);
	a->argv[0] = "echo";
	a->argv[1] = "\"test $PWD \'$PWD\' cat | ls -al\"";
	a->argv[2] = NULL;
	a->cmd = "echo";
	a->redir_list = NULL;
	a->next = b;

	b->pipe_cnt = 0;
	b->line_cut = "cat << ylee";
	tmp = "00026666666";
	i = 0;
	while (tmp[i])
		i++;
	b->int_line_cut = (int *)malloc(sizeof(int) * i);
	i = 0;
	while (tmp[i])
	{
		b->int_line_cut[i] = tmp[i] - '0';
		i++;
	}
	b->argv = (char **)malloc(sizeof(char *) * 2);
	b->argv[0] = "cat";
	b->argv[1] = NULL;
	b->cmd = "cat";
	b->redir_list = (t_list *)malloc(sizeof(t_list));
	b->redir_list->redir_flag = 3;
	b->redir_list->file = "ylee";
	b->redir_list->next = NULL;
	b->next = NULL;
	*start = *a;
	free(a);
	return (1);
}
