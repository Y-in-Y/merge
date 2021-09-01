/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 18:31:50 by ylee              #+#    #+#             */
/*   Updated: 2021/09/02 02:03:54 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env_list;

void	exec_heredoc(int i, t_list *r_list)
{
	int		fd;
	char	*openfile;
	char	*line;
	char	*delimiter;

	delimiter = ft_strjoin(r_list->file, "\n");
	openfile = ft_strjoin("/tmp/.", ft_itoa(i));
	fd = open(openfile, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		printf("run_heredoc open error\n");
		return ;
	}
	line = readline("> ");
	while (line)
	{
		if (ft_strncmp(delimiter, line, ft_strlen(line)) == 1)
		{
			close(fd);
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
	close(fd);
	exit(3);
}

int	tmp_in_heredoc(int i, t_list *r_list)
{
	pid_t			pid;
	int				status;

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
		signal(SIGINT, (void *)sig_handler_c);
		if (status != 0)
			return (status);
		return (0);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		exec_heredoc(i, r_list);
		exit(1);
	}
	return (1);
}

int	check_heredoc(t_all *a)
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
				if (tmp_in_heredoc(i, r_list) == 2) //ctrl + C 로 끝난 경우
				{
					printf("\n");
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
