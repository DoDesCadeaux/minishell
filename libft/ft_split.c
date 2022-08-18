/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 00:20:31 by pamartin          #+#    #+#             */
/*   Updated: 2021/12/26 00:20:33 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_count_words(char const *str, char c)
{
	int		count;
	int		i;
	char	**split;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	split = (char **)malloc(sizeof(char *) * (count + 1));
	return (split);
}

static int	ft_lenword(const char *str, char c, int i)
{
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	ft_copy(char *dest, const char *str, char c, int i)
{
	int	j;

	j = 0;
	while (str[i] && str[i] != c)
	{
		dest[j] = str[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		words;
	int		i;

	if (!s)
		return (0);
	split = ft_count_words(s, c);
	if (!split)
		return (0);
	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			split[words] = malloc(sizeof(char) * ft_lenword(s, c, i) + 1);
			if (!split[words])
				return (ft_free_split(split));
			i = ft_copy(split[words++], s, c, i);
		}
	}
	split[words] = 0;
	return (split);
}
/*
int main (void)
{
	char **c;

	c = NULL;

	c = malloc(sizeof(char *) * 4);
	ft_free(c);
	return (0);
}*/

/*
#include <stdio.h>
int main(void)
{
	int i;
	char **split;
	char c1, c2, c3, c4, c5;
	char	*str1, *str2, *str4, *str3, *str5;


	split = ft_split(str4, c4);
	i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
}*/