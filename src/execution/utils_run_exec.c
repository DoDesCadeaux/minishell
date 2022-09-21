/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_run_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:59:44 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/15 13:59:46 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	run_bad_binary(t_struct *data, char *cmd)
{
	char	**cmd_arg;

	cmd_arg = ft_split_pipe(cmd, ' ');
	if (!cmd_arg)
		ft_error("minishell: error malloc", MALLOC);
	if (!cmd_arg[0])
		ft_error(msg(cmd, NULL, "Command not found"), CMD_ERROR);
	if (!var_exist(data, "PATH"))
		ft_error(msg(cmd_arg[0], NULL, "No such file or directory"), CMD_ERROR);
	if (!ft_strncmp(cmd, "./", 2))
		ft_error(msg(cmd_arg[0], NULL, "Command not found"), CMD_ERROR);
	if (!ft_strncmp(cmd, "/", 1))
		ft_error(msg(cmd_arg[0], NULL, "Command not found"), CMD_ERROR);
	else
		ft_error(msg(cmd, NULL, "Command not found"), CMD_ERROR);
	ft_free_split(cmd_arg);
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

void	run_without_pipe(t_struct *data, char **tok)
{
	if (data->type == BU_EXIT)
		exit_builtins();
	else if (data->type == BU_UNSET)
		unset_env(data, tok[1]);
	else if (data->type == BU_EXPORT)
		export_env(data, tok[1]);
}
