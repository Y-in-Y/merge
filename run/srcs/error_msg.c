#include "minishell.h"

void	error_msg(char *str)
{
	perror(str);
	exit(1);
}
