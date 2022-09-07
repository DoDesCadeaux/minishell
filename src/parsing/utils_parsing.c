/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                      :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:32:28 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 13:32:31 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	*str_dup_parts(char *src, int end, int start)
{
	char	*duplicate;
	int		i;

	if ((end - start) <= 0)
		return (ft_strdup(""));
	duplicate = malloc(sizeof(char) * (end - start) + 1);
	if (!duplicate)
		return (NULL);
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

int	skip_single_quotes(char *line, int i)
{
	if (line[i] == 39)
	{
		i++;
		while (line[i] != 39 && line[i])
			i++;
		i++;
	}
	return (i);
}

int	skip_all_quotes(char *line, int i)
{
	i++;
	while (line[i] != 39 && line[i] != 34 && line[i])
		i++;
	i++;
	return (i);
}
