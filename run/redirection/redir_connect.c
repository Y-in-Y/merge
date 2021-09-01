/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_connect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 18:11:31 by ylee              #+#    #+#             */
/*   Updated: 2021/09/02 02:02:40 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env_list;

void	redir_in(t_list *tmp)
{
	filefd_to_stdin(tmp->file);
}

void	redir_out(t_list *tmp)
{
	filefd_to_stdout(tmp->file);
}

void	heredoc(t_list *tmp)
{
	char	*tmpfile;

	tmpfile = ft_strjoin("/tmp/.", ft_itoa(tmp->pipe_idx));
	filefd_to_stdin(tmpfile);
}

void	redir_connect(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->redir_flag == 0)
			break ;
		if (tmp->redir_flag == 1)
			redir_in(tmp);
		else if (tmp->redir_flag == 2)
			redir_out(tmp);
		else if (tmp->redir_flag == 3)
			heredoc(tmp);
		else if (tmp->redir_flag == 4)
			append_out(tmp->file);
		else
			error_msg("redir error");
		tmp = tmp->next;
	}
}
