#include "minishell.h"

extern t_env	*g_env_list;

void	parsing_test(t_all *a)
{
	pid_t	pid;
	int		state;
	char	*argv[3];

	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
//		printf("this child process is %d\n", getpid());

/*
		argv[0] = "printenv";
		argv[1] = "PWD";
		argv[2] = NULL;
		execve("/usr/bin/printenv", argv, ms->envp);
*/

/*		
		state = open("./in", O_RDWR);
		if (state < 0)
		{
			printf("state : %d\n", state);
			error_msg("openerror");
		}
*/		
		argv[0] = "ls";
		argv[1] = NULL;
		argv[2] = NULL;
		if (!a)
			return ;
		execve("/bin/ls", argv, 0);
	}
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &state, 0);
		printf("process %d is over. state is %d\n", pid, state);
		signal(SIGINT, (void *)sig_handler_c);
//		printf("process %d is over\n", pid);
	}
}
