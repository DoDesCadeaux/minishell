/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 03:30:38 by pamartin          #+#    #+#             */
/*   Updated: 2021/12/10 03:30:41 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    argc++;
    int i;
    i = 0;

    printf("my   ---> %zu \n", ft_strlen(argv[1]));
    printf("real ---> %lu \n", strlen(argv[1]));
}*/
