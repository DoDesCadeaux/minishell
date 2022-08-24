#include "../include/minishell.h"

char	*str_dup_parts(char *src, int end, int start)
{
	char	*duplicate;
	int		i;

	if ((end - start) <= 0)
		return (NULL);
	duplicate = malloc(sizeof(char) * (end - start) + 1);
	if (!duplicate)
		return (NULL);
	i = 0;
	while (src && start - 1 < end)
	{
		duplicate[i] = src[start];
		i++;
		start++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

char	*join_and_replace(t_struct *data, char *tmp_1, char *to_replace, char *tmp_3)
{
	char	*dst;
	char	*tmp_dollar;
	int		i;

	tmp_dollar = var_exist(data, to_replace);
    if (tmp_dollar)
	{
        i = 0;
		while (tmp_dollar[i] != '=' && tmp_dollar[i])
			i++;
        i++;
		tmp_dollar = str_dup_parts(tmp_dollar, ft_strlen(tmp_dollar), i);
		dst = ft_strjoin(tmp_1, tmp_dollar);
        dst = ft_strjoin(dst, tmp_3);
	}
	else
		dst = ft_strjoin(tmp_1, tmp_3);
    free(tmp_dollar);
	return (dst);
}

char	*parsing_dollar(t_struct *data, char *line_to_pars)
{
	int		i;
	int		y;
    int     z;
	char	*tmp_1;
	char	*tmp_2;
	char	*tmp_3;

	i = 0;
	while (line_to_pars[i])
	{
		if (line_to_pars[i] == '$')
		{
            z = i;
            tmp_1 = str_dup_parts(line_to_pars, i - 1, 0);
			y = i + 1;
			while (line_to_pars[i] != ' ' && line_to_pars[i])
				i++;
            tmp_2 = str_dup_parts(line_to_pars, i - 1, y);
            y = i;
			while (line_to_pars[i])
				i++;
            if (i - y > 0)
                tmp_3 = str_dup_parts(line_to_pars, i - 1, y);
            else
                tmp_3 = ft_strdup("");

            if (var_exist(data, tmp_2))
                line_to_pars = join_and_replace(data, tmp_1, tmp_2, tmp_3);
			free(tmp_1);
            free(tmp_2);
            free(tmp_3);
            i = z;
        }
		i++;
	}
	return(line_to_pars);
}