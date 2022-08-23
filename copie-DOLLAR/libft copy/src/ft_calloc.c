/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tverdood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:19:40 by tverdood          #+#    #+#             */
/*   Updated: 2022/01/07 18:20:26 by tverdood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*ptr_memory;

	ptr_memory = malloc(count * size);
	if (!ptr_memory)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		ptr_memory[i] = 0;
		i++;
	}
	return (ptr_memory);
}
