/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_run_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:59:44 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/22 16:06:55 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	run_bad_binary(t_struct *data, char *cmd)
{
	char	**cmd_arg;

	cmd_arg = ft_split_pipe(cmd, ' ');
	if (!cmd_arg)
		ft_error("minishell: error malloc", MALLOC);
	else if (!cmd_arg[0])
		ft_error(msg(cmd, NULL, "Command not found"), CMD_ERROR);
	else if (!var_exist(data, "PATH"))
		ft_error(msg(cmd_arg[0], NULL, "No such file or directory"), CMD_ERROR);
	else if (!ft_strncmp(cmd, "./", 2))
		ft_error(msg(cmd_arg[0] + 2, NULL, "No such file or directory"), CMD_ERROR);
	else if (!ft_strncmp(cmd, "/", 1))
		ft_error(msg(cmd_arg[0], NULL, "No such file or directory"), CMD_ERROR);
	else
		ft_error(msg(cmd_arg[0], NULL, "Command not found"), CMD_ERROR);
	ft_free_split(cmd_arg);
}

void	run_exec(t_struct *data, char **tok)
{
	printf("run exec : %p\n", tok);
	if (data->type == BINARY)
		execute(data, tok[1]);
	else if (data->type == BU_ECHO)
		echo(tok);
	else if (data->type == BU_PWD)
		pwd_builtin(data);
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
