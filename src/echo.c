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

#include "../include/minishell.h"

int	option_n(char **split_cmd)
{
	int	check;

	check = ft_strncmp("-n", split_cmd[1], 2);
	if (!check)
		return (1);
	return (0);
}

void	echo(char **parse)
{
	char	**split_cmd;
	int		i;

	i = 1;
	split_cmd = ft_split(parse[1], ' ');
	if (option_n(split_cmd) == 1)
		i++;
	while (split_cmd[i])
	{
		ft_putstr_fd(split_cmd[i], ft_atoi(parse[2]));
		i++;
		if (i != len_split(split_cmd))
			ft_putchar_fd(' ', ft_atoi(parse[2]));
	}
	if (option_n(split_cmd) == 0)
		ft_putchar_fd('\n', ft_atoi(parse[2]));
	ft_free_split(split_cmd);
}

