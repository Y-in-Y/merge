#include "minishell.h"

char	*ft_strdup(char *str)
{
	char	*result;
	int		len;
	int		i;

	if (!str)
		return (0);
	len = ft_strlen(str);
	result = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
