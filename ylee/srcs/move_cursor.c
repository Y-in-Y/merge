#include "minishell.h"

static int		ft_atoi(char *str)
{
	int		i;
	int		num;

	if (!str)
		return (-1);
	i = 0;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

int		putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void	move_to_prevline(int *row, int *col)
{
	char	*cm;
	int		p_len;

	*row = *row - 1;
	p_len = ft_strlen(PROMPT);
	*col = p_len;
	
	tgetent(NULL, getenv("TERM"));
	cm = tgetstr("cm", NULL);
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);
}

void	move_cursor(int *row, int *col)
{
	struct termios	term;
	char			buf[255];
	int				readlen;
	int				i;
	int				row_f;
	
	tcgetattr(0, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	write(0, "\033[6n", 4);
	readlen = read(0, buf, 254);
	buf[readlen] = '\0';
	i = 1;
	row_f = 0;
	while (buf[i])
	{
		if (row_f == 0 && buf[i] >= '0' && buf[i] <= '9')
		{
			*row = ft_atoi(&buf[i]) - 1;
			while (buf[i] >= '0' && buf[i] <= '9')
				i++;
			row_f = 1;
		}
		else if (row_f == 1 && buf[i] >= '0' && buf[i] <= '9')
		{
			*col = ft_atoi(&buf[i]) - 1;
			break ;
		}
		else if (buf[i] < 0 || buf[i] > '9')
			i++;
	}
	move_to_prevline(row, col);
}
