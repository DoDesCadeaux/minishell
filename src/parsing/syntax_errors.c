#include "../../include/minishell.h"

static int		empty_line(char *line)
{
	if (*line == '\0')
		return (1);
	return (0);
}

static int		is_only_spaces(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'
		   || line[i] == '\v' || line[i] == '\f' || line[i] == '\r')
		i++;
	if (i == ft_strlen(line))
		return (1);
	return (0);
}

static int		open_quotes(char *line)
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

int 			syntax_errors(char *line)
{
	if (empty_line(line))
		return (1);
	if (is_only_spaces(line))
		return (1);
	if (open_quotes(line))
		return (1);
	return (0);
}
