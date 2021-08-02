#include "minishell.h"

t_env	*g_env_list;

t_env	*envp_to_list(char *env)
{
	t_env	*list;
	int		i;

	list = (t_env *)malloc(sizeof(t_env));
	if (!list)
		return (0);
	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			break ;
		i++;
	}
	if (env[i] == '=')
	{
		env[i] = '\0';
		list->name = ft_strdup(env);
		list->value = ft_strdup(&env[i + 1]);
		list->origin = NULL;
		list->next = NULL;
	}
	else
		return (0);
	return (list);
}

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
	print_ascii_art();
	g_env_list = init_envp(envp);
	env_list_to_arr();
	pid = fork();
	if (pid < 0)
		error_msg("fork error");
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid > 0)
	{
//		printf("main process : %d\n", getpid());
		waitpid(pid, &state, 0);
		if (state != 0)
			printf("minishell error %d\n", state);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
//		printf("minishell is over\n");
	}
	else if (pid == 0)
	{
//		printf("minishell process : %d\n", getpid());
		minishell();
	}
//	system("leaks minishell");
	return (0);
}
