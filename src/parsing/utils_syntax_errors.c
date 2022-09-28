/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 23:11:04 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/27 17:01:28 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_empty_line(char *line)
{
	if (*line == '\0')
		return (1);
	return (0);
}

int	error_msg(char *msg, int code)
{
	ft_error(msg, code);
	return (1);
}
