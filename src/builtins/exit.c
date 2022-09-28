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
		printf("exit: %s : numeric argument required\n", numbers);
		return (2);
	}
	return (ft_long_atoi(numbers));
}

int	exit_builtins(char *line)
{
	long	exit_value;

	exit_value = ft_return_nbr(line);
	if (exit_value >= LONG_MAX)
	{
		printf("exit: %li : numeric argument required\n", exit_value);
		exit(2);
	}
	else
		printf("exit\n");
	exit(exit_value);
}
