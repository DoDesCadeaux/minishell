/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:08:17 by algaspar          #+#    #+#             */
/*   Updated: 2022/11/30 16:08:38 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

pid_t	protected_fork(void)
{
	pid_t	child;

	child = fork();
	if (child == -1)
	{
		ft_error(msg(NULL, NULL, "", 1), errno);
		return (-1);
	}
	return (child);
}
