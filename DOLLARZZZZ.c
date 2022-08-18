#include <stdio.h>
#include <stdlib.h>
# include <readline/readline.h>
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}



char	*str_dup_parts(char *src, int end, int start)
{
	char	*duplicate;
	int		i;

	if ((end - start) == 0)
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
}

char    *var_exist(t_struct *data, char *variable)
{
    int     i;
    char    *tmp;

    tmp = ft_strjoin(variable, "=");
    i = 0;
    while (data->envp[i])
    {
        if (!ft_strncmp(data->envp[i], tmp, ft_strlen(tmp)))
        {
            free(tmp);
            return (data->envp[i]);
        }
        i++;
    }
    free(tmp);
    return (NULL);
}

char	*join_and_replace(t_struct *data, char *tmp_1, char *to_replace, char *tmp_3)
{
	char	*dst;
	char	*tmp;
	int		*i;

	//malloc tmp ?
	tmp = var_exist(data, to_replace); //tmp : tanguy=bg
	if (tmp)
	{
		i = 0;
		while (tmp[i] != '=')
			i++;
		i++;
		//free tmp avant de le ramplacer?
		tmp = str_dup_parts(tmp, ft_strlen(tmp), i);
		dst = ft_strjoin(tmp_1, tmp);
		dst = ft_strjoin(dst, tmp_3);
	}
	else
		dst = ft_strjoin(tmp1, tmp2);
	return (dst);
}

char	*parsing(t_struct *data, char *line_to_pars)
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
			tmp_1 = str_dup_parts(line_to_pars, i, 0);
			y = i + 1;
			while (line_to_pars[i] != ' ')
				i++;
			tmp_2 = str_dup_parts(line_to_pars, i, y);
			y = i;
			while (line_to_pars[i])
				i++;
			tmp_3 = str_dup_parts(line_to_pars, i, y);
			printf("tmp1 = %s\ntmp2 = %s\ntmp3 = %s\n", tmp_1, tmp_2, tmp_3);
			//free avant de le remplacer ?
			line_to_pars = join_and_replace(data, tmp1, tmp2, tmp3);
			free(tmp_1);
			free(tmp_2);
			free(tmp_3);
		}
		i++;
	}
//	free(tmp);
	return(line_to_pars);
}

int	main(int ac, char **av)
{
	char *line;
	char *tmp;

	tmp = str_dup_parts("okkkkkk", 0, 3);

	if (ac == 1)
		return(0);

		//printf("%s\n", av[i]);
		line = ft_strjoin(tmp, av[1]);
	
	parsing(line);
	return (0);
}