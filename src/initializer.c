/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 23:29:57 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/13 23:30:01 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_struct 	*initializer(char **envp, int argc, char **argv)
 {
	t_struct *data;

	if (argc != 1)
		 ft_error_exit("Number of arguments != 1", ERROR);
	if (ft_strcmp(argv[0], "./minishell"))
		ft_error_exit("Bad program name", ERROR);
	welcome();
	error_code = 0;
	data = malloc(sizeof(t_struct));
	protect_malloc(data);
	data = clone_env(envp, data);
	return (data);
 }
