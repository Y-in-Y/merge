#include "minishell.h"

extern t_env	*g_env_list;

void	redir_in(t_list *tmp)
{
	filefd_to_stdin(tmp->file);
}

void	redir_out(t_list *tmp)
{
	filefd_to_stdout(tmp->file);
}

void	heredoc(t_list *tmp)
{
	int		p_fd[2];
	char	*line;

	pipe(p_fd);
	while (1)
	{
		line = readline("> ");
		if (line)
		{
			printf("heredoc line : |%s|\n", line);
			if (ft_strncmp(line, tmp->file, ft_strlen(line)) == 1)
				break ;
			write(p_fd[1], line, ft_strlen(line));
			write(p_fd[1], "\n", 1);
			free(line);
		}
	}
	close(p_fd[1]);
	dup2(p_fd[0], 0);
	close(p_fd[0]);
}

void	out_append(t_list *tmp)
{
	final_result_append_to_outfile(tmp->file); //need to rename
}

void	redir_connect(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->redir_flag == 0)
			break ;
		if (tmp->redir_flag == 1)
			redir_in(tmp);
		else if (tmp->redir_flag == 2)
			redir_out(tmp);
		else if (tmp->redir_flag == 3)
			heredoc(tmp);
		else if (tmp->redir_flag == 4)
			out_append(tmp);
		else
			error_msg("redir error");
		tmp = tmp->next;
	}
}
