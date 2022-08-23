/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Verdoodt <Verdoodt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:24:25 by tverdood          #+#    #+#             */
/*   Updated: 2022/01/24 12:26:20 by Verdoodt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_print_var(char type, va_list args)
{
	int	char_count;

	char_count = 0;
	if (type == 'd' || type == 'i')
		char_count = ft_print_int(va_arg(args, int));
	if (type == 'c')
		char_count = ft_print_char(va_arg(args, int));
	if (type == 's')
		char_count = ft_print_string(va_arg(args, char *));
	if (type == '%')
		char_count = ft_print_pourcent();
	if (type == 'x' || type == 'X')
		char_count = ft_print_hexa(va_arg(args, unsigned int), type);
	if (type == 'u')
		char_count = ft_print_unsigned_int(va_arg(args, unsigned int));
	if (type == 'p')
		char_count = ft_print_pointer(va_arg(args, unsigned long long int));
	return (char_count);
}
