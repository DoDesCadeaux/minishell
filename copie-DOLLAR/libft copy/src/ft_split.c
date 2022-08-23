/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tverdood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:04:26 by tverdood          #+#    #+#             */
/*   Updated: 2022/01/12 12:03:32 by tverdood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_count_words(const char *str, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == c)
			i++;
		else
		{
			words++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (words);
}

static int	ft_word_length(const char *str, char c, int i)
{
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	ft_copy(char *dest, int i, const char *src, char c)
{
	int	j;

	j = 0;
	while (src[i] && src[i] != c)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (i);
}

static void	ft_free(char **matrice)
{
	int	i;

	i = 0;
	while (matrice[i])
	{
		free(matrice[i]);
		i++;
	}
	free(matrice);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		words;
	char	**matrice;

	if (!s)
		return (0);
	matrice = malloc(sizeof(char **) * (ft_count_words(s, c) + 1));
	if (!matrice)
		return (0);
	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			matrice[words] = malloc(ft_word_length(s, c, i) + 1);
			if (!matrice[words])
				ft_free(matrice);
			i = ft_copy(matrice[words++], i, s, c);
		}
		else
			i++;
	}
	matrice[words] = 0;
	return (matrice);
}
