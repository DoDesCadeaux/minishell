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
	char	*tmp;
	int		i;

	line_split = ft_split_pipe(line, ' ');
	i = 0;
	i = tok_fd_in(tok, line_split, i);
	if (i == len_split(line_split))
		return (NULL);
	i = tok_1(tok, line_split, i, line);
	if (data->i_redir != 0)
		i = data->i_redir;
	if (line_split[i] && !ft_strcmp(line_split[i], GREAT))
		tmp = get_fd(line_split[i + 1], REDIR_STDOUT, GREAT);
	else if (line_split[i] && !ft_strcmp(line_split[i], DGREAT))
		tmp = get_fd(line_split[i + 1], REDIR_STDOUT, DGREAT);
	else if (line_split[i] && !ft_strcmp(line_split[i], LESS))
		tmp = get_fd(line_split[i + 1], REDIR_STDIN, NULL);
	else
		tmp = get_fd(NULL, REDIR_STDOUT, NULL);
	tok[1] = parsing(tok[1], data);
	if (tmp)
		tok[2] = ft_strdup(tmp);
	else
		return (NULL);
	if (i < len_split(line_split) - 3)
		data->i_redir = i + 2;
	else
	{
		data->i_redir = 0;
		free(line);
	}
	tok[3] = 0;
	free(tmp);
	ft_free_split(line_split);
	data->type = check_type(tok, data);
	return (tok);
}
