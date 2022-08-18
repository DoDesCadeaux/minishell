/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 17:20:25 by pamartin          #+#    #+#             */
/*   Updated: 2021/12/31 17:20:28 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*my_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst_tempo;
	char	*src_tempo;
	size_t	i;

	if (!dst && !src)
		return (0);
	dst_tempo = (char *)dst;
	src_tempo = (char *)src;
	i = 0;
	while (i < n)
	{
		dst_tempo[i] = src_tempo[i];
		i++;
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_tempo;
	char	*src_tempo;

	dst_tempo = (char *)dst;
	src_tempo = (char *)src;
	if (!dst && !src)
		return (0);
	if (src > dst)
		my_memcpy(dst, src, len);
	else
	{
		while (len > 0)
		{
			dst_tempo[len - 1] = src_tempo[len - 1];
			len--;
		}
	}
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    printf("my memmove   : %s \n", ft_memmove(argv[1], argv[2], atoi(argv[3])));
    printf("real memmove : %s \n", memmove(argv[1], argv[2], atoi(argv[3])));

	char dst1[0xF0];
	char dst2[0xF0];
	char *data = "thiß ß\xde\xad\xbe\xeftriñg will be øvérlapéd !\r\n";
	int size = 0xF0 - 0xF;

	printf("my memmove   : %s \n", ft_memmove(dst2 + 3, dst1, size));
    printf("real memmove : %s \n", memmove(dst2 + 3, dst1, size));
}*/
