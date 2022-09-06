/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:14:33 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 13:14:35 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_builtin(t_struct *data, char **tok)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		ft_putstr_fd(data->envp[i], ft_atoi(tok[2]));
		ft_putchar_fd('\n', ft_atoi(tok[2]));
		i++;
	}
	//attention message d'erreur
}
