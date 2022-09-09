/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:59:46 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/05 13:59:52 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_struct	*run_exec(t_struct *data, char **tok)
{
	if (data->type == BINARY)
		execute(data, tok[1]);
	else if (data->type == BU_ECHO)
		echo(tok);
	else if (data->type == BU_CD)
		cd_builtin(data, tok);
	else if (data->type == BU_PWD)
		pwd_builtin();
	else if (data->type == BU_ENV)
		env_builtin(data);
	else if (data->type == BU_EXPORT)
	{
		export_env(data, tok[1]);
		//exit(EXIT_SUCCESS);
	}
	else if (data->type == BU_UNSET)
	{
		unset_env(data, tok[1]);
		//exit(EXIT_SUCCESS);
	}
	//Quid de l'exit 
	return (data);
}

void	call_exec(t_struct *data, char **tok, int fdin, int fdout)
{
	pid_t	child;
	int		check;

	child = fork();
	if (data->type == BU_EXIT)
		exit_builtins(data, tok);
	if (child == 0)
	{
		check = dup2(fdin, 0);
		//protect(check);
		check = dup2(fdout, 1);
		// protect(check);
		if (fdout != 1)
			close(fdout);
		if (fdin != 0)
			close(fdin);
		data = run_exec(data, tok);
	}
	waitpid(child, NULL, 0);
	if (access(HERE_DOC, F_OK) == 0)
		unlink(HERE_DOC);
}

void	pipe_exec(t_struct *data, char **tok, char *line)
{
	int		check;
	char	**split_pipe;
	int		len;
	int		i;
	int		pipe_fd[2];
	int		pipe_fd2[2];

	split_pipe = ft_split(line, '|');
	len = len_split(split_pipe);
	i = 0;
	tok = tokenisation(split_pipe[i], tok, data);
	check = pipe(pipe_fd);
	//protection
	if (ft_atoi(tok[2]) == 1)
		call_exec(data, tok, ft_atoi(tok[0]), pipe_fd[1]);
	else
		call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]));
	close(pipe_fd[1]);
	i++;
	while (i < len - 2)
	{
		check = pipe(pipe_fd2);
		//protection
		tok = tokenisation(split_pipe[i], tok, data);
		if (ft_atoi(tok[0]) == 0 && ft_atoi(tok[2]) == 1)
			call_exec(data, tok, pipe_fd[0], pipe_fd2[1]);
		else if (ft_atoi(tok[0]) == 0 && ft_atoi(tok[2]) != 1)
			call_exec(data, tok, pipe_fd[0], ft_atoi(tok[2]));
		else if (ft_atoi(tok[0]) != 0 && ft_atoi(tok[2]) == 1)
			call_exec(data, tok, ft_atoi(tok[0]), pipe_fd2[1]);
		else
			call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]));
		close(pipe_fd2[1]);
		pipe_fd[0] = dup2(pipe_fd2[0], pipe_fd[0]);
		pipe_fd[1] = dup2(pipe_fd2[1], pipe_fd[1]);
		close(pipe_fd2[0]);
		close(pipe_fd2[1]);
		i++;
	}
	tok = tokenisation(split_pipe[i], tok, data);
	if (ft_atoi(tok[0]) == 0)
		call_exec(data, tok, pipe_fd[0], ft_atoi(tok[2]));
	else
		call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]));
}
