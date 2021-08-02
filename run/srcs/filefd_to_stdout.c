/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filefd_to_stdout.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 19:13:03 by ylee              #+#    #+#             */
/*   Updated: 2021/06/13 17:12:40 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	filefd_to_stdout(char *file)
{
	int		fd;

	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd < 0)
		error_msg("file open error");
//	printf("file %s open by fd %d\n", file, fd);
	dup2(fd, STDOUT_FD);
	close(fd);
}
