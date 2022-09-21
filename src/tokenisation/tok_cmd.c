/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:50:40 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/19 15:31:57 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_cmd(char *str, int i)
{
	int		y;
	char	*line;

	y = 0;
	if (!str)
		return (NULL);
	line = malloc(sizeof(char) * i + 1);
	protect_malloc(line);
	while (y < i)
	{
		line[y] = str[y];
		y++;
	}
	line[y] = '\0';
	return (line);
}

static int	manage_redirection_with_quotes(char **line_split, int i)
{
	while (line_split[i])
	{	
		if (line_split[i][0] == 39 && line_split[i + 1])
		{
			i++;
			while (line_split[i][0] == 39 && line_split[i + 1])
				i++;
		}
		if (line_split[i][0] == 34 && line_split[i + 1])
		{
			i++;
			while (line_split[i][0] == 34 && line_split[i + 1])
				i++;
		}
		if (ft_strcmp(line_split[i], GREAT) && ft_strcmp(line_split[i], DGREAT)
			&& ft_strcmp(line_split[i], LESS)
			&& ft_strcmp(line_split[i], DLESS))
			i++;
		else
			break ;
	}
	return (i);
}

int	tok_1(char **tok, char **line_split, int i, char *line)
{
	char	*tmp;
	char	*start;
	char	*end;
	int		i_end;

	end = NULL;
	start = ft_strdup(line_split[i]);
	tmp = ft_strstr(line, start);
	i = manage_redirection_with_quotes(line_split, i);
	if (line_split[i])
		end = ft_strdup(line_split[i]);
	if (end && i != 0)
		i_end = ft_strpstr(tmp, end);
	else
		i_end = ft_strlen(line);
	tok[1] = get_cmd(tmp, i_end);
	return (i);
}
