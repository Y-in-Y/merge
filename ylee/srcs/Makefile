USER = ylee

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RL_FLAG = -I ~/.brew/opt/readline/include
#RL_FLAG = -I /usr/include/readline/include

FSNTZ = -fsanitize=address

NAME = minishell.a

H_DIR = ../include

SRCS = minishell.c\
	   print_ascii_art.c\
	   error_msg.c\
	   check_exit.c\
	   ft_strncmp.c\
	   move_cursor.c\
	   env_list_to_arr.c\
	   ft_strlen.c\
	   ft_strdup.c\
       ft_strjoin.c\
       ft_split.c\
       ft_calloc.c\
       ft_strlcpy.c\
       redir_connect.c\
	   check_cmd_upper.c\
	   check_blt_func.c\
	   builtin_echo.c\
	   builtin_cd.c\
	   builtin_pwd.c\
	   builtin_export.c\
	   builtin_unset.c\
	   builtin_env.c\
	   builtin_exit.c\
	   find_env_value.c\
	   parsing.c\
	   parsing_utils.c\
	   check_args.c\
	   parsing_test.c\
	   multipipe.c\
	   child_process.c\
	   pipefd_to_stdin.c\
	   pipefd_to_stdout.c\
	   filefd_to_stdin.c\
	   filefd_to_stdout.c\
	   run_here_document.c\
	   final_result_append_to_outfile.c\
	   check_cmd.c\
	   run_blt.c\
	   run_execve_cmd.c\
#	   run_cmd.c\
#	   builtin_cmd_check.c\
#	   parsing_utils.c\

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)

$(OBJS) : $(SRCS)
	$(CC) $(CFLAGS) -I$(H_DIR) -c $(SRCS) $(RL_FLAG) $(FSNTZ)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
