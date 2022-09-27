/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:49:30 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/27 15:21:58 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static void	run_first(t_struct *data, char **tok, int *pipe_fd)
// {
// 	if (ft_atoi(tok[2]) == 1)
// 		call_exec(data, tok, ft_atoi(tok[0]), pipe_fd[1]);
// 	else
// 		call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]));
// 	close(pipe_fd[1]);
// }

// static void	run_last(t_struct *data, char **tok, int *pipe_fd)
// {
// 	if (ft_atoi(tok[0]) == 0)
// 		call_exec(data, tok, pipe_fd[0], ft_atoi(tok[2]));
// 	else
// 		call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]));
// }

// static void	run_multi_pipe(t_struct *data, char **tok, int *pipe_fd1)
// {
// 	int		pipe_fd2[2];

// 	data->check = pipe(pipe_fd2);
// 	if (data->check < 0)
// 	{
// 		error_perror();
// 	}
// 	if (ft_atoi(tok[0]) == 0 && ft_atoi(tok[2]) == 1)
// 		call_exec(data, tok, pipe_fd1[0], pipe_fd2[1]);
// 	else if (ft_atoi(tok[0]) == 0 && ft_atoi(tok[2]) != 1)
// 		call_exec(data, tok, pipe_fd1[0], ft_atoi(tok[2]));
// 	else if (ft_atoi(tok[0]) != 0 && ft_atoi(tok[2]) == 1)
// 		call_exec(data, tok, ft_atoi(tok[0]), pipe_fd2[1]);
// 	else
// 		call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]));
// 	close(pipe_fd2[1]);
// 	pipe_fd1[0] = dup2(pipe_fd2[0], pipe_fd1[0]);
// 	pipe_fd1[1] = dup2(pipe_fd2[1], pipe_fd1[1]);
// 	close(pipe_fd2[0]);
// 	close(pipe_fd2[1]);
// }

// void	pipe_exec(t_struct *data, char **tok, char *line)
// {
// 	char	**split_pipe;
// 	int		len;
// 	int		i;
// 	int		pipe_fd[2];

// 	split_pipe = ft_split_pipe(line, '|');
// 	len = len_split(split_pipe);
// 	i = 0;
// 	tok = tokenisation(split_pipe[i], tok, data);
// 	data->check = pipe(pipe_fd);
// 	if (data->check < 0)
// 	{
// 		error_perror();
// 	}
// 	run_first(data, tok, pipe_fd);
// 	i++;
// 	while (i < len - 2)
// 	{
// 		tok = tokenisation(split_pipe[i], tok, data);
// 		run_multi_pipe(data, tok, pipe_fd);
// 		i++;
// 	}
// 	tok = tokenisation(split_pipe[i], tok, data);
// 	run_last(data, tok, pipe_fd);
// }

void	single_pipe(char **split_pipe, char **tok, t_struct *data)
{
	int	pfd[2];
	int	pid1;
	int	pid2;

	tok = tokenisation(split_pipe[0], tok, data);
	if (pipe(pfd) == -1)
		ft_error_exit("pipe error", 0);
	pid1 = fork();
	if (pid1 == -1)
		ft_error_exit("fork error", 0);
	if (pid1 == 0)
	{
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[0]);
		run_exec(data, tok);
	}
	else
	{
		tok = tokenisation(split_pipe[1], tok, data);
		pid2 = fork();
		if (pid2 == -1)
			ft_error_exit("fork error", 0);
		if (pid2 == 0)
		{
			dup2(pfd[0], STDIN_FILENO);
			close(pfd[1]);
			run_exec(data, tok);
		}
	}
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid1, NULL, 0);
	wait(NULL);
}

int	split_len(char **split)
{
	int	len;

	len = 0;
	while (split[len])
		len++;
	return (len);
}

void	multi_pipe(char **split_pipe, char **tok, t_struct *data)
{
	int	pfd[2];
	int	pid;
	int	fdd;
	int	i;

	i = 0;
	fdd = 0;
	while (split_pipe[i])
	{
		if (pipe(pfd) == -1)
			ft_error_exit("pipe error", 0);
		tok = tokenisation(split_pipe[i], tok, data);
		pid = fork();
		if (pid == -1)
			ft_error_exit("fork error", 0);
		if (pid == 0)
		{
			dup2(fdd, 0);
			if (split_pipe[i + 1] != NULL)
				dup2(pfd[1], 1);
			close(pfd[0]);
			run_exec(data, tok);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(pfd[1]);
			fdd = pfd[0];
			i++;
		}
	}
}

void	pipe_exec(t_struct *data, char **tok, char *line)
{
	char	**split_pipe;

	split_pipe = ft_split_pipe(line, '|');
	if (split_len(split_pipe) == 2)
		single_pipe(split_pipe, tok, data);
	else
		multi_pipe(split_pipe, tok, data);
}
