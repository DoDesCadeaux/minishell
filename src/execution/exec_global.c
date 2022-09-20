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

void	protected_execve(char *path, char **cmd_arg, char **envp, int status)
{
	int	check;

	printf("bordel de cul\n");
	//printf("cmd arg = %s\n", path);
	if (status == 1)
		check = execve(path, cmd_arg, envp);
	else
		check = -1;
	if (check == -1)
	{
		ft_free_split(cmd_arg);
		ft_error_exit(msg(cmd_arg[0], NULL, "Command not found"), CMD_ERROR);
	}
}

void	close_fd(int fdin, int fdout)
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
		ft_error("ERROR SPLIT ARG", CMD_ERROR);
	if (!cmd_arg[0])
		ft_error_exit(msg(cmd_arg[0], NULL, "Command not found"), CMD_ERROR);
	if (!var_exist(data, "PATH"))
		ft_error_exit(msg(cmd_arg[0], NULL, "No such file or directory"), CMD_ERROR);
	if (!ft_strncmp(cmd, "./", 2))
	{
		if (access(cmd, X_OK) != 0)
			ft_error_exit(msg(cmd_arg[0], NULL, "Command not found"), CMD_ERROR);
		else
			protected_execve(cmd_arg[0], cmd_arg, data->envp, 1);
	}
	if (!ft_strncmp(cmd, "/", 1))
	{
		if (access(cmd, X_OK) != 0)
			ft_error_exit(msg(cmd_arg[0], NULL, "Command not found"), CMD_ERROR);
		else
			protected_execve(cmd_arg[0], cmd_arg, data->envp, 1);
	}
	else
	{
		paths = path_list(data->envp);
		if (!paths)
			ft_error_exit(msg(cmd_arg[0], NULL, "Command not found"), CMD_ERROR);
		path = get_cmd_path(paths, cmd_arg[0]);
		if (!path)
			ft_error_exit(msg(cmd_arg[0], NULL, "Command not found"), CMD_ERROR);
		protected_execve(path, cmd_arg, data->envp, 1);
	}
}

void	run_exec(t_struct *data, char **tok)
{
	if (data->type == BINARY)
		execute(data, tok[1]);
	else if (data->type == BU_ECHO)
		echo(tok);
	else if (data->type == BU_PWD)
		pwd_builtin();
	else if (data->type == BU_ENV)
		env_builtin(data);
	else if (data->type == BU_EXPORT_EMPTY)
		export_empty(data);
	else
		exit(EXIT_SUCCESS);
}

void	call_exec(t_struct *data, char **tok, int fdin, int fdout)
{
	pid_t	child;

	if (data->type == BU_CD)
		cd_builtin(data, tok);
	child = fork();
	if (data->pipe == 0)
	{
		if (data->type == BU_EXIT)
			exit_builtins();
		else if (data->type == BU_UNSET)
			unset_env(data, tok[1]);
		else if (data->type == BU_EXPORT)
			export_env(data, tok[1]);
	}
	if (child == 0)
	{
		data->check = dup2(fdin, 0);
		if (data->check == -1)
			ft_error_exit("", ERRNO);
		data->check = dup2(fdout, 1);
		if (data->check == -1)
			ft_error_exit("", ERRNO);
		close_fd(fdin, fdout);
		run_exec(data, tok);
	}
	waitpid(child, NULL, 0);
	if (access(HERE_DOC, F_OK) == 0)
		unlink(HERE_DOC);
}
