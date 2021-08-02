#include "minishell.h"

int	ft_isalpha(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

int	check_exit(char *line)
{
	int		i;
	int		j;
	char	result[10];

	if (!line)
		return (0);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (j < 9 && ft_isalpha(line[i]) == 1)
			result[j++] = line[i++];
	}
	result[j] = '\0';
	if (ft_strncmp(result, "exit", 5) == 1)
		return (1);
	return (0);
}
