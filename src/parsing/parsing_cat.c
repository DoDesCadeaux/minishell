/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:32:28 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/27 16:59:16 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*

# include "stdio.h"

int	skip_single_quotes(char *line, int i)
{
	if (line[i] == 39)
	{
		i++;
		while (line[i] != 39 && line[i])
			i++;
	}
	return (i);
}

int	skip_double_quotes(char *line, int i)
{
	if (line[i] == 34)
	{
		i++;
		while (line[i] != 34 && line[i])
			i++;
	}
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	len1;
	int	len2;
	int	i;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 != len2)
		return (1);
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

char	*str_dup_parts(char *src, int end, int start)
{
	char	*duplicate;
	int		i;

	if ((end - start) <= 0)
		return (ft_strdup(""));
	duplicate = malloc(sizeof(char) * (end - start) + 1);
	i = 0;
	while (src[i] && start - 1 < end)
	{
		duplicate[i] = src[start];
		i++;
		start++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}
*/

/////////////////////////////////////

static int	find_cat(const char *haystack, const char *needle)
{
	int	i;
	int	y;

	i = 0;
	if (needle[i] == '\0')
		return (0);
	while (haystack[i])
	{
		y = 0;
		while (haystack[i + y] && (haystack[i + y] == needle[y]))
		{
			if (needle[y + 1] == '\0')
				if (haystack[i + y + 1] == ' ')
					return (i);
			y++;
		}
		i++;
	}
	return (0);
}

static char	*erase(char *line, int end_first_part, int start_second_part)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = str_dup_parts(line, end_first_part, 0);
	tmp2 = str_dup_parts(line, ft_strlen(line), start_second_part);
	line = ft_strjoin(tmp1, tmp2);
	return (line);
}

//static int	is_end_of_word(char *line, int i)
//{
//	if (!ft_isalpha(line[i + 1]))
//		return (1);
//	if (line[i + 1] == '\0')
//		return (1);
//	return (0);
//}

static char	*return_line(char *line, int start_cut, int i)
{
	if (line[i] == 34)
		i = skip_double_quotes(line, i);
	else
		i = skip_single_quotes(line, i);
	i++;
	if (line[i] == ' ')
		i++;
	line = erase(line, start_cut, i);
	return (line);
}

static char	*erase_redirection_and_following_word(char *line, int i)
{
	int	start_cut;

	start_cut = i - 1;
	i++;
	if (line[i] == ' ')
		i++;
	if (line[i] == 34 || line[i] == 39)
		return (return_line(line, start_cut, i));
	while (line[i])
	{
		if (!ft_isalpha(line[i + 1]) || line[i + 1] == '\0')
		{
			i += 1;
			line = erase(line, start_cut, i);
			return (line);
		}
		i++;
	}
	return (NULL);
}

char	*parsing_cat(char *line)
{
	int	i;

	i = find_cat(line, "cat");
	if (i > 0)
	{
		while (line[i])
		{
			if (is_a_less_redir(line, i))
			{
				line = erase_redirection_and_following_word(line, i);
				return (line);
			}
			i++;
		}
	}
	return (line);
}

/*
int 	main(int ac, char **av)
{
	ac = 667;
	char *line = av[1];
	line = parsing_cat(line);
	printf("LINE = %s\n", line);
	return (0);
}*/











/*
char	*manage_multi_redir(char **line_split, int i, int len, int nb)
{
	char	*line;
	char	*tmp;

	while (line_split[i])
	{
		if (!ft_strcmp(line_split[i], DLESS))
		{
			free(line_split[i]);
			line_split[i] = ft_strdup(" ");
			if (line_split[i + 1])
			{
				if (there_is_a_less_redirection(line_split, i + 1) || (!there_is_a_less_redirection(line_split, i + 1) && line_split[i + 2]) || i + 1 >= len - nb)
				{
					free(line_split[i + 1]);
					line_split[i + 1] = ft_strdup(" ");
				}
			}
		}
		if (!ft_strcmp(line_split[i], LESS))
		{
			free(line_split[i]);
			line_split[i] = ft_strdup(" ");
			if (line_split[i + 1])
			{
				if (access(line_split[i + 1], F_OK) == 0)
				{
					if (line_split[i + 2] || i + 1 >= len - nb)
					{
						free(line_split[i + 1]);
						line_split[i + 1] = ft_strdup(" ");
					}
				}
				else
				{
					line = ft_strjoin(line_split[0]," ");
					tmp = ft_strjoin(line, line_split[i + 1]);
					free(line);
					return (tmp);
				}
			}
		}
		i++;
	}
	i = 0;
	while(line_split[i])
	{
		printf("split %d : %s\n", i, line_split[i]);
		i++;
	}
	line = reverse_split(line_split, " ");
	return (line);

}*/