#include "minishell.h"

extern t_env	*g_env_list;

void	sig_handler_c(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_setting(int *row, int *col)
{
	struct termios	term;

	g_env_list->origin_stdin = dup(0);
	g_env_list->origin_stdout = dup(1);
	signal(SIGINT, (void *)sig_handler_c);
	signal(SIGQUIT, SIG_IGN);
	tcgetattr(0, &term);
	tcgetattr(0, &(g_env_list->backup));
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	*row = 0;
	*col = 0;
}

void	free_struct(t_all *a)
{
	free(a->int_line_cut);
	free(a->arg);
	free(a->redir_list);
	if (a->next)
	{
		free_struct(a->next);
		free(a->next);
	}
}

void	minishell(void)
{
	int		row;
	int		col;
	int		check;
	char	*line;
	t_all	a;

	init_setting(&row, &col);
	line = readline(PROMPT);
	while (line)
	{
		if (line[0])
		{
			parsing(line, &a); // line parsing and add data to a struct
			if (!a.int_line_cut)
			{
				printf("syntax error\n");
				g_env_list->exit_code = 258;
				free(line);
			}
			else
			{
//				printf("int line cut pointer : %p\n", a.int_line_cut);
				make_tmp_file(a.pipe_cnt);
//				printf("end make tmp file\n");
				if (check_heredoc(&a, 0) == 0)
					check = check_cmd(&a);
				else // heredoc 중에 ctrl + C 로 끝낸경우 
					check = -1;
				if (check == -1)
					;
				else if (check == 1 && a.pipe_cnt == 0)
					run_blt(&a);
				else if (check == 0 || a.pipe_cnt != 0) // cmd is builtin cmd : return  1, is not : return 0
				{
					pid_t	pid;
					int		state;
					pid = fork();
					if (pid > 0)
					{
						signal(SIGINT, SIG_IGN);
						signal(SIGQUIT, SIG_IGN);
						waitpid(pid, &state, 0);
						if (WIFEXITED(state))
							g_env_list->exit_code = WEXITSTATUS(state);
						else if (WIFSIGNALED(state))
							g_env_list->exit_code = WTERMSIG(state) + 128;
						if (state == 2)
							printf("^C\n");
						else if (state == 3 && a.pipe_cnt == 0)
							printf("^\\Quit: 3\n");
						else if (state == 3 && a.pipe_cnt != 0)
							printf("^\\");
						signal(SIGINT, (void *)sig_handler_c);
						signal(SIGQUIT, SIG_IGN);
					}
					else if (pid == 0)
					{
						signal(SIGINT, SIG_DFL);
						signal(SIGQUIT, SIG_DFL);
						if (a.pipe_cnt == 0)
							run_execve_cmd(&a); // no pipe and cmd is not builtin -> use execve to run cmd
						else
						{
							multipipe(&a); // when 1 more pipe
							exit(0);
						}
					}
				}
				remove_tmp_file(a.pipe_cnt);
				if (line && line[0])
					add_history(line);
				free(line);
				free_struct(&a);
			}
		}
		else //line[0] = '\0' 인 경우 : enter 나 ctrl+C 한 경우
			free(line);
		line = readline(PROMPT);
	}
	if (!line) // press ctrl+D in prompt
	{
		move_cursor(&row, &col);
		write(1, "exit\n", 5);
		exit(0);
	}
}
