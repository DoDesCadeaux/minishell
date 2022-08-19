/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduraku <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:26:40 by dduraku           #+#    #+#             */
/*   Updated: 2022/08/19 15:26:43 by dduraku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv)
{
	int		i;
	int		j;
	int		k;
	char	*string_in_quote;

	i = 1;
	j = 0;
	k = 0;

	string_in_quote = malloc(sizeof (char *) * ft_strlen(argv[i]) + 1);
	if (!string_in_quote)
		return (0);
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (argv[i][j] == 39)
				j++;
			else
			{
				string_in_quote[k] = argv[i][j];
				k++;
				j++;
			}
		}
		i++;
	}
	string_in_quote[k] = '\0';
	printf("String in single quotes : [%s]\n", string_in_quote);
	printf("ARGC %i\n", argc);
}