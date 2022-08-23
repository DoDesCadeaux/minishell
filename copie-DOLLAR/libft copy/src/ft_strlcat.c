/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tverdood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:31:25 by tverdood          #+#    #+#             */
/*   Updated: 2022/01/14 12:03:26 by tverdood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

size_t	ft_strlcat(char *s1, const char *s2, size_t n)
{
	size_t	size_s1;
	size_t	size_s2;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if (n < size_s1)
		return (size_s2 + n);
	else
	{
		s1 = s1 + size_s1;
		ft_strlcpy(s1, s2, n - size_s1);
		return (size_s1 + size_s2);
	}
}
