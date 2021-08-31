NAME			=	minishell
CC				=	gcc
CFLAGS_42		=	-Wall -Wextra -Werror
CLFAGS_ASAN		=	-g2 -fsanitize=address
RL_FLAG			=	-lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
TC_FLAG			=	-ltermcap

H_DIR			=	./include

SRCS_D			=	./parsing/\
					./run/run_shell/\
					./run/ft_utils/\
					./run/blt/\
					./run/redirection/\
					./run/srcs/

OBJS_D			=	./objs/


SRCS			=	./parsing/check_args.c\
					./parsing/check_cmd_echo.c\
					./parsing/check_cmd_echo_2.c\
					./parsing/cutting_line.c\
					./parsing/env_to_str.c\
					./parsing/envp_to_list.c\
					./parsing/find_env_value.c\
					./parsing/parsing.c\
					./parsing/parsing_env.c\
					./parsing/parsing_init.c\
					./parsing/parsing_quote.c\
					./parsing/parsing_redir.c\
					./parsing/parsing_utils.c\
					./parsing/parsing_utils_2.c\
					./parsing/rearrange_args.c\
					./parsing/split_line_by_two.c\
					./run/run_shell/child_process.c\
					./run/run_shell/manage_tmp_file.c\
					./run/run_shell/move_cursor.c\
					./run/run_shell/minishell.c\
					./run/run_shell/multipipe.c\
					./run/run_shell/print_nyan.c\
					./run/run_shell/print_nyan_2.c\
					./run/ft_utils/ft_split.c\
					./run/ft_utils/ft_strjoin.c\
					./run/ft_utils/ft_strlcpy.c\
					./run/ft_utils/ft_strlen.c\
					./run/ft_utils/ft_atoi.c\
					./run/blt/builtin_cd.c\
					./run/blt/builtin_echo.c\
					./run/blt/builtin_env.c\
					./run/blt/builtin_exit.c\
					./run/blt/builtin_export.c\
					./run/blt/builtin_pwd.c\
					./run/blt/builtin_unset.c\
					./run/blt/env_list_to_arr.c\
					./run/redirection/append_out.c\
					./run/redirection/filefd_to_stdin.c\
					./run/redirection/filefd_to_stdout.c\
					./run/redirection/pipefd_to_stdin.c\
					./run/redirection/pipefd_to_stdout.c\
					./run/redirection/redir_connect.c\
					./run/redirection/run_here_document.c\
					./run/redirection/check_heredoc.c\
					./run/srcs/check_blt_func.c\
					./run/srcs/check_cmd.c\
					./run/srcs/check_delimiter.c\
					./run/srcs/error_msg.c\
					./run/srcs/run_blt.c\
					./run/srcs/run_blt_cmd.c\
					./run/srcs/run_cmd.c\
					./run/srcs/run_execve_cmd.c\

OBJS = $(addprefix $(OBJS_D)/, $(notdir $(SRCS:.c=.o)))
vpath %.c $(SRCS_D)


// command must edit

.PHONY:	all clean fclean re bonus

$(NAME): $(OBJ_D) $(PARSING_O) $(RUN_O) $(FT_O) $(BLT_O) $(REDIR_O) $(ELSE_O)
	$(CC) -I$(H_DIR) main.c $(TOTAL_O) -o $(NAME) $(RL_FLAG) $(TC_FLAG)

$(OBJ_D):
	mkdir objs

.c.o:
	$(CC) -I$(H_DIR) -c -o $@ $< $(RL_FLAG) $(TC_FLAG)
	mv $@ $(OBJ_D)

all: $(NAME)

clean:
	rm -rf $(OBJ_D)

fclean: clean
	rm -rf $(NAME)

re:	fclean all
