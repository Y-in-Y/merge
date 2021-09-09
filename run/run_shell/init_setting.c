/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_setting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:59:53 by ylee              #+#    #+#             */
/*   Updated: 2021/09/09 11:59:54 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env_list;

void	init_setting(int *row, int *col)
{
	struct termios	term;

	g_env_list->origin_stdin = dup(0);
	g_env_list->origin_stdout = dup(1);
	signal(SIGINT, (void *)sig_handler_c);
	signal(SIGQUIT, SIG_IGN);
	tcgetattr(0, &term);
	tcgetattr(0, &(g_env_list->backup));
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	*row = 0;
	*col = 0;
}
