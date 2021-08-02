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

    signal(SIGINT, (void *)sig_handler_c);
    signal(SIGQUIT, SIG_IGN);
    tcgetattr(0, &term);
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
    char	*line;
    t_all	a;

    init_setting(&row, &col);
    line = readline(PROMPT);
    while (line)
    {
        if (line[0])
        {
            //		printf("stdin line is |%s|\n", line);
            parsing(line, &a); // line parsing and add data to a struct
            
/*
            printf("parsing is end. here is minishell func.\n");
            printf("struct a init?\n");
            t_all *tmp;
            tmp = &a;
            while (tmp)
            {
       			printf("cmd : %s  ", tmp->cmd);
                tmp = tmp->next;
            }
            printf("\n");
  */          

            int check;
			check = check_blt_func(a.cmd);
			if (check == 1 && a.pipe_cnt != 0)
				check = 0;
			if (check == 1)
				run_blt(&a);
			else if (check == 0) // cmd is builtin cmd : return  1, is not : return 0
            {
                //printf("builtin_cmd_check : %d\n", check);
                pid_t	pid;
                int		state;
                pid = fork();
                if (pid > 0)
                {
                    waitpid(pid, &state, 0);
//					printf("pid %d is exit by state %d\n", pid, state);
                }
                else if (pid == 0)
                {
                    if (a.pipe_cnt == 0)
                        run_execve_cmd(&a); // no pipe and cmd is not builtin -> use execve to run cmd
                    else
                    {
                        multipipe(&a); // when 1 more pipe
                        exit(0);
                    }
                }
            }
            //		printf("builtin_cmd_check : %d\n", check);
            if (line && line[0])
                add_history(line);
            //		printf("this process is %d\n", getpid());
            free(line);
            free_struct(&a);
            //		printf("\n\nnow new prompt\n\n");
        }
        else
            free(line);
        line = readline(PROMPT);
    }
    if (!line)// press ctrl+D in prompt
    {
        move_cursor(&row, &col);
        write(1, "exit\n", 5);
        exit(0);
    }
}
