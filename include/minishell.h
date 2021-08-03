#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "parsing.h"
# include "builtin.h"
# include "function.h"
# include "multipipe.h"

# define PROMPT "nyanshell > "

typedef struct		s_env	t_env;
typedef struct		s_list	t_list;
typedef	struct		s_all	t_all;

#endif
