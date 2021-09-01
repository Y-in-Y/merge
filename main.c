/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 00:06:54 by ylee              #+#    #+#             */
/*   Updated: 2021/09/02 02:05:26 by ylee             ###   ########.fr       */
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

void	main_parent_process(pid_t pid, int state, struct termios term)
{
	waitpid(pid, &state, 0);
	tcsetattr(0, TCSANOW, &term);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (WIFEXITED(state))
		exit(WEXITSTATUS(state));
}

int	main(int argc, char **argv, char **envp)
{
	int				state;
	pid_t			pid;
	struct termios	term;

	if (argc != 1 || !argv || !envp)
		error_msg("no need arg!");
	state = 0;
	print_nyan();
	g_env_list = init_envp(envp);
	tcgetattr(0, &term);
	env_list_to_arr();
	pid = fork();
	if (pid < 0)
		error_msg("fork error");
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid > 0)
		main_parent_process(pid, state, term);
	else if (pid == 0)
		minishell();
	return (0);
}
