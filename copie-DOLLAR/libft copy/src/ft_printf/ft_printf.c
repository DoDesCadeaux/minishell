/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Verdoodt <Verdoodt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:15:14 by tverdood          #+#    #+#             */
/*   Updated: 2022/01/24 12:26:48 by Verdoodt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	ft_input_reader(va_list args, const char *input)
{
	int	i;
	int	char_count;

	i = 0;
	char_count = 0;
	while (input[i])
	{
		if (input[i] == '%' && input[i + 1])
		{
			if (ft_input_type(input[i + 1]))
				char_count += ft_print_var(input[i + 1], args);
			else if (input[i + 1])
				char_count += ft_putchar(input[i + 1]);
			i++;
		}
		else if (input[i] != '%')
			char_count += ft_putchar(input[i]);
		i++;
	}
	return (char_count);
}

int	ft_printf(const char *input, ...)
{
	va_list	ptr;
	int		char_count;

	char_count = 0;
	va_start(ptr, input);
	char_count = ft_input_reader(ptr, input);
	va_end(ptr);
	return (char_count);
}
