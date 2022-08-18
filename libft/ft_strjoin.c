/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 01:21:00 by pamartin          #+#    #+#             */
/*   Updated: 2021/12/24 01:21:03 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	y;
	char	*str;

	if (!s1 || !s2)
		return (0);
	i = 0;
	y = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (0);
	while (s1[i])
		str[y++] = s1[i++];
	i = 0;
	while (s2[i])
		str[y++] = s2[i++];
	str[y] = 0;
	return (str);
}

/*
#include <stdio.h>
int main(int argc, char **argv)
{
	argc++;
	printf("%s \n", ft_strjoin(argv[1], argv[2]));
}*/
