CC = gcc

CFLAGS = -Wall -Wextra -Werror

RL_FLAG = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
#RL_FLAG = -lreadline -I /usr/include/readline/include

TC_FLAG = -ltermcap

FSNTZ = -fsanitize=address

NAME = minishell

LIB = minishell.a

SRCS = main.c

all : $(NAME)

$(NAME) :
	$(MAKE) -C ./srcs
	cp ./srcs/$(LIB) ./
	$(CC) $(CFLAGS) -Iinclude $(SRCS) $(LIB) -o $(NAME) $(RL_FLAG) $(TC_FLAG) $(FSNTZ)

clean :
	$(MAKE) clean -C ./srcs
	rm -f $(LIB)

fclean : clean
	$(MAKE) fclean -C ./srcs
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
