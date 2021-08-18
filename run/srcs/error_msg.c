#include "minishell.h"

void	error_msg(char *str)
{
	if (ft_strncmp("cmd not found", str, ft_strlen(str)))
	{
		perror(str);
		exit(127);
	}
	perror(str);
	exit(1);
}
