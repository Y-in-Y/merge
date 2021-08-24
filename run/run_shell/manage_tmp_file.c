/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_tmp_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 22:02:57 by ylee              #+#    #+#             */
/*   Updated: 2021/08/24 18:12:37 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_tmp_file(int cnt)
{
	pid_t	pid;
	int		status;
	int		i;
	char	**rm;

	pid = fork();
	if (pid > 0)
		wait(&status);
	else if (pid == 0)
	{
		rm = malloc(sizeof(char *) * (cnt + 3));
		rm[0] = "rm";
		i = 0;
		while (i <= cnt)
		{
			rm[i + 1] = ft_strjoin("/tmp/.", ft_itoa(i));
			i++;
		}
		rm[i + 1] = NULL;
		execve("/bin/rm", rm, NULL);
		printf("rm execve do not run");
	}
}

void	make_tmp_file(int	cnt)
{
	pid_t	pid;
	int		i;
	int		status;
	int		fd;

	i = 0;
	pid = fork();
	if (pid > 0)
		wait(&status);
	else if (pid == 0)
	{
		while (i <= cnt)
		{
			fd = open(ft_strjoin("/tmp/.", ft_itoa(i)), \
					O_RDWR | O_CREAT | O_TRUNC, 0666);
			close(fd);
			i++;
		}
		exit(0);
	}
}
