/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:41:43 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/05 18:41:45 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	echo(char **tok)
{
	char	*line;
	int		i;
	int		y;

	i = ft_strqstr(tok[1], CMD) + 1;
	y = ft_strqstr(tok[1], OPTION) + 1;
	//logique magique de dorian pour le potentiel faux -n
	if (y == 0)
		line = ft_strdup(tok[1] + i);
	else
		line = ft_strdup(tok[1] + y);
	printf("%s", line);
	if (y == 0)
		printf("\n");
	free(line);
	exit(EXIT_SUCCESS);
}
