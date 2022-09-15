/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:59:44 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/15 13:59:46 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
			while (str[i])
			{
				if (str[i] == 34)
				{
					i++;
					while (str[i] != 34)
						i++;
				}
				if (str[i] == 39)
				{
					i++;
					while (str[i] != 39)
						i++;
				}
				if (str[i] != c)
					i++;
				if (str[i] == c)
					break ;
			}
		}
		else
			i++;
	}
	split = (char **)malloc(sizeof(char *) * (count + 1));
	return (split);
}

static int	ft_lenword(const char *str, char c, int i)
{
	int	y;
	int	z;

	y = i;
	while (str[i])
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] != 34)
				i++;
		}
		if (str[i] == 39)
		{
			i++;
			while (str[i] != 39)
				i++;
		}
		if (str[i] != c)
			i++;
		else
			break ;
	}
	z = i - y;
	return (z);
}

void	run_cpy(char *dest, char *str, int i, int j)
{
	dest[j] = str[i];
	i++;
	j++;
}

static int	ft_copy(char *dest, char *str, char c, int i)
{
	int	j;

	j = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			dest[j] = str[i];
			j++;
			i++;
			while (str[i] != 34)
			{
				dest[j] = str[i];
				j++;
				i++;
			}
		}
		if (str[i] == 39)
		{
			dest[j] = str[i];
			j++;
			i++;
			while (str[i] != 39)
			{
				dest[j] = str[i];
				j++;
				i++;
			}
		}
		if (str[i] != c)
		{
			dest[j] = str[i];
			i++;
			j++;
		}
		else
			break ;
	}
	dest[j] = '\0';
	return (i);
}

char	**ft_split_pipe(char *s, char c)
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
#include <stdio.h>

int main(void)
{
	int i;
	char **pipe;
	char c = '|';
	char *str="echo bonjour | '|' | 'echo blabla' | '|||'";

	pipe = ft_split(str, c);
	i = 0;
	while (pipe[i])
	{
		printf("line %d : -%s-\n", i, pipe[i]);
		i++;
	}
}
*/