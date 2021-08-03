#include "minishell.h"

extern t_env	*g_env_list;

void	run_export(char	*name, char *value)
{
	t_env	*tmp;
	int		check;

	tmp = g_env_list;
	check = 0;
	while (tmp && check == 0)
	{
		check = ft_strncmp(tmp->name, name, ft_strlen(name));
		if (check == 1)
			break;
		if (!tmp->next)
			break;
		tmp = tmp->next;
	}
	if (check == 1)
	{
		free(tmp->value);
		tmp->value = ft_strdup(value);
	}
	else if (!tmp->next && check == 0)
	{
		tmp->next = (t_env *)malloc(sizeof(t_env));
		tmp = tmp->next;
		tmp->name = name;
		tmp->value = value;
		tmp->origin = NULL;
		tmp->next = NULL;
	}
	env_list_to_arr();
}

void	print_only_export(void)
{
	t_env	*env;

	env = g_env_list;
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->name, env->value);
		env = env->next;
	}
}

void	builtin_export(t_all *a)
{
	char	*check;
	char	*name;
	char	*value;
	int		i;

	if (!a)
		return ;
	if (!a->arg[1])
		print_only_export();
	else
	{
		check = a->arg[1];
		name = NULL;
		value = NULL;
		if (!check)
			error_msg("export arg missing");
		i = 0;
		while (check[i])
		{
			if (check[i] == '=')
			{
				check[i] = '\0';
				name = ft_strdup(check);
				value = ft_strdup(&check[i + 1]);
				break;
			}
			i++;
		}
		if (!name || !value)
			error_msg("export arg missing");
		run_export(name, value);
	}
}
