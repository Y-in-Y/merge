/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_result_append_to_outfile.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:26:15 by ylee              #+#    #+#             */
/*   Updated: 2021/06/14 23:15:08 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	final_result_append_to_outfile(char *file)
{
	int		fd;

	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
		error_msg("file open error");
	dup2(fd, STDOUT_FD);
	close(fd);
}
