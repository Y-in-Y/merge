#include "minishell.h"

extern t_env	*g_env_list;

void	builtin_cd(t_all *a)
{
	char	*pwd;

	if (!a)
		return ;
	pwd = getcwd(NULL, 0);
	run_export("OLDPWD", pwd);
	if (!a->arg[1])
	{
		t_env *tmp = g_env_list;
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
		chdir(a->arg[1]);
		pwd = getcwd(NULL, 0);
		run_export("PWD", pwd);
	}
}
