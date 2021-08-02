#include "minishell.h"

int	check_cmd(t_all *a, int cnt, int *new_fd)
{
	if (ft_strncmp(a->cmd, "echo", 5) == 1)
		builtin_echo(a);
	else if (ft_strncmp(a->cmd, "cd", 3) == 1)
		builtin_cd(a);
	else if (ft_strncmp(a->cmd, "pwd", 4) == 1)
		builtin_pwd(a);
	else if (ft_strncmp(a->cmd, "export", 7) == 1)
    {
        if (cnt == 0)
		    builtin_export(a);
        else
        {
            printf("command not found\n");
            return (-1);
        }
    }
	else if (ft_strncmp(a->cmd, "unset", 6) == 1)
    {
        if (cnt == 0)
            builtin_unset(a);
        else
        {
            printf("command not found\n");
            return (-1);
        }
	}
    else if (ft_strncmp(a->cmd, "env", 4) == 1)
		builtin_env(a);
	else if (ft_strncmp(a->cmd, "exit", 5) == 1)
		builtin_exit(a, new_fd);
	else
		return (0);
	return (1);
}
