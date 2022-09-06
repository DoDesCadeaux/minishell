#include "../../include/minishell.h"

int		check_if_open_quotes(char *line)
{
	int i;
	int count_quotes;

	count_quotes = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 39)
			count_quotes++;
		i++;
	}
	if (count_quotes % 2 != 0)
		return (1);
	return (0);
}