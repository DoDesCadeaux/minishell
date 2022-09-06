#include "../../include/minishell.h"

static char 	*add_space(char *line, int i)
{
	char *tmp1;
	char *tmp2;
	char *str;

	tmp1 = str_dup_parts(line, i, 0);
	tmp2 = str_dup_parts(line, ft_strlen(line), i + 1);
	tmp1 = ft_strjoin(tmp1, " ");
	str = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (str);
}

static char 	*check_spaces_redirections(char *line_to_pars)
{
	int 	i;

	i = 0;
	while (line_to_pars[i])
	{
		if (line_to_pars[i] == 39 || line_to_pars[i] == 34)
			i = skip_all_quotes(line_to_pars, i);
		if (line_to_pars[i] == '<' || line_to_pars[i] == '>')
			if (line_to_pars[i + 1] != ' ')
				line_to_pars = add_space(line_to_pars, i);
		i++;
	}
	return (line_to_pars);
}

char 	*parsing(char *line, t_struct *data)
{
	line = parsing_dollar(data, line);
	line = check_spaces_redirections(line);
	return (line);
}