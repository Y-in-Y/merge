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
}
