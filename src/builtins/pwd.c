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

#include "../include/minishell.h"

void	pwd_builtin(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 200);
	if (!pwd)
		printf("prout pwd\n");
	printf("%s\n", pwd);
	free(pwd);
	pwd = 0x0;
	exit(EXIT_SUCCESS);
}
