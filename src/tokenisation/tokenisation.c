/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:49:46 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 12:49:51 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*create_heredoc(char *delimiter)
{
	char	*line;
	char	*info;
	int		here_doc;
	int		fd;

	here_doc = open("here_doc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (here_doc < 0)
		printf("ERROR HERE DOC");
	line = get_next_line(0);
	while (line && (ft_strncmp(line, delimiter, ft_strlen(delimiter))
			|| ft_strlen(delimiter) + 1 != ft_strlen(line)))
	{
		write(here_doc, line, ft_strlen(line));
		line = get_next_line(0);
	}
	free(line);
	fd = open("here_doc", O_RDONLY);
	info = ft_itoa(fd);
	return (info);
}

int	tok_fd_in(char **tok, char **line_split, int i)
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
		info = get_fd(NULL, REDIR_STDIN, NULL);
	tok[0] = ft_strdup(info);
	free(info);
	return (i);
}

int	tok_1(char **tok, char **line_split, int i)
{
	char	*info;
	char	*tmp;

	if (ft_strcmp(line_split[i], GREAT) && ft_strcmp(line_split[i], DGREAT)
		&& ft_strcmp(line_split[i], PIPE))
	{
		info = ft_strdup(line_split[i]);
		i++;
	}
	while (line_split[i])
	{
		if (ft_strcmp(line_split[i], GREAT) && ft_strcmp(line_split[i], DGREAT)
			&& ft_strcmp(line_split[i], PIPE))
		{
			tmp = ft_strjoin(info, " ");
			free(info);
			info = ft_strjoin(tmp, line_split[i]);
			free(tmp);
		}
		else
			break ;
		i++;
	}
	tok[1] = ft_strdup(info);
	free(info);
	return (i);
}

char	**tokenisation(char *line, char **tok)
{
	char **line_split;
	char *tmp;
	int i;

	line_split = ft_split(line, ' ');
	i = 0;
	i = tok_fd_in(tok, line_split, i);
	i = tok_1(tok, line_split, i); //APPEL PARSING
	if (line_split[i] && !ft_strcmp(line_split[i], GREAT)) //TOK_FD_OUT
		tmp = get_fd(line_split[i + 1], REDIR_STDOUT, GREAT);
	else if (line_split[i] && !ft_strcmp(line_split[i], DGREAT))
		tmp = get_fd(line_split[i + 1], REDIR_STDOUT, DGREAT);
	else
		tmp = get_fd(NULL, REDIR_STDOUT, NULL);
	tok[2] = ft_strdup(tmp);
	tok[3] = 0;
	free(tmp);
	free(line);
	ft_free_split(line_split);
	return (tok);
}

void	call_execute(char **tok, t_struct *data)
{
	char	**full_cmd;

	run_signals(2);
	full_cmd = ft_split(tok[1], ' ');
	if (!ft_strcmp(full_cmd[0], ECHO))
		echo(tok);
	else if (!ft_strcmp(full_cmd[0], CD))
		cd_builtin(data, full_cmd[1], tok);
	else if (!ft_strcmp(full_cmd[0], PWD))
		pwd_builtin(data, tok);
	else if (!ft_strcmp(full_cmd[0], ENV))
		env_builtin(data, tok);
	else if (!ft_strcmp(full_cmd[0], EXPORT))
		data = export_env(data, full_cmd);
	else if (!ft_strcmp(full_cmd[0], UNSET))
		data = unset_env(data, full_cmd);
	else if (!ft_strcmp(full_cmd[0], EXIT))
		exit_builtins(data, tok);
	else
		exec_global(data, tok, tok[1]);
	if (access(HERE_DOC, F_OK) == 0)
		unlink("here_doc");
	ft_free_split(full_cmd);
}
