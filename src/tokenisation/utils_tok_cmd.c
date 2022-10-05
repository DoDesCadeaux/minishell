/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tok_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:51:25 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/19 06:35:50 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*add_space(char *tmp, char *new_line)
{
	tmp = ft_strjoin(new_line, " ");
	free(new_line);
	return (tmp);
}

static char	**malloc_and_free(char *line)
{
	char	**array;

	array = ft_split_pipe(line, ' ');
	protect_malloc(array);
	free(line);
	return (array);
}

char	*remove_multi_space(char *line)
{
	char	**split_space;
	int		i;
	char	*new_line;
	char	*tmp;

	split_space = malloc_and_free(line);
	i = 1;
	new_line = ft_strdup(split_space[0]);
	tmp = NULL;
	if (split_space[i])
		tmp = add_space(tmp, new_line);
	else
	{
		ft_free_split(split_space);
		return (new_line);
	}
	while (split_space[i])
	{
		new_line = ft_strjoin(tmp, split_space[i]);
		free(tmp);
		if (split_space[i + 1])
			tmp = add_space(tmp, new_line);
		else
		{
			ft_free_split(split_space);
			return (new_line);
		}
		i++;
	}
	free(new_line);
	ft_free_split(split_space);
	return (tmp);
}

void	protect(void)
{
	perror("minishell: ");
	exit(EXIT_FAILURE);
}
