/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 23:11:04 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/13 23:11:05 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	empty_line(char *line)
{
	if (*line == '\0')
		return (1);
	return (0);
}

static int	is_only_spaces(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'
		|| line[i] == '\v' || line[i] == '\f' || line[i] == '\r')
		i++;
	if (i == ft_strlen(line))
		return (1);
	return (0);
}

static int	open_quotes(char *line)
{
	int	i;
	int	count_quotes;

	count_quotes = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 39)
			i = skip_single_quotes(line, i);
		else if (line[i] == 34)
			i = skip_double_quotes(line, i);
		i++;
	}
	if (count_quotes % 2 != 0)
		return (1);
	return (0);
}

static int	begin_or_end_with_pipe(char *line)
{
	int	i;
	int	max;

	i = 0;
	if (is_metachar(line[i]))
		return (1);
	max = ft_strlen(line);
	if (is_metachar(line[max]))
		return (1);
	return (0);
}

int	syntax_errors(char *line)
{
	if (empty_line(line))
	{
		ft_error("Syntax error : empty line", 1);
		return (1);
	}
	if (is_only_spaces(line))
	{
		ft_error("Syntax error : there's only spaces", 1);
		return (1);
	}
	if (open_quotes(line))
	{
		ft_error("Syntax error : open quotes", 1);
		return (1);
	}
	if (begin_or_end_with_pipe(line))
	{
		ft_error("Syntax error : Begins or ends with a pipe", 1);
		return (1);
	}
	return (0);
}
