/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 19:27:40 by pamartin          #+#    #+#             */
/*   Updated: 2021/12/31 19:27:42 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	y;

	i = 0;
	while (src[i])
		i++;
	if (dstsize == 0)
		return (i);
	y = 0;
	while (src[y] && y < (dstsize - 1))
	{
		dst[y] = src[y];
		y++;
	}
	dst[y] = '\0';
	return (i);
}
