/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:22:40 by algaspar          #+#    #+#             */
/*   Updated: 2022/11/30 16:22:52 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipe_loop(char **split_pipe, char **tok, t_struct *data, int pipe_fd[2])
{
	int	i;

	i = 1;
	while (i < len_split(split_pipe) - 2)
	{
		tok = tokenisation(split_pipe[i], tok, data);
		run_multi_pipe(data, tok, pipe_fd);
		ft_clear_split(tok);
		i++;
	}
	return (i);
}
