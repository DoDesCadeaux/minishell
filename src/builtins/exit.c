/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:43:18 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 14:43:47 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_return_nbr(char *line)
{
	int		i;
	int		j;
	int		tmp;
	char	*numbers;

	i = 0;
	j = 0;
	numbers = malloc(sizeof(char) * ft_strlen(line) + 1);
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			i++;
		else
		{
			numbers[j] = line[i];
			j++;
			i++;
		}
	}
	numbers[j] = '\0';
	if (ft_strlen(numbers) > 19 || ft_long_atoi(numbers) > 9223372036854775807)
	{
		ft_error(msg("exit", numbers, "numeric argument required"), JSP);
		free(numbers);
		return (2);
	}
	tmp = ft_long_atoi(numbers);
	return (tmp);
}

int	exit_builtins(char *line)
{
	long	exit_value;

	exit_value = ft_return_nbr(line);
	if (exit_value >= LONG_MAX)
	{
		ft_error(msg("exit", (char *)exit_value, "numeric argument required"), JSP);
		free(line);
		exit(2);
	}
	else
		printf("exit\n");
	free(line);
	exit(exit_value);
}
