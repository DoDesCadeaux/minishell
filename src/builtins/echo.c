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

	if (!ft_strcmp(tok[1], "echo -n"))
		exit(EXIT_SUCCESS);
	i = ft_strqstr(tok[1], CMD) + 1;
	y = ft_strqstr(tok[1], OPTION) + 1;
	if (ft_strncmp(tok[1], "echo", ft_strlen(tok[1])))
	{
		if (y == 0)
			line = ft_strdup(tok[1] + i);
		else
			line = ft_strdup(tok[1] + y + 1);
		printf("%s", line);
		free(line);
	}
	if (y == 0)
		printf("\n");
	exit(EXIT_SUCCESS);
}
