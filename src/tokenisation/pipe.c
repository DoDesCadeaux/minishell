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

void	call_exec(t_struct *data, char **tok, int fdin, int fdout, int type)
{
	pid_t	child;
	int		check;
	
	child = fork();
	if (child == 0)
	{
		printf("new exec with in: %i o:%i\n", fdin, fdout);
		check = dup2(fdin, 0);
		//protect(check);
		check = dup2(fdout, 1);
		// protect(check);
		if (fdout != 1)
			close(fdout);
		if (fdin != 0)
			close(fdin);
		if (type == BINARY)
			execute(data, tok[1]);
		else if (type == BU_ECHO)
			echo(tok);
		else if (type == BU_CD)
			cd_builtin(data, tok);
		else if (type == BU_PWD)
			pwd_builtin();
		else if (type == BU_ENV)
			env_builtin(data);
		else if (type == BU_EXPORT)
		{
			data = export_env(data, tok[1]);
			exit(EXIT_SUCCESS);
		}
		else if (type == BU_EXIT)
			exit_builtins(data, tok);
		else if (type == BU_UNSET)
		{
			data = unset_env(data, tok[1]);
			exit(EXIT_SUCCESS);
		}
	}
	waitpid(child, NULL, 0);
}

void	pipe_exec(t_struct *data, char **tok, char *line)
{
	int		check;
	char	**split_pipe;
	int		len;
	int		i;
	int		pipe_fd[2];
	int		pipe_fd2[2];
	int		type;


	

	split_pipe = ft_split(line, '|');
	len = len_split(split_pipe);
	i = 0;
	//split_pipe[i] = parsing_dollar(data, split_pipe[i]);
	tok = tokenisation(split_pipe[i], tok);

	type = check_type(tok);


	check = pipe(pipe_fd);
	printf("new pipe fds in: %i o:%i\n\n", pipe_fd[0], pipe_fd[1]);
	call_exec(data, tok, ft_atoi(tok[0]), pipe_fd[1], type);
	close(pipe_fd[1]);
	i++;
	while (i < len - 2)
	{
		check = pipe(pipe_fd2);
		printf("new pipe 2 fds in: %i o:%i\n\n", pipe_fd2[0], pipe_fd2[1]);
		//split_pipe[i] = parsing_dollar(data, split_pipe[i]);
		tok = tokenisation(split_pipe[i], tok);
		type = check_type(tok);
		call_exec(data, tok, pipe_fd[0], pipe_fd2[1], type);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(pipe_fd2[1]);
		pipe_fd[0] = pipe_fd2[0];
		pipe_fd[1] = pipe_fd2[1];
		i++;
	}
	//split_pipe[i] = parsing_dollar(data, split_pipe[i]);
	// printf("gnl: %s\n", get_next_line(pipe_fd[0]));
	tok = tokenisation(split_pipe[i], tok);
	type = check_type(tok);
	call_exec(data, tok, pipe_fd[0], ft_atoi(tok[2]), type);
	printf("j'qi finiiiiiii\n");
}