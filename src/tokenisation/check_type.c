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

int	export_type(char *line)
{
	int	type;

	if (!line)
		type = BU_EXPORT_EMPTY;
	else
		type = BU_EXPORT;
	return (type);
}

int	is_good_binary(t_struct *data, char *cmd)
{
	char	**paths;
	char	**cmd_arg;
	char	*path;

	cmd_arg = ft_split_pipe(cmd, ' ');
	if (!cmd_arg)
		ft_error("???", CMD_ERROR);	// que écrire dans l'error??
	if (!cmd_arg[0])
		return (0);
	if (!var_exist(data, "PATH"))
		return (0);
	if (!ft_strncmp(cmd, "./", 2))
	{
		if (access(cmd, X_OK) != 0)
			return (0);
		else
			return (1);
	}
	if (!ft_strncmp(cmd, "/", 1))
	{
		if (access(cmd, X_OK) != 0)
			return (0);
		else
			return (1);
	}
	else
	{
		paths = path_list(data->envp);
		path = get_cmd_path(paths, cmd_arg[0]);
		if (access(path, X_OK) != 0)
			return (0);
		else
			return (1);
	}
}

int	check_type(char **tok, t_struct *data)
{
	char	**full_cmd;
	int		type;

	run_signals(2);
	full_cmd = ft_split(tok[1], ' ');
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
	{
		if (!is_good_binary(data, tok[1]))
			type = BAD_BINARY;
	}
	return (type);
}
