#include "minishell.h"

int	check_cmd(t_all *a, int cnt)
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
		builtin_exit(a);
	else
		return (0);
	return (1);
}

int	check_blt_func(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 1)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 1)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 4) == 1)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 1)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 1)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 1)
		return (1);
	else if (ft_strncmp(cmd, "exit", 5) == 1)
		return (1);
	return (0);
}

int	builtin_cmd_check(t_all *a, int is_pipe)
{
    int     cnt;
	int		is_blt;

	if (!a)
		return (0);
//	printf("pipe num is %d and cmd is %s\n", a->pipe_cnt, a->cmd);
	if (a->pipe_cnt != 0)
		return (0);
	printf("here blt cmd check func\n");
	if (a->redir_list)
		printf("redir_flag : %d\n", a->redir_list->redir_flag);
    cnt = 0;
    check_cmd_upper(a->cmd, &cnt);
	is_blt = check_blt_func(a->cmd);
	if (is_blt == 0)
		return (0);
	if (is_pipe == 0)
	{

	}
	//divide check and run func for blt
	return (check_cmd(a, cnt));
}
