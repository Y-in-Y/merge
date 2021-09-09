/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:58:15 by ylee              #+#    #+#             */
/*   Updated: 2021/09/09 11:58:16 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env_list;

void	builtin_pwd(t_all *a)
{
	char	*pwd;

	if (!a)
		return ;
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	g_env_list->exit_code = 0;
}
