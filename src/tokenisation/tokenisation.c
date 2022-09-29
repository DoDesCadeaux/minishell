/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:49:46 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/26 18:15:55 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**tokenisation(char *line, char **tok, t_struct *data)
{
	char	**line_split;
	int		i;

	data->i_redir = 0;
	line_split = ft_split_pipe(line, ' ');
	i = 0;
	i = tok_fd_in(data, tok, line_split, i);
	if (i == len_split(line_split))
		return (NULL);
	while (data->i_redir != 0)
		i = tok_fd_in(data, tok, line_split, i);
	if (!tok[0])
		return (NULL);
	i = tok_1(tok, line_split, i, line);
	if (i < 0)
		return (NULL);
	i = tok_fd_out(data, tok, line_split, i);
	while (data->i_redir != 0)
		i = tok_fd_out(data, tok, line_split, i);
	tok[1] = parsing(tok[1], data);
	free(line);
	tok[3] = 0;
	ft_free_split(line_split);
	data->type = check_type(tok, data);
	return (tok);
}
