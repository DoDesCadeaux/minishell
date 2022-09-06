/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:08:46 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 13:08:48 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd_builtin(t_struct *data, char **tok)
{
	char	*pwd;

	data++;
	pwd = NULL;
	pwd = getcwd(pwd, 200);
	if (!pwd)
		printf("prout pwd\n");
	ft_putstr_fd(pwd, ft_atoi(tok[2]));
	ft_putchar_fd('\n', ft_atoi(tok[2]));
	free(pwd);
	pwd = 0x0;
}
