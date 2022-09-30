/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:44:29 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/30 12:44:31 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**check_dless(char **line_split, int i)
{
	while (line_split[i])
	{
		if (!ft_strcmp(line_split[i], DLESS))
		{
			free(line_split[i + 1]);
			line_split[i + 1] = ft_strdup("here_doc");
			i++;
		}
		i++;
	}
	return (line_split);
}

int	nb_of_redir(char **line_split, int i)
{
	int nb;

	nb = 0;
	while (line_split[i])
	{
		if (is_less_redirection(line_split, i))
			nb++;
		i++;
	}
	return (nb);
}

char	*manage_one_redir(char **line_split, int i)
{
	char	*line;
	char	*tmp;
//	int		cible;

	//cible = 0;
	line = NULL; //
	while (line_split[i])
	{
		if (!ft_strcmp(line_split[i], DLESS))
		{
			free(line_split[i]);
			line_split[i] = ft_strdup(" ");
			if (line_split[i + 1] && line_split[i + 2])
			{
				free(line_split[i + 1]);
				line_split[i + 1] = ft_strdup(" ");
			}
			else if (line_split[i + 1] && !line_split[i + 2])
			{
				free(line_split[i + 1]);
				line_split[i + 1] = ft_strdup("here_doc");
			}
		}
		if (!ft_strcmp(line_split[i], LESS))
		{
			free(line_split[i]);
			line_split[i] = ft_strdup(" ");
			if (line_split[i + 1])
			{
				if (access(line_split[i + 1], F_OK) == 0)
				{
					if (line_split[i + 2])
					{
						free(line_split[i + 1]);
						line_split[i + 1] = ft_strdup(" ");
					}
				}
				else
				{
					line = ft_strjoin(line_split[0]," ");
					tmp = ft_strjoin(line, line_split[i + 1]);
					free(line);
					ft_free_split(line_split);
					printf("tmp = %s\n", tmp);
					return (tmp);
				}
			}
		}
		i++;
	}
	i = 0;
	while (line_split[i])
	{
		printf("split %d : %s\n", i, line_split[i]);
		i++;
	}
	line = reverse_split(line_split, " ");
	//ft_free_split(line_split);
	return (line);
}

char	*manage_multi_redir(char **line_split, int i)
{
	char	*line;
	char	*tmp;

	line = NULL; //
	while (line_split[i])
	{
		if (!ft_strcmp(line_split[i], DLESS))
		{
			free(line_split[i]);
			line_split[i] = ft_strdup(" ");
			if (line_split[i + 1] && there_is_a_less_redirection(line_split, i + 1))
			{
				free(line_split[i + 1]);
				line_split[i + 1] = ft_strdup(" ");
			}
			else
			{
				free(line_split[i + 1]);
				line_split[i + 1] = ft_strdup("here_doc");
			}
		}
		if (!ft_strcmp(line_split[i], LESS))
		{
			free(line_split[i]);
			line_split[i] = ft_strdup(" ");
			if (line_split[i + 1])
			{
				if (access(line_split[i + 1], F_OK) == 0)
				{
					if (line_split[i + 2])
					{
						free(line_split[i + 1]);
						line_split[i + 1] = ft_strdup(" ");
					}
				}
				else
				{
					line = ft_strjoin(line_split[0]," ");
					tmp = ft_strjoin(line, line_split[i + 1]);
					free(line);
					ft_free_split(line_split);
					printf("tmp = %s\n", tmp);
					return (tmp);
				}
			}
		}
		i++;
	}
	i = 0;
	while (line_split[i])
	{
		printf("split %d : %s\n", i, line_split[i]);
		i++;
	}
	line = reverse_split(line_split, " ");
	//ft_free_split(line_split);
	return (line);

}

char	*parsing_redirstdin(char *line)
{
	char 	**line_split;
	char 	*new_line;
	int		i;
	int		nb;

	new_line = NULL; //
	line_split = ft_split_pipe(line, ' ');
	i = 0;
	line_split = check_dless(line_split, i);
	nb = nb_of_redir(line_split, i);
	printf("nb = %d\n", nb);
	if (nb == 0)
	{
		ft_free_split(line_split);
		return (line);
	}
	if (nb == 1)
		new_line = manage_one_redir(line_split, i);
	if (nb > 1)
		new_line = manage_multi_redir(line_split, i);
	ft_free_split(line_split);
	return (new_line);
}