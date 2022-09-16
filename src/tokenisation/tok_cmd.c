/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:50:40 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/15 18:50:42 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_cmd(char *str, int i)
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

int	manage_quote_status(int quote)
{
	if (quote == 1)
		quote = 0;
	else
		quote = 1;
	return (quote);
}

int	manage_redirection_with_quotes(char **line_split, int i)
{
	int		quote_simple;
	int		quote_double;

	quote_simple = 0;
	quote_double = 0;
	while (line_split[i])
	{	
		if (line_split[i][0] == 39)
		{
			quote_simple = manage_quote_status(quote_simple);
			i++;
		}
		if (line_split[i][0] == 34)
		{
			quote_double = manage_quote_status(quote_double);
			i++;
		}
		if (ft_strcmp(line_split[i], GREAT) && ft_strcmp(line_split[i], DGREAT))
			i++;
		else if (quote_simple == 1 || quote_double == 1)
			i++;
		else
			break ;
	}
	return (i);
}

int	tok_1(char **tok, char **line_split, int i, char *line)
{
	char	*info;
	char	*tmp;
	char	*start;
	char	*end;
	int		i_end;

	end = NULL;
	info = NULL;
	start = ft_strdup(line_split[i]);
	tmp = ft_strstr(line, start);
	i = manage_redirection_with_quotes(line_split, i);
	if (line_split[i])
		end = ft_strdup(line_split[i]);
	if (end)
		i_end = ft_strpstr(tmp, end);
	else
		i_end = ft_strlen(line);
	info = get_cmd(tmp, i_end);
	tok[1] = ft_strdup(info);
	free(info);
	tok[1] = remove_multi_space(tok[1]);
	return (i);
}
