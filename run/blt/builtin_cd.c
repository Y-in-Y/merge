/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:57:42 by ylee              #+#    #+#             */
/*   Updated: 2021/09/09 11:57:45 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env_list;

void	go_to_home(void)
{
	char	*pwd;
	t_env	*tmp;

	tmp = g_env_list;
	pwd = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "HOME", 5) == 1)
		{
			pwd = tmp->value;
			break ;
		}
		tmp = tmp->next;
	}
	if (!pwd)
	{
		printf("cd: HOME not set\n");
		g_env_list->exit_code = 1;
		return ;
	}
	chdir(pwd);
	pwd = getcwd(NULL, 0);
	run_export("PWD", pwd);
	g_env_list->exit_code = 0;
}

void	builtin_cd(t_all *a)
{
	char	*pwd;

	if (!a)
		return ;
	pwd = getcwd(NULL, 0);
	run_export("OLDPWD", pwd);
	if (!a->arg[1])
		go_to_home();
	else
	{
		if (chdir(a->arg[1]) == -1)
		{
			printf("%s is not a directory\n", a->arg[1]);
			g_env_list->exit_code = 1;
			return ;
		}
		pwd = getcwd(NULL, 0);
		run_export("PWD", pwd);
		g_env_list->exit_code = 0;
	}
}
