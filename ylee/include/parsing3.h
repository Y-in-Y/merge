/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:09:50 by inyang            #+#    #+#             */
/*   Updated: 2021/07/07 17:05:20 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	char			**origin;
	struct s_env	*next;
}				t_env;

typedef struct s_list
{
	int				redir_flag;
	char			*file;
	struct s_list	*next;
}				t_list;

typedef struct s_all
{
	int				pipe_cnt;
	char			*line_cut;
	int				*int_line_cut;
	char			*cmd;
	char			**argv;
	t_list			*redir_list;
	struct s_all	*next;
}				t_all;

int		parsing(char *line, t_all *start);
void	parsing_test(t_all *a);
char			**ft_split(char const *s, char c);
int				px_gnl(char **line);
int				px_strlen(char *s);

#endif
