/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions_supp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Verdoodt <Verdoodt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:20:57 by tverdood          #+#    #+#             */
/*   Updated: 2022/01/24 12:26:45 by Verdoodt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_input_type(char c)
{
	if (c == 'd' || c == 'i' || c == 'u' || c == 'p' || c == 'x'
		|| c == 'X' || c == 'c' || c == 's' || c == '%')
		return (1);
	else
		return (0);
}

int	ft_putchar(int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_putstr_and_count(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int	hexa_len(unsigned long long int nb)
{
	int	char_count;

	char_count = 0;
	while (nb >= 16)
	{
		nb = (nb / 16);
		char_count++;
	}
	return (++char_count);
}
