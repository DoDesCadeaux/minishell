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

void	execute(t_struct *data, char *cmd)
{
	char	**paths;
	char	**cmd_arg;
	char	*path;
	int		check;

	cmd_arg = ft_split(cmd, ' ');
	if (!cmd_arg)
		printf("ERROR SPLIT ARG\n");
	paths = path_list(data->envp);
	if (!paths)
		printf("ERROR PATH\n");
	path = get_cmd_path(paths, cmd_arg[0]);
	if (!path)
		printf("ERROR PATH ARG\n");
	check = execve(path, cmd_arg, data->envp);
	if (check == -1)
	{
		ft_free_split(cmd_arg);
		printf("ERROR EXEC\n");
	}
}

void	exec_global(t_struct *data, char **tok, char *cmd)
{
	pid_t	child;
	int		check;

	child = fork();
	if (child == 0)
	{
		if (ft_strcmp(tok[0], "0"))
		{
			check = dup2(ft_atoi(tok[0]), 0);
			if (check == -1)
				printf("nuuuuul\n");
			close(ft_atoi(tok[0]));
		}
		if (ft_strcmp(tok[2], "1"))
		{
			check = dup2(ft_atoi(tok[2]), 1);
			if (check == -1)
				printf("merdouille\n");
			close(ft_atoi(tok[2]));
		}
		execute(data, cmd);
	}
	waitpid(-1, NULL, 0);
}
