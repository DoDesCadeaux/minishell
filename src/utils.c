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
		error_code = 1;
		exit(EXIT_FAILURE);
	}
}
