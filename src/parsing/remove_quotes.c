#include "../../include/minishell.h"

static char	*remove_quote(char *line, int i)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = str_dup_parts(line, i - 1, 0);
	tmp2 = str_dup_parts(line, ft_strlen(line), i + 1);
	line = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (line);
}

int		increment_i_double(char *line, int i)
{
	i++;
	while (line[i] != 34 && line[i])
		i++;
	if (line[i] == 34 && line[i])
		i--;
	return (i);
}

int		increment_i_single(char *line, int i)
{
	i++;
	while (line[i] != 39 && line[i])
		i++;
	if (line[i] == 39 && line[i])
		i--;
	return (i);
}

char 	*remove_double(char *line, int i)
{
	line = remove_quote(line, i);
	while (line[i] != 34 && line[i])
		i++;
	if (line[i] == 34 && line[i])
	{
		line = remove_quote(line, i);
		i--;
	}
	return (line);
}

char 	*remove_single(char *line, int i)
{
	line = remove_quote(line, i);
	while (line[i] != 39 && line[i])
		i++;
	if (line[i] == 39 && line[i])
	{
		line = remove_quote(line, i);
		i--;
	}
	return (line);
}

char	*remove_quotes(char *line)
{
	char *new_line = ft_strdup(line);
	int i = 0;
	int j = 0;
	char quote = 0;
	while(line[i])
	{
		if (line[i] == quote)
			quote = 0;
		else if (!quote && (line[i] == '\'' || line[i] == '\"'))
			quote = line[i];
		else
		{
			new_line[j] = line[i];
			j++;
		}
		i++;
	}
	new_line[j] = 0;
	free(line);
	return (new_line);
}