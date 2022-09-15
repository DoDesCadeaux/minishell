/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:49:30 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/13 14:49:32 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	run_first(t_struct *data, char **tok, int *pipe_fd)
{
	if (ft_atoi(tok[2]) == 1)
		call_exec(data, tok, ft_atoi(tok[0]), pipe_fd[1]);
	else
		call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]));
	close(pipe_fd[1]);
}

void	run_last(t_struct *data, char **tok, int *pipe_fd)
{
	if (ft_atoi(tok[0]) == 0)
		call_exec(data, tok, pipe_fd[0], ft_atoi(tok[2]));
	else
		call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]));
}

void	run_multi_pipe(t_struct *data, char **tok, int *pipe_fd1)
{
	int		pipe_fd2[2];

	data->check = pipe(pipe_fd2);
	//protection
	if (ft_atoi(tok[0]) == 0 && ft_atoi(tok[2]) == 1)
		call_exec(data, tok, pipe_fd1[0], pipe_fd2[1]);
	else if (ft_atoi(tok[0]) == 0 && ft_atoi(tok[2]) != 1)
		call_exec(data, tok, pipe_fd1[0], ft_atoi(tok[2]));
	else if (ft_atoi(tok[0]) != 0 && ft_atoi(tok[2]) == 1)
		call_exec(data, tok, ft_atoi(tok[0]), pipe_fd2[1]);
	else
		call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]));
	close(pipe_fd2[1]);
	pipe_fd1[0] = dup2(pipe_fd2[0], pipe_fd1[0]);
	pipe_fd1[1] = dup2(pipe_fd2[1], pipe_fd1[1]);
	close(pipe_fd2[0]);
	close(pipe_fd2[1]);
}

void	pipe_exec(t_struct *data, char **tok, char *line)
{
	char	**split_pipe;
	int		len;
	int		i;
	int		pipe_fd[2];

	split_pipe = ft_split_pipe(line, '|');
	len = len_split(split_pipe);
	i = 0;
	tok = tokenisation(split_pipe[i], tok, data);
	data->check = pipe(pipe_fd);
	//protection
	run_first(data, tok, pipe_fd);
	i++;
	while (i < len - 2)
	{
		tok = tokenisation(split_pipe[i], tok, data);
		run_multi_pipe(data, tok, pipe_fd);
		i++;
	}
	tok = tokenisation(split_pipe[i], tok, data);
	run_last(data, tok, pipe_fd);
}
