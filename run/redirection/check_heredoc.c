/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 18:31:50 by ylee              #+#    #+#             */
/*   Updated: 2021/08/09 01:18:48 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env *g_env_list;

void	exec_heredoc(int i, t_list *r_list)
{
	int		fd;
	char	*line;
	char	*delimiter;

	delimiter = ft_strjoin(r_list->file, "\n");
	fd = open(ft_strjoin("/tmp/.", ft_itoa(i)), O_RDWR | O_CREAT | O_TRUNC , 0666);
	if (fd < 0)
	{
		printf("run_heredoc open error\n");
		return ;
	}
	line = readline("> ");
	while (line)
	{
		/*
		if (line[0] == '\0')
		{
			printf("case1\n");
			break ;
		}
		*/
		printf("heredoc line : >|%s|<\n", line);
		printf("heredoc delimiter : >|%s|<\n\n", r_list->file);
		if (ft_strncmp(delimiter, line, ft_strlen(line)) == 1)
		{
			close(fd);
			printf("case2\n");
			exit(0);
		}
		else
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 2);
		}
		free(line);
		line = readline("> ");
	}
	printf("case3\n");
	close(fd);
	exit(3);
}

int	tmp_in_heredoc(int i, t_list *r_list)
{
	pid_t	pid;
	int		status;
	struct termios	term;

	pid = fork();
	if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_env_list->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_env_list->exit_code = WTERMSIG(status);
//		printf("\n*** exit state : %d g_code : %d\n\n", status, g_env_list->exit_code);
//		printf("heredoc result : %d\n", status);
		signal(SIGINT, (void *)sig_handler_c);
		signal(SIGQUIT, SIG_IGN);
/*
		tcgetattr(0, &term);
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &term);
*/
//		printf("tmp heredoc status %d\n", status);
		if (status != 0)
			return (status);
		return (0);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
/*
		tcgetattr(0, &term);
		term.c_lflag &= ECHOCTL;
		tcsetattr(0, TCSANOW, &term);
*/
		exec_heredoc(i, r_list);
		exit(1);
	}
}

int		check_heredoc(t_all *a)
{
	int		i;
	t_all	*tmp;
	t_list	*r_list;

	i = 0;
	tmp = a;
	while (tmp)
	{
		r_list = tmp->redir_list;
		r_list->pipe_idx = i;
		while (r_list)
		{
			if (r_list->redir_flag == 3)
			{
				int	check;
				check = tmp_in_heredoc(i, r_list);
//				printf("check heredoc check %d\n", check);
				if (check == 2) //ctrl + C 로 끝난 경우
				{
					printf("\^C\n");
					return (1);
				}
				else if (check == 3) //ctrl + \ 로 끝난 경우
				{
					printf("\^\\Quit :3\n");
					return (1);
				}
			}
			r_list = r_list->next;
		}
		tmp = tmp->next;
		i++;
	}
	return (0);
}
