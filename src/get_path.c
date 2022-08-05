/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:44:04 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/05 18:44:07 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**path_list(char **envp)
{
	char	*path;
	char	**full_path;
	size_t	i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4))
		i++;
	path = envp[i] + 5;
	full_path = ft_split(path, ':');
	return (full_path);
}

static char	*get_cmd_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*path;
	size_t	i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

char	*get_full_cmd(char **argv)
{
	int		i;
	char	*full_cmd;

	i = 2;
	full_cmd = ft_strjoin(argv[1], " ");
	while (argv[i])
	{
		full_cmd = ft_strjoin(full_cmd, argv[i]);
		full_cmd = ft_strjoin(full_cmd, " ");
		i++;
	}
	return (full_cmd);
}
