NAME			=	minishell
CC				=	gcc
CFLAGS_42		=	-Wall -Wextra -Werror
CLFAGS_ASAN		=	-g2 -fsanitize=address
RL_FLAG			=	-lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
TC_FLAG			=	-ltermcap
H_DIR			=	./include
OBJ_D			=	./objs/
TOTAL_O			=	$(addsuffix .o, $(addprefix $(OBJ_D), $(PARSING_F)))\
					$(addsuffix .o, $(addprefix $(OBJ_D), $(RUN_F)))\
					$(addsuffix .o, $(addprefix $(OBJ_D), $(FT_F)))\
					$(addsuffix .o, $(addprefix $(OBJ_D), $(BLT_F)))\
					$(addsuffix .o, $(addprefix $(OBJ_D), $(REDIR_F)))\
					$(addsuffix .o, $(addprefix $(OBJ_D), $(ELSE_F)))\


PARSING_D		=	./parsing/
PARSING_F		=	check_args\
					check_cmd_echo\
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
PARSING_O		=	$(addsuffix .o, $(addprefix $(PARSING_D), $(PARSING_F)))

RUN_D			=	./run/run_shell/
RUN_F			=	print_ascii_art\
					child_process\
					manage_tmp_file\
					move_cursor\
					minishell\
					multipipe\

RUN_C			=	$(addsuffix .c, $(addprefix $(RUN_D), $(RUN_F)))
RUN_O			=	$(addsuffix .o, $(addprefix $(RUN_D), $(RUN_F)))

FT_D			=	./run/ft_utils/
FT_F			=	ft_split\
					ft_strjoin\
					ft_strlcpy\
					ft_strlen\

FT_C			=	$(addsuffix .c, $(addprefix $(FT_D), $(FT_F)))
FT_O			=	$(addsuffix .o, $(addprefix $(FT_D), $(FT_F)))

BLT_D			=	./run/blt/
BLT_F			=	builtin_cd\
					builtin_echo\
					builtin_env\
					builtin_exit\
					builtin_export\
					builtin_pwd\
					builtin_unset\
					env_list_to_arr\

BLT_C			=	$(addsuffix .c, $(addprefix $(BLT_D), $(BLT_F)))
BLT_O			=	$(addsuffix .o, $(addprefix $(BLT_D), $(BLT_F)))

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
REDIR_O			=	$(addsuffix .o, $(addprefix $(REDIR_D), $(REDIR_F)))

ELSE_D			=	./run/srcs/
ELSE_F			=	check_blt_func\
					check_cmd\
					check_delimiter\
					error_msg\
					run_blt\
					run_blt_cmd\
					run_cmd\
					run_execve_cmd\

ELSE_C			=	$(addsuffix .c, $(addprefix $(ELSE_D), $(ELSE_F)))
ELSE_O			=	$(addsuffix .o, $(addprefix $(ELSE_D), $(ELSE_F)))


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
