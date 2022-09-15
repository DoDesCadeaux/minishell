/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_stdin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:50:26 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/15 18:50:28 by pamartin         ###   ########.fr       */
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

char	*manage_info_stdin(char *info, char **line_split, int i)
{
	if (!ft_strcmp(line_split[i], LESS))
	{
		info = get_fd(line_split[i + 1], REDIR_STDIN, NULL);
		if (!info)
			ft_error("ERROR FD1", 1); ///youpi: No such file or directory
	}
	else if (!ft_strcmp(line_split[i], DLESS))
	{
		info = create_heredoc(line_split[i + 1]);
		if (!line_split[i + 1])
			unlink(HERE_DOC);
	}
	return (info);
}

int	tok_fd_in(char **tok, char **line_split, int i)
{
	char	*info;

	info = NULL;
	info = manage_info_stdin(info, line_split, i);
	if (!ft_strcmp(line_split[i], LESS))
		i = 2;
	else if (!ft_strcmp(line_split[i], DLESS))
	{
		if (!line_split[i + 1])
			i = 3;
	}
	else if (!ft_strcmp(line_split[i], DGREAT)
		|| !ft_strcmp(line_split[i], GREAT))
		i = 2;
	else
		info = get_fd(NULL, REDIR_STDIN, NULL);
	if (!info)
		return (i);
	tok[0] = ft_strdup(info);
	free(info);
	return (i);
}
