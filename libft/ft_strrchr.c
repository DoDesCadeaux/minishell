/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:33:22 by pamartin          #+#    #+#             */
/*   Updated: 2021/12/16 18:33:25 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (0);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	argc++;

	printf("my   strchr   --->%s \n", ft_strrchr(argv[1], atoi(argv[2])));
	printf("real strchr   --->%s \n", strrchr(argv[1], atoi(argv[2])));

}*/
