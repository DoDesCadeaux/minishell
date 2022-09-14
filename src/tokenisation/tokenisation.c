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

	if (!delimiter)
		return (NULL);
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

	info= NULL;
	if (!ft_strcmp(line_split[i], LESS))
	{
		info = get_fd(line_split[i + 1], REDIR_STDIN, NULL);
		if (!info)
			ft_error("ERROR FD1", 1); ///youpi: No such file or directory
		i = 2;
	}
	else if (!ft_strcmp(line_split[i], DLESS))
	{
		info = create_heredoc(line_split[i + 1]);
		i = 2;
		if (!line_split[i + 1])
		{
			i = 3;
			unlink(HERE_DOC);
		}
	}
	else if (!ft_strcmp(line_split[i], DGREAT)|| !ft_strcmp(line_split[i], GREAT))
		i = 2;
	else
		info = get_fd(NULL, REDIR_STDIN, NULL);
	if (!info)
		return (i);
	tok[0] = ft_strdup(info);
	free(info);
	return (i);
}

char	*get_cmd(char *str, int i)
{
	int		y;
	char	*line;

	y = 0;
	if (!str)
		return (NULL);
	line = malloc(sizeof(char) * i + 1);
	protect_malloc(line);
	while (y < i)
	{
		line[y] = str[y];
		y++;
	}
	line[y] = '\0';
	return (line);
}

int	tok_1(char **tok, char **line_split, int i, char *line)
{
	char	*info;
	char	*tmp;
	char	*start;
	char	*end;
	int		i_end;

	end = NULL;
	info = NULL;
	start = ft_strdup(line_split[i]);
	tmp = ft_strstr(line, start);
	while (line_split[i])
	{
		if (ft_strcmp(line_split[i], GREAT) && ft_strcmp(line_split[i], DGREAT))
			i++;
		else
			break ;
	}
	if (line_split[i])
		end = ft_strdup(line_split[i]);
	if (end)
		i_end = ft_strpstr(tmp, end);
	else
		i_end = ft_strlen(line);
	info = get_cmd(tmp, i_end);
	tok[1] = ft_strdup(info);
	free(info);
	return (i);
}

char	**tokenisation(char *line, char **tok, t_struct *data)
{
	char **line_split;
	char *tmp;
	int i;

	line_split = ft_split(line, ' ');
	i = 0;
	i = tok_fd_in(tok, line_split, i);
	if (i == len_split(line_split))
		return (NULL);
	i = tok_1(tok, line_split, i, line); //APPEL PARSING
	tok[1] = parsing(tok[1], data);
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
	data->type = check_type(tok);
	return (tok);
}

int	check_type(char **tok)
{
	char	**full_cmd;
	int		type;

	run_signals(2);
	full_cmd = ft_split(tok[1], ' ');
	if (!ft_strcmp(full_cmd[0], ECHO))
		type = BU_ECHO;
	else if (!ft_strcmp(full_cmd[0], CD))
		type = BU_CD;
	else if (!ft_strcmp(full_cmd[0], PWD))
		type = BU_PWD;
	else if (!ft_strcmp(full_cmd[0], ENV))
		type = BU_ENV;
	else if (!ft_strcmp(full_cmd[0], EXPORT))
		type = BU_EXPORT;
	else if (!ft_strcmp(full_cmd[0], UNSET))
		type = BU_UNSET;
	else if (!ft_strcmp(full_cmd[0], EXIT))
		type = BU_EXIT;
	else
		type = BINARY;
	return (type);
}