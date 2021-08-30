#include "minishell.h"

extern t_env	*g_env_list;

void	change_env_value(t_env *tmp, int check, char *name, char *value)
{
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
}

void	run_export(char	*name, char *value)
{
	t_env	*tmp;
	int		check;

	if (name[0] >= '0' && name[0] <= '9')
	{
		printf("env name cannot start num\n");
		g_env_list->exit_code = 1;
		return ;
	}
	if (!value)
		return ;
	tmp = g_env_list;
	check = 0;
	while (tmp && check == 0)
	{
		check = ft_strncmp(tmp->name, name, ft_strlen(name));
		if (check == 1)
			break ;
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	change_env_value(tmp, check, name, value);
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

void	check_to_name_value(char *check, char **name, char **value)
{
	int	i;

	i = 0;
	*name = NULL;
	*value = NULL;
	while (check[i])
	{
		if (check[i] == '=')
		{
			check[i] = '\0';
			*name = ft_strdup(check);
			*value = ft_strdup(&check[i + 1]);
			break ;
		}
		i++;
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
		if (!check)
		{
			printf("export arg missing\n");
			g_env_list->exit_code = 1;
		}
		check_to_name_value(check, &name, &value);
		if (!name)
			name = ft_strdup(check);
		run_export(name, value);
	}
	if (name && (name[0] < '0' || name[0] > '9'))
		g_env_list->exit_code = 0;
}
