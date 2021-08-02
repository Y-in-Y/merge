/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filefd_to_stdin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 19:13:03 by ylee              #+#    #+#             */
/*   Updated: 2021/06/13 17:12:27 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	filefd_to_stdin(char *file)
{
	int		fd;

	fd = open(file, O_RDWR | O_CREAT, 0666);
	if (fd < 0)
		error_msg("file open error");
	dup2(fd, STDIN_FD);
	close(fd);
}
