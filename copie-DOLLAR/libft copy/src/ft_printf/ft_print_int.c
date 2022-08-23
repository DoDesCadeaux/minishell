/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Verdoodt <Verdoodt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:22:40 by tverdood          #+#    #+#             */
/*   Updated: 2022/01/24 12:26:39 by Verdoodt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_print_int(int nbr)
{
	char	*str;
	int		char_count;

	char_count = 0;
	str = ft_itoa(nbr);
	char_count = ft_putstr_and_count(str);
	if (str)
		free(str);
	return (char_count);
}
