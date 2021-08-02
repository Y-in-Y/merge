/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_here_document.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:22:53 by ylee              #+#    #+#             */
/*   Updated: 2021/06/15 14:30:59 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_line(char **line, char *buf, char *file, int *fd)
{
	char	*tmp;
	char	*file_for_check;

	tmp = ft_strjoin(*line, buf);
	if (*line)
		free(*line);
	*line = tmp;
	if (*buf == '\n')
	{
		file_for_check = ft_strjoin(file, "\n");
		if (check_delimiter(*line, file_for_check) == 1)
		{
			free(file_for_check);
			free(*line);
			return (1);
		}
		free(file_for_check);
		write(fd[WRITE], *line, ft_strlen(*line));
		free(*line);
		*line = NULL;
		write(1, "pipe heredoc> ", ft_strlen("pipe heredoc> "));
	}
	return (0);
}

void	run_here_document(char *file)
{
	int		fd[2];
	int		readlen;
	int		check_result;
	char	*line;
	char	buf[2];

	if (pipe(fd) < 0)
		error_msg("pipe error");
	line = NULL;
	buf[1] = '\0';
	write(1, "pipe heredoc> ", ft_strlen("pipe heredoc> "));
	readlen = read(0, buf, 1);
	if (readlen < 0)
		error_msg("read error");
	while (readlen > 0)
	{
		check_result = check_line(&line, buf, file, fd);
		if (check_result == 1)
			break ;
		readlen = read(0, buf, 1);
	}
	dup2(fd[READ], STDIN_FD);
	close(fd[READ]);
	close(fd[WRITE]);
}
