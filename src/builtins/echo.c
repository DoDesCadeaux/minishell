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

int	option_n(char **split_cmd)
{
	int	check;

	check = ft_strncmp("-n", split_cmd[1], 2);
	if (!check)
		return (1);
	return (0);
}

void	echo(char **tok)
{
	char	**split_cmd;
	int		i;

	i = 1;
	split_cmd = ft_split(tok[1], ' ');
	if (option_n(split_cmd) == 1)
		i++;
	while (split_cmd[i])
	{
		printf("%s", split_cmd[i]);
		i++;
		if (i != len_split(split_cmd))
			printf(" ");
	}
	if (option_n(split_cmd) == 0)
		printf("\n");
	ft_free_split(split_cmd);
	exit(EXIT_SUCCESS);
}
