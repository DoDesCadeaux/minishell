/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:14:33 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 13:14:35 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_builtin(t_struct *data)
{
	int	i;

	if (!var_exist(data, "PATH"))
		ft_error_exit(msg("env", NULL, MSG_NO_SUCH_FILE, 0), CMD_ERROR);
	if (!find_env_path(data))
		ft_error_exit(msg("env", NULL, "Command not found", 0), CMD_ERROR);
	i = 0;
	while (data->envp[i])
	{
		printf("%s\n", data->envp[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}

char	*add_quotes(char *export)
{
	int		i;
	char	*tmp;
	char	*exportable;
	char	*line;

	i = ft_strpstr(export, "=");
	exportable = ft_strrchr(export, '=');
	tmp = ft_substr(export, 0, i + 1);
	line = ft_strjoin(tmp, "\"");
	free(tmp);
	tmp = ft_strjoin(line, exportable + 1);
	line = ft_strjoin(tmp, "\"");
	free(tmp);
	return (line);
}

char	**rm_last_exe(char **export)
{
	int	i;

	i = 0;
	while (export[i])
	{
		if (!ft_strncmp(export[i], VAR_DECLARE, ft_strlen(VAR_DECLARE)))
		{
			while (i + 1 < len_split(export) - 1)
			{
				free(export[i]);
				export[i] = 0x0;
				export[i] = ft_strdup(export[i + 1]);
				i++;
			}
			free(export[i]);
			export[i] = 0x0;
			return (export);
		}
		i++;
	}
	return (export);
}

char	**export_to_declare(char **export)
{
	int		i;
	char	*tmp;

	i = 0;
	while (export[i])
	{
		tmp = add_quotes(export[i]);
		free(export[i]);
		export[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	return (export);
}

void	export_empty(t_struct *data)
{
	int		i;
	char	**export;

	export = malloc(sizeof(char *) * len_split(data->envp) + 1);
	protect_malloc(export);
	i = 0;
	while (data->envp[i])
	{
		export[i] = malloc(sizeof(char) * ft_strlen(data->envp[i]) + 1);
		protect_malloc(export[i]);
		export[i] = ft_strlcpy(export[i], data->envp[i],
				ft_strlen(data->envp[i]) + 1);
		i++;
	}
	export[i] = 0;
	export = export_to_declare(export);
	export = rm_last_exe(export);
	i = 0;
	while (export[i])
	{
		printf("declare -x ");
		printf("%s\n", export[i]);
		i++;
	}
	ft_free_split(export);
	exit(EXIT_SUCCESS);
}
