#include "minishell.h"

extern t_env	*g_env_list;

void	builtin_cd(t_all *a)
{
	char	*pwd;
	t_env	*tmp;

	if (!a)
		return ;
	pwd = getcwd(NULL, 0);
	run_export("OLDPWD", pwd);
	if (!a->arg[1])
	{
		tmp = g_env_list;
		while (tmp)
		{
			if (ft_strncmp(tmp->name, "HOME", 5) == 1)
			{
				pwd = tmp->value;
				break ;
			}
			tmp = tmp->next;
		}
		chdir(pwd);
		pwd = getcwd(NULL, 0);
		run_export("PWD", pwd);
	}
	else
	{
		if (chdir(a->arg[1]) == -1)
		{
			printf("%s is not a directory\n", a->arg[1]);
			return ;
		}
		pwd = getcwd(NULL, 0);
		run_export("PWD", pwd);
	}
	g_env_list->exit_code = 0;
}
