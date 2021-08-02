#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "parsing.h"

typedef struct		s_env	t_env;
typedef struct		s_list	t_list;
typedef	struct		s_all	t_all;

int		check_blt_func(char *cmd);
int		check_cmd(t_all *a, int cnt, int *new_fd);
void	reset_std_fd(int *new_fd);
void	run_blt(t_all *a);
//int		builtin_cmd_check(t_all *a);
void	builtin_echo(t_all *a);
void	builtin_cd(t_all *a);
void	builtin_pwd(t_all *a);
void	builtin_export(t_all *a);
void	builtin_unset(t_all *a);
void	builtin_env(t_all *a);
void	builtin_exit(t_all *a, int *new_fd);
void	run_export(char *name, char *value);
void	env_list_to_arr(void);
char	*find_env_value(char *name);

#endif
