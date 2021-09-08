#include "minishell.h"

extern t_env	*g_env_list;

void	parsing_error_case(char *line)
{
	printf("syntax error\n");
	g_env_list->exit_code = 258;
	free(line);
}

void	shell_parent_process(t_all *a, pid_t pid)
{
	int	state;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &state, 0);
	if (WIFEXITED(state))
		g_env_list->exit_code = WEXITSTATUS(state);
	else if (WIFSIGNALED(state))
		g_env_list->exit_code = WTERMSIG(state) + 128;
	if (state == 2)
		printf("^C\n");
	else if (state == 3 && a->pipe_cnt == 0)
		printf("^\\Quit: 3\n");
	else if (state == 3 && a->pipe_cnt != 0)
		printf("^\\");
	signal(SIGINT, (void *)sig_handler_c);
	signal(SIGQUIT, SIG_IGN);
}

void	need_fork_case(t_all *a)
{
	pid_t	pid;

	pid = fork();
	if (pid > 0)
		shell_parent_process(a, pid);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (a->pipe_cnt == 0)
			run_execve_cmd(a);
		else
		{
			multipipe(a);
			exit(0);
		}
	}
}

void	validlinecase(char *line)
{
	int		check;
	t_all	a;

	check = -1;
	parsing(line, &a);
	if (!a.int_line_cut)
		parsing_error_case(line);
	else
	{
		make_tmp_file(a.pipe_cnt);
		if (check_heredoc(&a, 0) == 0)
			check = check_cmd(&a);
		if (check == 1 && a.pipe_cnt == 0)
			run_blt(&a);
		else if (check == 0 || a.pipe_cnt != 0)
			need_fork_case(&a);
		remove_tmp_file(a.pipe_cnt);
		if (line && line[0])
			add_history(line);
		free(line);
		free_struct(&a);
	}
}

void	minishell(void)
{
	int		row;
	int		col;
	char	*line;

	init_setting(&row, &col);
	line = readline(PROMPT);
	while (line)
	{
		if (line[0])
			validlinecase(line);
		else
			free(line);
		line = readline(PROMPT);
	}
	if (!line)
	{
		move_cursor(&row, &col);
		write(1, "exit\n", 5);
		exit(0);
	}
}
