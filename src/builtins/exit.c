/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:43:18 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 14:43:47 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_builtins(t_struct *data, char **tok)
{
	ft_free_split(data->envp);
	ft_free_split(data->pwd);
	free(data);
	ft_free_split(tok);
//	system("leaks minishell");
	exit(EXIT_SUCCESS);
}
