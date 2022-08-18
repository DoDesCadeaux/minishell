/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 19:29:17 by pamartin          #+#    #+#             */
/*   Updated: 2021/12/17 19:29:19 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*str;

	if (n == 0)
		return (0);
	str = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return ((void *)(str + i));
		i++;
	}
	return (0);
}

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	argc++;

	printf("my   memchr   --->%s \n", ft_memchr(argv[1], atoi(argv[2]),
		atoi(argv[3])));
	printf("real memchr   --->%s \n", memchr(argv[1], atoi(argv[2]),
		atoi(argv[3])));

}*/
