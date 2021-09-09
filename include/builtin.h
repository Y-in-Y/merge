/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:55:15 by ylee              #+#    #+#             */
/*   Updated: 2021/09/09 11:55:18 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "parsing.h"

typedef struct s_env	t_env;
typedef struct s_list	t_list;
typedef struct s_all	t_all;

void	reset_std_fd(void);
void	run_blt(t_all *a);
void	run_blt_cmd(t_all *a);
void	builtin_echo(t_all *a);
void	builtin_cd(t_all *a);
void	builtin_pwd(t_all *a);
void	builtin_export(t_all *a);
void	run_export(char *name, char *value);
void	builtin_unset(t_all *a);
void	builtin_env(t_all *a);
void	builtin_exit(t_all *a);
void	run_export(char *name, char *value);
void	env_list_to_arr(void);
char	*find_env_value(char *name);

#endif
