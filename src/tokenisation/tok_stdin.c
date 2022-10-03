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
	else
		info = get_fd(NULL, REDIR_STDIN, NULL);
	printf("info = %s\n", info);
	return (info);
}

int	tok_fd_in(t_struct *data, char **tok, char **line_split, int i)
{
	char	*info;
	int		y;
	int		i_manage;

	y = 0;
	info = NULL;
	if (data->i_redir == 1)
		i = data->i_redir;
	else if (data->i_redir > 1)
		i = data->i_redir - 1;
	i_manage = i;
	if (!ft_strcmp(line_split[i], LESS)) /// remplacer par is_less_redirection
		i += 2;
	else if (!ft_strcmp(line_split[i], DLESS))
		i += 2;
	else if (is_a_greater_redirection(line_split, i))
		i += 0;
	if (there_is_a_less_redirection(line_split, i) && i > 0)
		data->i_redir = i + 1;
	else
		data->i_redir = -1;
	if (data->i_redir != -1 && data->cmd < 0)
	{
		data->cmd = i;
	}
	printf("line_split[i] = %s\n", line_split[i]);
	if ((data->i_redir != -1 && !is_any_redirection(line_split, i)) || (there_is_a_less_redirection(line_split, i) && i == 0))
	{
		y = i + 1;
		while (line_split[y] && !is_a_greater_redirection(line_split, y))
		{
			printf("ici\n");
			printf("au debut de le boucle line = %s\n", line_split[y]);
			manage_info_stdin(info, line_split, y);
			if (!ft_strcmp(line_split[y], LESS)) /// remplacer par is_less_redirection
				y += 2;
			else if (!ft_strcmp(line_split[y], DLESS))
				y += 2;
			else if (is_a_greater_redirection(line_split, y))
				y += 0;
			else
				y += 1;
			printf("dans le boucle line = %s\n", line_split[y]);
		}
		data->i_redir = -1;
	}
	info = manage_info_stdin(info, line_split, i_manage);
	if (!info)
		return (-1);
	tok[0] = ft_strdup(info);
	if (data->cmd == 0)
		return (data->cmd);
	if (!info)
		return (i);
	free(info);
	printf("tok0 = %s\n", tok[0]);
	return (i);
}
