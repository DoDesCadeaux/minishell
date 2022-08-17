/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:09:42 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/11 21:09:48 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	len1;
	int	len2;
	int	i;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 != len2)
		return (1);
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

char	*get_fd(char *file, int type, char *token)
{
	int		fd;
	char	*fd_tok;

	if (type == REDIR_STDIN)
	{
		if (file)
			fd = open(file, O_RDONLY);
		else
			fd = 0;
	}
	else
	{
		if (file && !ft_strcmp(token, GREAT))
			fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else if (file && !ft_strcmp(token, DGREAT))
			fd = open(file, O_CREAT | O_APPEND | O_RDWR, 0644);
		else
			fd = 1;
	}
	if (fd < 0)
		return (NULL);
	fd_tok = ft_itoa(fd);
	return (fd_tok);
}
