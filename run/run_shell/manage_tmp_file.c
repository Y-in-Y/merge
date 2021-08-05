/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_tmp_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 22:02:57 by ylee              #+#    #+#             */
/*   Updated: 2021/08/06 00:21:48 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_tmp_file(void)
{
	pid_t	pid;
	int		status;
	char	**ls;

	pid = fork();
	if(pid > 0)
		wait(&status);
	else if(pid == 0)
	{
		ls = malloc(sizeof(char *) * 5);
		ls[0] = "ls";
		ls[1] = "-al";
		ls[2] = "/tmp/";
		ls[3] = NULL;
		execve("/bin/ls", ls, NULL);
		printf("execve do not run\n");
	}
}

void	remove_tmp_file(int cnt)
{
	pid_t	pid;
	int	status;
	char	**rm;

	pid = fork();
	if (pid > 0)
		wait(&status);
	else if (pid == 0)
	{
		rm = malloc(sizeof(char *) * (cnt + 3));
		rm[0] = "rm";
		int i = 0;
		while (i <= cnt)
		{
			rm[i + 1] = ft_strjoin("/tmp/.", ft_itoa(i));
			i++;
		}
		rm[i + 1] = NULL;
		execve("/bin/rm", rm, NULL);
		printf("rm execve do not run");
	}
	check_tmp_file();
}

void	make_tmp_file(int	cnt)
{
	pid_t	pid;
	int	i;
	int	status;
	int	fd;
	char	*tmp;
	char	**ls;

	i = 0;
	pid = fork();
	if (pid > 0)
		wait(&status);
	else if (pid == 0)
	{
		while (i <= cnt)
		{
			tmp = ft_strjoin("/tmp/.", ft_itoa(i));
			fd = open(tmp, O_RDWR | O_CREAT | O_TRUNC ,0666);
			close(fd);
			i++;
		}
		check_tmp_file();
		exit(0);
	}
}
