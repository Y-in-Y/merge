#include "minishell.h"

extern t_env	*g_env_list;

void	only_pipe(t_all *a, int i, int **fd)
{
	if (!a || i < 0 || !fd)
		exit(0);
	if (i > 0)
		pipefd_to_stdin(fd[i - 1]);
	if (i < a->pipe_cnt)
		pipefd_to_stdout(fd[i]);
}

void    rearrange_arg(t_all *a)
{
    int     i;
    int     cnt;
    char    **new;

    i = 0;
    cnt = 0;
    while (a->arg && a->arg[i])
    {
        if (a->arg[i][0])
            cnt++;
        i++;
    }
    new = (char **)malloc(sizeof(char *) * (cnt + 1));
    i = 0;
    cnt = 0;
    while (a->arg[i])
    {
        if (a->arg[i][0] != '\0')
        {
//			printf("a->arg[%d][0] : %c = %d\n", i, a->arg[i][0], a->arg[i][0]);
            new[cnt] = ft_strdup(a->arg[i]);
            cnt++;
        }
        free(a->arg[i]);
        i++;
    }
    new[cnt] = NULL;
    free(a->arg[i]);
    free(a->arg);
    a->arg = new;
    i = 0;
    while (a->arg && a->arg[i])
    {
//		printf("new a->arg[%d] : %s\n", i, a->arg[i]);
        i++;
    }
}

void	child_process(t_all *a, int i, int **fd)
{
	t_all	*thispage;
	t_list	*tmp;
	int		check;
	int		j;

	j = 0;
	thispage = a;
	while (j < i)
	{
		thispage = thispage->next;
		j++;
	}
	thispage->pipe_cnt = 1;
	tmp = thispage->redir_list;
	if (tmp && tmp->redir_flag != 0)
        rearrange_arg(thispage);
	only_pipe(a, i, fd);
	check = check_blt_func(thispage->cmd);
	if (check == 1)
		run_blt(thispage);
	else if (check == 0)
		run_execve_cmd(thispage);
}
