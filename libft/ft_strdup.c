/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 23:08:49 by pamartin          #+#    #+#             */
/*   Updated: 2021/12/17 23:08:52 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*ft_cpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		len;

	len = ft_len(s1);
	dup = (char *)malloc(sizeof(*dup) * (len + 1));
	if (!dup)
		return (0);
	dup = ft_cpy((char *)dup, (char *)s1);
	return (dup);
}

/*
#include <stdio.h>

int main(int argc, char **argv)
{
    argc++;
    printf("my   strdup   --->%s \n", ft_strdup(argv[1]));
	printf("real strdup   --->%s \n", strdup(argv[1]));
}*/