/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 20:00:21 by pamartin          #+#    #+#             */
/*   Updated: 2021/12/17 20:00:22 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return ((void *)str);
}

/*
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    argc++;

    printf("my   memset --> %s \n", ft_memset(argv[1], atoi(argv[2]),
		atoi(argv[3])));
	printf("real memset --> %s \n", memset(argv[1], atoi(argv[2]),
		atoi(argv[3])));
}*/