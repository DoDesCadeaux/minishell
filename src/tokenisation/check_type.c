/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:35:50 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/15 18:35:52 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	export_type(char *line)
{
	int	type;

	if (!line)
		type = BU_EXPORT_EMPTY;
	else
		type = BU_EXPORT;
	return (type);
}

static int	check_binary(t_struct *data, char **cmd_arg, int type)
{
	int			i;
	struct stat	sb;

	i = 1;
	data->error_cat = 0;
	if (type == BINARY)
	{
		if (!is_good_binary(data, cmd_arg[0]))
			type = BAD_BINARY;
		else
		{
			if (!ft_strcmp(cmd_arg[0], "cat"))
			{
				if (!ft_strcmp(cmd_arg[i], "-e"))
					i++;
				while (cmd_arg[i])
				{
					if (stat(cmd_arg[i], &sb) < 0)
						data->error_cat = 1;
					i++;
				}
			}
		}
	}
	return (type);
}

int	check_type(t_struct *data, char **tok)
{
	char	**full_cmd;
	int		type;

	run_signals(2);
	full_cmd = ft_split_pipe(tok[1], ' ');
	if (!ft_strcmp(full_cmd[0], ECHO))
		type = BU_ECHO;
	else if (!ft_strcmp(full_cmd[0], CD))
		type = BU_CD;
	else if (!ft_strcmp(full_cmd[0], PWD))
		type = BU_PWD;
	else if (!ft_strcmp(full_cmd[0], ENV))
		type = BU_ENV;
	else if (!ft_strcmp(full_cmd[0], EXPORT))
		type = export_type(full_cmd[1]);
	else if (!ft_strcmp(full_cmd[0], UNSET))
		type = BU_UNSET;
	else if (!ft_strcmp(full_cmd[0], EXIT))
		type = BU_EXIT;
	else
		type = BINARY;
	if (type == BINARY)
		type = check_binary(data, full_cmd, type);
	ft_free_split(full_cmd);
	return (type);
}
