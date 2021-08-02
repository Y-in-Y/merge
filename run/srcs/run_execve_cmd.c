#include "minishell.h"

extern t_env    *g_env_list;

char    **path_dir(void)
{
	char    *path;
	char    **dir;
	int     i;

	path = find_env_value("PATH");
	if (!path)
		error_msg("cannot find PATH env");
//	printf("path : %s\n", path);
	dir = ft_split(path, ':');
	if (!dir)
		error_msg("cannot split path");
	i = 0;
//	printf(">>path split result<<\n");
	while (dir[i])
	{
//		printf("%d) %s\n", i, dir[i]);
		i++;
	}
	return (dir);
}

void	run_execve_cmd(t_all *a)
{
	char    **dir;
	char    *tmp;
	char    *cmd;

	dir = path_dir();
	if (a->redir_list && a->redir_list->redir_flag != 0)
	{
		redir_connect(a->redir_list);
        rearrange_arg(a);
	}
	while (dir && *dir)
	{
//		printf("dir : %s  ", *dir);
		tmp = ft_strjoin(*dir, "/");
		cmd = ft_strjoin(tmp, a->cmd);
		free(tmp);
		printf("join cmd : %s\n", cmd);
//		int i;
//		i = 0;
//		while (a->arg[i])
//		{
//			printf("arg[%d] : %s\n", i, a->arg[i]);
//			i++;
//		}
		execve(cmd, a->arg, g_env_list->origin);
		free(cmd);
		dir++;
	}
	error_msg("cmd not found");
}
