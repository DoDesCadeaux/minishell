/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 23:10:43 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/13 23:10:46 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_single_quotes(char *line)
{
	int		i;
	char	*tmp1;
	char	*tmp2;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39)
		{
			tmp1 = str_dup_parts(line, i - 1, 0);
			tmp2 = str_dup_parts(line, ft_strlen(line), i + 1);
			line = ft_strjoin(tmp1, tmp2);
			free(tmp1);
			free(tmp2);
			i = 0;
			continue ;
		}
		i++;
	}
	return (line);
}
