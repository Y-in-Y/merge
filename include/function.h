/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:55:23 by ylee              #+#    #+#             */
/*   Updated: 2021/09/09 11:55:25 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# include "minishell.h"

void	sig_handler_c(int signo);
void	init_setting(int *row, int *col);
void	minishell(void);
void	error_msg(char *str);
int		check_exit(char *line);
int		check_cmd(t_all *a);
char	*check_cmd_upper(char *cmd, int *cnt);
void	move_cursor(int *row, int *col);
void	run_execve_cmd(t_all *a);
void	redir_connect(t_list *list);
void	free_struct(t_all *a);

int		ft_atoi(char *str);
int		ft_strlen(char *str);
char	*ft_strjoin(char *str1, char *str2);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif
