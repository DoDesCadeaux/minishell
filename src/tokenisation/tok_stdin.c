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

static void	protect(void)
{
	perror("minishell: ");
	exit(EXIT_FAILURE);
}

static char	*create_heredoc(char *delimiter)
{
	char	*line;
	char	*info;
	int		here_doc;
	int		fd;

	if (!delimiter)
		return (NULL);
	here_doc = open("here_doc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (here_doc < 0)
		protect();
	line = get_next_line(0, MSG_HERE);
	while (line && (ft_strncmp(line, delimiter, ft_strlen(delimiter))
			|| ft_strlen(delimiter) + 1 != ft_strlen(line)))
	{
		write(here_doc, line, ft_strlen(line));
		line = get_next_line(0, MSG_HERE);
	}
	free(line);
	fd = open("here_doc", O_RDONLY);
	if (fd < 0)
		protect();
	info = ft_itoa(fd);
	return (info);
}

static char	*manage_info_stdin(char *info, char **line_split, int i)
{
	if (!ft_strcmp(line_split[i], LESS))
		info = get_fd(line_split[i + 1], REDIR_STDIN, NULL);
	else if (!ft_strcmp(line_split[i], DLESS))
	{
		info = create_heredoc(line_split[i + 1]);
		if (!line_split[i + 1])
			unlink(HERE_DOC);
	}
	else if (is_a_greater_redirection(line_split, i))
		info = get_fd(NULL, REDIR_STDIN, NULL);
	//printf("info ====== %s\n", info);
	return (info);
}

int	tok_fd_in(t_struct *data, char **tok, char **line_split, int i)
{
	char	*info;

	info = NULL;
	if (data->i_redir != 0)
		i = data->i_redir;
	//printf("i = %d\n", i);
	info = manage_info_stdin(info, line_split, i);
//printf("pass manageavec info = %s\n", info);
	if (!ft_strcmp(line_split[i], LESS))
		i += 2;
	else if (!ft_strcmp(line_split[i], DLESS))
		i += 2;
	else if (is_a_greater_redirection(line_split, i))
		i += 0;
	if (there_is_a_less_redirection(line_split, i) && info)
		data->i_redir = i;
	else
		data->i_redir = 0;
	tok[0] = ft_strdup(info);
	if (!info)
		return (i);
	free(info);
	return (i);
}
