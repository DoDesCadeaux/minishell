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

#include "../../include/minishell.h"

static void	protected_execve(char *path, char **cmd_arg, char **envp)
{
	int	check;

	check = execve(path, cmd_arg, envp);
	if (check == -1)
	{
		ft_free_split(cmd_arg);
		ft_error_exit(msg(cmd_arg[0], NULL, "Command not found"), CMD_ERROR);
	}
}

static void	close_fd(int fdin, int fdout)
{
	if (fdout != 1)
		close(fdout);
	if (fdin != 0)
		close(fdin);
}

void	execute(t_struct *data, char *cmd)
{
	char	**paths;
	char	**cmd_arg;
	char	*path;

	cmd_arg = ft_split_pipe(cmd, ' ');
	if (!cmd_arg)
		ft_error("minishell: error malloc", MALLOC);
	if (!ft_strncmp(cmd, "./", 2))
		protected_execve(cmd_arg[0], cmd_arg, data->envp);
	if (!ft_strncmp(cmd, "/", 1))
		protected_execve(cmd_arg[0], cmd_arg, data->envp);
	else
	{
		paths = path_list(data->envp);
		path = get_cmd_path(paths, cmd_arg[0]);
		protected_execve(path, cmd_arg, data->envp);
	}
}

void	call_exec(t_struct *data, char **tok, int fdin, int fdout)
{
	pid_t	child;

	g_error_code = 0;
	if (data->type == BU_CD)
		cd_builtin(data, tok);
	if (data->type == BAD_BINARY)
		run_bad_binary(data, tok[1]);
	child = fork();
	if (data->pipe == 0)
		run_without_pipe(data, tok);
	if (child == 0)
	{
		data->check = dup2(fdin, 0);
		if (data->check == -1)
			ft_error_exit("", errno);
		data->check = dup2(fdout, 1);
		if (data->check == -1)
			ft_error_exit("", errno);
		close_fd(fdin, fdout);
		run_exec(data, tok);
	}
	waitpid(child, NULL, 0);
	if (access(HERE_DOC, F_OK) == 0)
		unlink(HERE_DOC);
}

void	run_program(t_struct *data, char **tok, char *line)
{
	if (!is_pipe(line))
	{
		data->pipe = 0;
		tok = tokenisation(line, tok, data);
		if (tok)
		{
			call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]));
			ft_clear_split(tok);
		}
		free(tok);
	}
	else
	{
		data->pipe = 1;
		pipe_exec(data, tok, line);
	}
}
