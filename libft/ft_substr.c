/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:03:27 by pamartin          #+#    #+#             */
/*   Updated: 2021/12/23 14:04:19 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(size_t size, size_t len, unsigned int start)
{
	if (size < start)
		len = 0;
	else if (start + len >= size)
		len = size - start;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			i;
	size_t			y;
	size_t			size;

	if (!s)
		return (0);
	size = ft_strlen(s);
	len = ft_len(size, len, start);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	i = 0;
	y = 0;
	while (s[i])
	{
		if (i >= start && y < len)
		{
			str[y] = s[i];
			y++;
		}
		i++;
	}
	str[y] = '\0';
	return (str);
}

/*#include <stdio.h>

int main (int argc, char **argv)
{
	argc++;
	printf("%s \n", ft_substr(argv[1], atoi(argv[2]), atoi(argv[3])));
}*/
