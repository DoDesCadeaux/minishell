/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Verdoodt <Verdoodt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:23:51 by tverdood          #+#    #+#             */
/*   Updated: 2022/01/24 12:26:33 by Verdoodt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_print_string(char *str)
{
	int	char_count;

	char_count = 0;
	if (!str)
		str = "(null)";
	char_count = ft_putstr_and_count(str);
	return (char_count);
}
