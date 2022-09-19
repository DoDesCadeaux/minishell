/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:06:00 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/19 18:06:05 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char    *get_full_pipe(char *line)
{
    char    *tmp;
    char    *tmp2;  

    tmp = get_next_line(0);
    tmp2 = ft_strjoin(line, " ");
    free(line);
    line = ft_strjoin(tmp2, tmp);
    line[ft_strlen(line) - 1] = '\0';
    free(tmp);
    free(tmp2);
    add_history(line);
    if (is_metachar(line[ft_strlen(line) - 1]))
		line = get_full_pipe(line);
    return (line);
}