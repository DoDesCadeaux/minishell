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

void	env_builtin(t_struct *data)
{
	int	i;

	if (!var_exist(data, "PATH"))
		ft_error_exit(msg("env", NULL, MSG_NO_SUCH_FILE, 0), CMD_ERROR);
	if (!find_env_path(data))
		ft_error_exit(msg("env", NULL, "Command not found", 0), CMD_ERROR);
	i = 0;
	while (data->envp[i])
	{
		printf("%s\n", data->envp[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}

void	export_empty(t_struct *data)
{
	int		i;
	char	**export;

	export = malloc(sizeof(char *) * len_split(data->envp) + 1);
	protect_malloc(export);
	i = 0;
	while (data->envp[i])
	{
		export[i] = malloc(sizeof(char) * ft_strlen(data->envp[i]) + 1);
		protect_malloc(export[i]);
		export[i] = ft_strlcpy(export[i], data->envp[i],
				ft_strlen(data->envp[i]) + 1);
		i++;
	}
	export[i] = 0;






	i = 0;
	while (export[i])
	{
		printf("declare -x ");
		printf("%s\n", export[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}
