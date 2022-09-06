#include "../../include/minishell.h"

static int	in_quote_str_len(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == 39 && line[i + 1])
		{
			i++;
			while (line[i] != 39)
			{
				j++;
				i++;
			}
		}
		i++;
	}
	return (j);
}

static int		check_if_open_quotes(char *line)
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

char	*single_quote(char *line)
{
	int	i;
	int	j;
	char *string_in_quote;

	if (check_if_open_quotes(line))
	{
		printf("ERROR : close single quotes\n");
		return (NULL);
	}
	string_in_quote = malloc(sizeof(char) * in_quote_str_len(line) + 1);
	if (!string_in_quote)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == 39 && line[i + 1])
		{
			i++;
			while (line[i] != 39 && line[i])
			{
				string_in_quote[j] = line[i];
				j++;
				i++;
			}
		}
		i++;
	}
	string_in_quote[i] = '\0';
	printf("line=%s\n", string_in_quote);
	return (string_in_quote);
}

//while (line[i])
//{
//	if (line[i] == 39)
//		i++;
//	string_in_quote[j] = line[i];
//	j++;
//	i++;
//}