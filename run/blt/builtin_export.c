/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 00:09:50 by ylee              #+#    #+#             */
/*   Updated: 2021/09/02 02:00:17 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env_list;

void	print_only_export(void)
{
	t_env	*env;

	env = g_env_list;
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->name, env->value);
		env = env->next;
	}
	g_env_list->exit_code = 0;
}

void	arg_to_name_value(char *arg, char **name, char **value)
{
	int	i;

	i = 0;
	*name = NULL;
	*value = NULL;
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			arg[i] = '\0';
			*name = ft_strdup(arg);
			*value = ft_strdup(&arg[i + 1]);
			arg[i] = '=';
			break ;
		}
		i++;
	}
	if (!*name)
		*name = ft_strdup(arg);
}

void	check_name(char **arg)
{
	int		i;
	int		check;
	char	*name;

	i = 1;
	check = 0;
	name = *arg;
	if (!ft_isalpha(name[0]) && name[0] != '_')
		check = 1;
	while (check == 0 && name[i])
	{
		if (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) && name[i] != '_')
			check = 1;
		else
			i++;
	}
	if (check == 0)
		return ;
	free(*arg);
	*arg = NULL;
	g_env_list->exit_code = 1;
}

void	builtin_export(t_all *a)
{
	char	*arg;
	char	*name;
	char	*value;

	if (!a)
		return ;
	if (!a->arg[1])
		print_only_export();
	else
	{
		arg = a->arg[1];
		arg_to_name_value(arg, &name, &value);
		check_name(&name);
		if (!name)
		{
			printf("export: `%s\': not a valid identifier\n", a->arg[1]);
			return ;
		}
		run_export(name, value);
		g_env_list->exit_code = 0;
	}
}
