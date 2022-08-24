/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
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

void	begin_end_with_separator(char *line)
{
	int		max;
	char	*str;
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		exit(EXIT_FAILURE);
	str = join_the_split(split);
	if (line[0] == '|')
		print_s_error(line[0], 0, 0, 258);
	max = ft_strlen(str) - 1;
	if (is_metachar(str[max]))
		print_s_error(0, 0, "newline", 258);
	else if (str[max - 1] && (str[max - 1] == '<'
							  || str[max - 1] == '>') && is_metachar(str[max]))
		print_s_error(str[max], 0, 0, 258);
	ft_free_split(split);
}

int	syntax_error(char *line)
{
	if (begin_end_with_separator(line))
		return (1);

	return (0);
}