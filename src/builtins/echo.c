/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:41:43 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/16 18:13:49 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	echo(char **tok)
// {
// 	char	*line;
// 	int		i;
// 	int		y;

// 	if (!ft_strcmp(tok[1], "echo -n"))
// 		exit(EXIT_SUCCESS);
// 	i = ft_strqstr(tok[1], CMD) + 1;
// 	y = ft_strqstr(tok[1], OPTION) + 1;
// 	if (ft_strncmp(tok[1], "echo", ft_strlen(tok[1])))
// 	{
// 		if (y == 0)
// 			line = ft_strdup(tok[1] + i);
// 		else
// 			line = ft_strdup(tok[1] + y + 1);
// 		printf("%s", line);
// 		free(line);
// 	}
// 	if (y == 0)
// 		printf("\n");
// 	exit(EXIT_SUCCESS);
// }

int	skip_n(char *tok)
{
	int	i;

	i = 0;
	if (tok[i] == '-')
	{
		i++;
		while (tok[i] == 'n')
			i++;
	}
	if (tok[i] == ' ')
	{
		i++;
		if (tok[i] == '-')
			i += skip_n(tok + i);
	}
	else if (tok[i] == '\0')
		return (i);
	else
		return (0);
	return (i);
}

void	echo(char **tok)
{
	int	i;

	i = 5;
	if (!ft_strcmp(tok[1], "echo") || (!ft_strcmp(tok[1], "echo ")))
	{
		write(1, "\n", 1);
		exit(EXIT_SUCCESS);
	}
	if (!ft_strncmp(tok[1], "echo -n", 7))
		i += skip_n(tok[1] + 5);
	if (i <= 5)
		printf("%s\n", tok[1] + i);
	else
		printf("%s", tok[1] + i);
	exit(EXIT_SUCCESS);
}