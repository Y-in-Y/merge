#include "minishell.h"

extern t_env	*g_env_list;

int		ft_strcpy(char *origin, char *txt)
{
	int		i;

	i = 0;
	while (txt[i])
	{
		origin[i] = txt[i];
		i++;
	}
	return (i);
}

void	make_new_arr(char **origin)
{
	t_env	*tmp;
	int		name_len;
	int		value_len;
	int		i;
	int		j;

	tmp = g_env_list;
	i = 0;
	while (tmp)
	{
		j = 0;
		name_len = ft_strlen(tmp->name);
		value_len = ft_strlen(tmp->value);
		origin[i] = (char *)malloc(sizeof(char) * (name_len + value_len + 2));
		j = j + ft_strcpy(origin[i], tmp->name);
		origin[i][j] = '=';
		j++;
		j = j + ft_strcpy(&origin[i][j], tmp->value);
		origin[i][j] = '\0';
		tmp = tmp->next;
		i++;
	}
	origin[i] = NULL;
	g_env_list->origin = origin;
}

void	free_old_arr(t_env	*tmp)
{
	int		i;

	i = 0;
	while (tmp->origin[i])
	{
		free(tmp->origin[i]);
		i++;
	}
	free(tmp->origin[i]);
	free(tmp->origin);
}

void	env_list_to_arr(void)
{
	t_env	*tmp;
	int		i;
	char	**origin;

	tmp = g_env_list;
	if (tmp->origin)
		free_old_arr(tmp);
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	origin = (char **)malloc(sizeof(char *) * (i + 1));
	make_new_arr(origin);
}
