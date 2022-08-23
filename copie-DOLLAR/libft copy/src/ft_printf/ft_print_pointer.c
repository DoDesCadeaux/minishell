/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Verdoodt <Verdoodt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:23:25 by tverdood          #+#    #+#             */
/*   Updated: 2022/01/24 12:26:35 by Verdoodt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static void	ft_print_ptr(unsigned long long int ptr)
{
	if (ptr >= 16)
	{
		ft_print_ptr(ptr / 16);
		ft_print_ptr(ptr % 16);
	}
	else
	{
		if (ptr < 10)
			ft_putchar_fd((ptr + '0'), 1);
		else
			ft_putchar_fd(ptr - 10 + 'a', 1);
	}
}

int	ft_print_pointer(unsigned long long int ptr)
{
	int	char_count;

	char_count = write(1, "0x", 2);
	ft_print_ptr(ptr);
	char_count += hexa_len(ptr);
	return (char_count);
}
