/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_global.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:40:15 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/17 20:40:17 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**path_list(char **envp)
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

char	*get_cmd_path(char **paths, char *cmd)
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

void	protected_execve(char *path, char **cmd_arg, char **envp, int status)
{
	int	check;

	if (status == 1)
		check = execve(path, cmd_arg, envp);
	else
		check = -1;
	if (check == -1)
	{
		ft_free_split(cmd_arg);
		printf("ERROR EXEC 2\n");
		exit(EXIT_SUCCESS);
	}
}

void	execute(t_struct *data, char *cmd)
{
	char	**paths;
	char	**cmd_arg;
	char	*path;

	cmd_arg = ft_split(cmd, ' ');
	if (!cmd_arg)
		printf("ERROR SPLIT ARG\n");
	if (!ft_strncmp(cmd, "./", 2))
	{
		if (access(cmd, X_OK) == 0)
			protected_execve(cmd, cmd_arg, data->envp, 1);
		else
			protected_execve(NULL, cmd_arg, NULL, 0);
	}
	else
	{
		paths = path_list(data->envp);
		if (!paths)
			printf("ERROR PATH\n");
		path = get_cmd_path(paths, cmd_arg[0]);
		if (!path)
			printf("ERROR PATH ARG\n");
		protected_execve(path, cmd_arg, data->envp, 1);
	}
}
