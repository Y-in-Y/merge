/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 00:06:54 by ylee              #+#    #+#             */
/*   Updated: 2021/08/24 15:39:32 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*g_env_list;

t_env	*init_envp(char **envp)
{
	t_env	*first;
	t_env	*tmp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	envp[i] = NULL;
	first = envp_to_list(envp[0]);
	tmp = first;
	i = 1;
	while (envp[i])
	{
		tmp->next = envp_to_list(envp[i]);
		tmp = tmp->next;
		i++;
	}
	return (first);
}

int	main(int argc, char **argv, char **envp)
{
	int			state;
	pid_t		pid;

	if (argc != 1 || !argv || !envp)
		error_msg("no need arg!");
	print_nyan();
	g_env_list = init_envp(envp);
	struct termios term;
	tcgetattr(0, &term);
	env_list_to_arr();
	pid = fork();
	if (pid < 0)
		error_msg("fork error");
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid > 0)
	{
		waitpid(pid, &state, 0);
		if (WIFEXITED(state))
			exit(WEXITSTATUS(state));
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (pid == 0)
		minishell();
	tcsetattr(0, TCSANOW, &term);
	if (WIFEXITED(state))
		exit(WEXITSTATUS(state));
	return (0);
}
