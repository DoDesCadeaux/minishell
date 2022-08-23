/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tverdood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:54:36 by tverdood          #+#    #+#             */
/*   Updated: 2022/01/05 18:59:48 by tverdood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*p_dest;
	char	*p_src;

	i = len;
	p_dest = (char *)dst;
	p_src = (char *)src;
	if (dst == src)
		return (dst);
	if (dst > src)
	{
		while (i-- > 0)
			*(p_dest + i) = *(p_src + i);
		return (dst);
	}
	else
	{
		while (i-- > 0)
			*p_dest++ = *p_src++;
	}
	return (dst);
}
