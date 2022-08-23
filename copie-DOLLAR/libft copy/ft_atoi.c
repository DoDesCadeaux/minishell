/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 03:30:23 by pamartin          #+#    #+#             */
/*   Updated: 2021/12/26 00:17:36 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_spacesigne(const char *str, int *signe, int *neg)
{
	int	i;

	i = 0;
	*neg = 0;
	*signe = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			*neg = 1;
		*signe += 1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	long		nb;
	int			signe;
	int			neg;
	int			i;

	if (!str)
		return (0);
	nb = 0;
	i = ft_spacesigne(str, &signe, &neg);
	if (signe > 1)
		return (0);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb *= 10;
		nb += str[i] - 48;
		i++;
		if (neg == 1 && nb > 2147483648)
			return (0);
		if (neg == 0 && nb > 2147483647)
			return (-1);
	}
	if (neg == 1)
		nb *= -1;
	return (nb);
}

/*
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	argc++;

	int my;
	int real;

	my = ft_atoi(argv[1]);
	real = atoi(argv[1]);

	printf ("my atoi   : %d\n", my);
	printf ("real atoi : %d\n", real);
}*/