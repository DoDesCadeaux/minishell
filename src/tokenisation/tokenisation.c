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

	printf("coucou\n");
	data->i_redir = 0;
	data->cmd = -1;
	//data->real_i = 1;
	line_split = ft_split_pipe(line, ' ');
	i = 0;
	i = tok_fd_in(data, tok, line_split, i);
	if (i == len_split(line_split))
		return (NULL);
	while (data->i_redir != 0)
		i = tok_fd_in(data, tok, line_split, i);
	printf("tok0 = %s\n", tok[0]);
	if (!tok[0])
		return (NULL);
	//printf("LIGNE AVANT TOK1 = %s\n", line_split[i]);
	i = tok_1(tok, line_split, i, line);
	if (i < 0)
	{
		printf("je suis ici\n");
		return (NULL);
	}
	i = tok_fd_out(data, tok, line_split, i);
	while (data->i_redir != 0)
		i = tok_fd_out(data, tok, line_split, i);
	printf("i = %d\n", i);
	tok[1] = parsing(tok[1], data);
	tok[1] = parsing_redirstdin(tok[1]);
	printf("tok[1] apres parsing cat = %s\n", tok[1]);
	free(line);
	tok[3] = 0;
	ft_free_split(line_split);
	data->type = check_type(tok, data);
	printf("tok[0] = %s\ntok[1] = %s\ntok[2] = %s\n", tok[0], tok[1], tok[2]);
	return (tok);
}
