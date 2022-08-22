#include "../include/minishell.h"

size_t	ft_strlen(const char *s) //inchange
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}



char	*str_dup_parts(char *src, int end, int start) //modifie
{
	char	*duplicate;
	int		i;

	if ((end - start) <= 0)
		return (NULL);
	duplicate = malloc(sizeof(char) * (end - start) + 1);
	if (!duplicate)
		return (NULL);
	i = 0;
	while (src && start - 1 < end)	// a calculer si erreur
	{
		duplicate[i] = src[start];
		i++;
		start++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
    size_t  i;
    size_t  y;
    char    *str;

    if (!s1 || !s2)
        return (0);
    i = 0;
    y = 0;
    str = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!str)
        return (0);
    while (s1[i])
        str[y++] = s1[i++];
    i = 0;
    while (s2[i])
        str[y++] = s2[i++];
    str[y] = 0;
    return (str);
} //inchange

char    *var_exist(char **envp, char *variable) //simplifie
{
    int     i;
    char    *tmp;

    tmp = ft_strjoin(variable, "=");
    i = 0;
    while (envp[i])
    {
        if (!ft_strncmp(envp[i], tmp, ft_strlen(tmp)))
        {
            free(tmp);
            return (envp[i]);
        }
        i++;
    }
    free(tmp);
    return (NULL);
}

char	*join_and_replace(t_struct *data, char *tmp_1, char *to_replace, char *tmp_3)
{
	char	*dst;
	char	*tmp_dollar;
	int		i;

	tmp_dollar = var_exist(data->envp, to_replace);
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
	char	*tmp_1;
	char	*tmp_2;
	char	*tmp_3;

	i = 0;
	while (line_to_pars[i])
	{
		if (line_to_pars[i] == '$')
		{
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

            printf("\ntmp1 = %s\ntmp2 = %s\ntmp3 = %s\n\n", tmp_1, tmp_2, tmp_3);
            if (var_exist(data->envp, tmp_2))
			    line_to_pars = join_and_replace(data, tmp_1, tmp_2, tmp_3);
            else
                printf("TO DO? --> TESTER\n");
			free(tmp_1);
			free(tmp_2);
			free(tmp_3);
		}
		i++;
	}
	return(line_to_pars);
}