/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status_binary.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 22:10:18 by pamartin          #+#    #+#             */
/*   Updated: 2022/11/14 10:52:16 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_access(char *cmd, char **cmd_arg)
{
	if (access(cmd, X_OK) != 0)
	{
		ft_free_split(cmd_arg);
		return (0);
	}
	else
	{
		ft_free_split(cmd_arg);
		return (1);
	}
}

static int	path_exists(char **cmd_arg, char *cmd)
{
	if (!ft_strncmp(cmd, "./", 2))
		return (check_access(cmd_arg[0], cmd_arg));
	if (!ft_strncmp(cmd, "/", 1))
		return (check_access(cmd_arg[0], cmd_arg));
	return (0);
}

int	is_good_binary(t_struct *data, char *cmd)
{
	char	**paths;
	char	**cmd_arg;
	char	*path;
	int		rt;

	cmd_arg = ft_split_pipe(cmd, ' ');
	if (!cmd_arg[0])
		return (0);
	if (cmd_arg[0][0] == '\"')
		return ((int)ft_free_split(cmd_arg));
	if (!var_exist(data, "PATH"))
		return (path_exists(cmd_arg, cmd));
	if (!ft_strncmp(cmd, "./", 2))
		return (check_access(cmd_arg[0], cmd_arg));
	if (!ft_strncmp(cmd, "/", 1))
		return (check_access(cmd_arg[0], cmd_arg));
	else
	{
		paths = path_list(data->envp);
		path = get_cmd_path(paths, cmd_arg[0]);
		rt = check_access(path, cmd_arg);
		free(path);
		return (rt);
	}
}
