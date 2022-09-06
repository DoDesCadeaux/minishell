#include "../../include/minishell.h"

char *remove_double_quotes(char *line)
{
	int 	i;
	char 	*tmp1;
	char 	*tmp2;

	i = 0;
	while(line[i])
	{
		if (line[i] == 34)
		{
			tmp1 = str_dup_parts(line, i - 1, 0);
			tmp2 = str_dup_parts(line, ft_strlen(line), i + 1);
			line = ft_strjoin(tmp1, tmp2);
			free(tmp1);
			free(tmp2);
			i = 0;
		}
		i++;
	}
	return (line);
}