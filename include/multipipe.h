#ifndef MULTIPIPE_H
# define MULTIPIPE_H

# include "minishell.h"

# define READ 0
# define WRITE 1
# define STDIN_FD 0
# define STDOUT_FD 1

void	make_tmp_file(int	cnt);
void	remove_tmp_file(int	cnt);
int		check_heredoc(t_all *a);

void	multipipe(t_all *a);
void	child_process(t_all *a, int i, int **fd);
void	pipefd_to_stdin(int *fd);
void	pipefd_to_stdout(int *fd);
void	filefd_to_stdin(char *file);
void	filefd_to_stdout(char *file);
void	run_here_document(char *file);
int		check_delimiter(char *argv, char *str);
void	append_out(char *file);

#endif
