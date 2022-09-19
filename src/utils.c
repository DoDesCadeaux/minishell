/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:44:52 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/13 18:44:54 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	protect_malloc(void *element)
{
	if (!element)
	{
		error_code = MALLOC;
		exit(EXIT_FAILURE);
	}
}

char	*msg(char *cmd, char *element, char *msg)
{
	char 	*tmp;
	char	*message;

	tmp = ft_strjoin("minishell: ", cmd);
	message = ft_strjoin(tmp, ": ");
	free(tmp);
	if (element)
	{
		tmp = ft_strjoin(message, element);
		free(message);
		message = ft_strjoin(tmp, ": ");
		free(tmp);
	}
	tmp = ft_strjoin(message, msg);
	free(message);
	return (tmp);
}
