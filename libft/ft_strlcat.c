/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 19:39:40 by pamartin          #+#    #+#             */
/*   Updated: 2021/12/31 19:39:41 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (dstsize <= len_dst)
		return (len_src + dstsize);
	dst = dst + len_dst;
	ft_strlcpy(dst, src, dstsize - len_dst);
	return (len_src + len_dst);
}

/*
#include <stdio.h>

int main(int argc, char **argv)
{
    argc++;
    printf("my strlcat   : %lu \n", ft_strlcat(argv[1], argv[2], atoi(argv[3])));
    printf("real strlcat : %lu \n", strlcat(argv[1], argv[2], atoi(argv[3])));
}*/
