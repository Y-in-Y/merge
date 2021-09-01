NAME			=	minishell
CC				=	gcc
CFLAGS_42		=	-Wall -Wextra -Werror
CLFAGS_ASAN		=	-g2 -fsanitize=address
H_FLAG			=	-I./include -I ~/.brew/opt/readline/include
RL_FLAG			=	-lreadline -L ~/.brew/opt/readline/lib
TC_FLAG			=	-ltermcap
H_DIR			=	./include
OBJ_D			=	./objs/
LIB				=	minishell.a
TOTAL_O			=	$(addsuffix .o, $(addprefix $(OBJ_D), $(PARSING_F)))\
					$(addsuffix .o, $(addprefix $(OBJ_D), $(RUN_F)))\
					$(addsuffix .o, $(addprefix $(OBJ_D), $(FT_F)))\
					$(addsuffix .o, $(addprefix $(OBJ_D), $(BLT_F)))\
					$(addsuffix .o, $(addprefix $(OBJ_D), $(REDIR_F)))\
					$(addsuffix .o, $(addprefix $(OBJ_D), $(ELSE_F)))\


PARSING_D		=	./parsing/
PARSING_F		=	check_args\
					check_cmd_echo\
					check_cmd_echo_2\
					cutting_line\
					env_to_str\
					envp_to_list\
					find_env_value\
					parsing\
					parsing_env\
					parsing_init\
					parsing_quote\
					parsing_redir\
					parsing_utils\
					parsing_utils_2\
					rearrange_args\
					split_line_by_two\

PARSING_C		=	$(addsuffix .c, $(addprefix $(PARSING_D), $(PARSING_F)))
PARSING_O		=	$(addsuffix .o, $(addprefix $(OBJ_D), $(PARSING_F)))

RUN_D			=	./run/run_shell/
RUN_F			=	child_process\
					manage_tmp_file\
					move_cursor\
					minishell\
					multipipe\
					print_nyan\
					print_nyan_2\

RUN_C			=	$(addsuffix .c, $(addprefix $(RUN_D), $(RUN_F)))
RUN_O			=	$(addsuffix .o, $(addprefix $(OBJ_D), $(RUN_F)))

FT_D			=	./run/ft_utils/
FT_F			=	ft_split\
					ft_strjoin\
					ft_strlcpy\
					ft_strlen\
					ft_atoi\

FT_C			=	$(addsuffix .c, $(addprefix $(FT_D), $(FT_F)))
FT_O			=	$(addsuffix .o, $(addprefix $(OBJ_D), $(FT_F)))

BLT_D			=	./run/blt/
BLT_F			=	builtin_cd\
					builtin_echo\
					builtin_env\
					builtin_exit\
					builtin_export\
					builtin_pwd\
					builtin_unset\
					env_list_to_arr\
					run_export\

BLT_C			=	$(addsuffix .c, $(addprefix $(BLT_D), $(BLT_F)))
BLT_O			=	$(addsuffix .o, $(addprefix $(OBJ_D), $(BLT_F)))

REDIR_D			=	./run/redirection/
REDIR_F			=	append_out\
					filefd_to_stdin\
					filefd_to_stdout\
					pipefd_to_stdin\
					pipefd_to_stdout\
					redir_connect\
					run_here_document\
					check_heredoc\

REDIR_C			=	$(addsuffix .c, $(addprefix $(REDIR_D), $(REDIR_F)))
REDIR_O			=	$(addsuffix .o, $(addprefix $(OBJ_D), $(REDIR_F)))

ELSE_D			=	./run/srcs/
ELSE_F			=	check_blt_func\
					check_cmd\
					check_delimiter\
					error_msg\
					run_blt\
					run_blt_cmd\
					run_execve_cmd\

ELSE_C			=	$(addsuffix .c, $(addprefix $(ELSE_D), $(ELSE_F)))
ELSE_O			=	$(addsuffix .o, $(addprefix $(OBJ_D), $(ELSE_F)))


all: $(NAME)

$(NAME): $(OBJ_D) $(LIB)
	$(CC) $(CFLAGS_42) $(H_FLAG) main.c $(LIB) -o $(NAME) $(RL_FLAG) $(TC_FLAG)

$(OBJ_D):
	mkdir objs

.c.o:
	$(CC) $(CFLAGS_42) $(H_FLAG) -c -o $@ $<
#	mv $@ $(OBJ_D)

$(LIB): $(PARSING_O) $(RUN_O) $(FT_O) $(BLT_O) $(REDIR_O) $(ELSE_O) $(TOTAL_O)
	ar rc $@ $(TOTAL_O)

clean:
	rm -rf $(OBJ_D)

fclean: clean
	rm -rf $(NAME)

re:	fclean all


.PHONY:	all clean fclean re
