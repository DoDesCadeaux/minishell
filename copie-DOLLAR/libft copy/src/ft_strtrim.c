/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tverdood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:22:36 by tverdood          #+#    #+#             */
/*   Updated: 2022/01/12 12:04:18 by tverdood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	is_charset(char c, const char *charset)
{
	int		i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_trim_right(char const *s1, char const *set, int trim_left)
{
	int		i;
	int		trim_right;

	trim_right = 0;
	i = ft_strlen(s1) - 1;
	while (trim_left < (int)ft_strlen(s1) && is_charset(s1[i], set))
	{
		trim_right++;
		i--;
	}
	return (trim_right);
}

static int	ft_trim_left(char const *s1, char const *set)
{
	int		i;
	int		trim_left;

	trim_left = 0;
	i = 0;
	while (is_charset(s1[i], set))
	{
		trim_left++;
		i++;
	}
	return (trim_left);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*str;
	int		len;
	int		trim_left;
	int		trim_right;

	if (!s1)
		return (0);
	trim_left = ft_trim_left(s1, set);
	trim_right = ft_trim_right(s1, set, trim_left);
	len = ft_strlen(s1) - trim_left - trim_right;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s1[trim_left];
		i++;
		trim_left++;
	}
	str[i] = '\0';
	return (str);
}
