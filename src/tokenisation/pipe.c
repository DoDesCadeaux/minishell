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

void	clear_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
}

int	tok_fd_in_pipe(char **tok, char **line_split, int i, int *pipe_fd)
{
	char	*info;

	if (!ft_strcmp(line_split[i], LESS))
	{
		info = get_fd(line_split[i + 1], REDIR_STDIN, NULL);
		if (!info)
		{
			printf("ERROR FD1\n"); ///youpi: No such file or directory
			exit(EXIT_FAILURE); //Pas de vrai exist!
		}
		i = 2;
	}
	else if (!ft_strcmp(line_split[i], DLESS))
	{
		info = create_heredoc(line_split[i + 1]);
		i = 2;
	}
	else
		info = ft_itoa(pipe_fd[0]);
	tok[0] = ft_strdup(info);
	free(info);
	return (i);
}

char	**toke_with_pipe(char *line, char **tok, int *pipe_fd)
{
	char	**line_split;
	char	*tmp;
	int		i;
	
	line_split = ft_split(line, ' ');
	i = 0;
	i = tok_fd_in_pipe(tok, line_split, i, pipe_fd);
	i = tok_1(tok, line_split, i); //APPEL PARSING
	if (line_split[i] && !ft_strcmp(line_split[i], GREAT)) //TOK_FD_OUT
		tmp = get_fd(line_split[i + 1], REDIR_STDOUT, GREAT);
	else if (line_split[i] && !ft_strcmp(line_split[i], DGREAT))
		tmp = get_fd(line_split[i + 1], REDIR_STDOUT, DGREAT);
	else
		tmp = ft_itoa(pipe_fd[1]);
	tok[2] = ft_strdup(tmp);
	tok[3] = 0;
	free(tmp);
	free(line);
	ft_free_split(line_split);
	return (tok);
}

void	execute_pipe(t_struct *data, char **tok, char *line)
{
	char	**split_pipe;
	int		len;
	int		i;
	int		pipe_fd[2];
	char	*tmp;
	int		check;

	check = pipe(pipe_fd);
	//protection du pipe
	split_pipe = ft_split(line, '|');
	len = len_split(split_pipe);
	i = 0;
	split_pipe[i] = parsing_dollar(data, split_pipe[i]);
	tok = tokenisation(split_pipe[i], tok);
	free(tok[2]);
	tmp = ft_itoa(pipe_fd[1]);
	tok[2] = ft_strdup(tmp);
	call_execute(tok, data);
	//printf("exec ok\n");
	clear_split(tok);
	i++;
	//printf("taille = %d\n", len);
	while (i < len - 2)
	{
		//split_pipe[i] = parsing_dollar(data, split_pipe[i]);
		printf("ici\n");
		tok = toke_with_pipe(split_pipe[i], tok, pipe_fd);
		printf("tok ok\n");
		printf("TOK\n0 : %s\n1 : %s\n2 : %s\n", tok[0], tok[1], tok[2]);
		call_execute(tok, data);
		printf("exec ok\n");
		clear_split(tok);
		printf("clear ok\n");
		i++;
		
	}
	split_pipe[i] = parsing_dollar(data, split_pipe[i]);
	tok = tokenisation(split_pipe[i], tok);
	free(tok[0]);
	tmp = ft_itoa(pipe_fd[0]);
	tok[0] = ft_strdup(tmp);
	call_execute(tok, data);
	printf("derniere exec ok\n");
	ft_free_split(tok);
}
