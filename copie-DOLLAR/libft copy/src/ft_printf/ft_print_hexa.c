/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Verdoodt <Verdoodt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:21:22 by tverdood          #+#    #+#             */
/*   Updated: 2022/01/24 12:26:41 by Verdoodt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static void	ft_hexa(unsigned int nb, char type)
{
	if (nb >= 16)
	{
		ft_print_hexa((nb / 16), type);
		ft_print_hexa((nb % 16), type);
	}
	else
	{
		if (nb < 10)
			ft_putchar_fd((nb + '0'), 1);
		else if (type == 'x')
			ft_putchar_fd((nb - 10 + 'a'), 1);
		else if (type == 'X')
			ft_putchar_fd((nb - 10 + 'A'), 1);
	}
}

int	ft_print_hexa(unsigned int nb, char type)
{
	int	char_count;

	ft_hexa(nb, type);
	char_count = hexa_len(nb);
	return (char_count);
}
