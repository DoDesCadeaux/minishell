/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:14:33 by pamartin          #+#    #+#             */
/*   Updated: 2022/11/17 15:50:20 by algaspar         ###   ########.fr       */
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

char	*ft_strdup_quotes(char *src)
{
	int		i;
	int		j;
	char	*dup;

	dup = malloc(sizeof(char) * ft_strlen(src) + 3);
	if (!dup)
		return (NULL);
	i = 0;
	while (src[i - 1] != '=')
	{
		dup[i] = src[i];
		i++;
	}
	j = i;
	dup[i++] = '\"';
	while (src[j])
	{
		dup[i] = src[j];
		i++;
		j++;
	}
	dup[i++] = '\"';
	dup[i] = '\0';
	return (dup);
}

void	sort_export(char **export)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (export[i])
	{
		j = i;
		while (export[j])
		{
			if (ft_cmp(export[i], export[j]) > 0)
			{
				tmp = export[i];
				export[i] = export[j];
				export[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_export(char **export)
{
	int	i;

	i = 0;
	while (export[i])
	{
		printf("declare -x %s\n", export[i]);
		i++;
	}
}

void	export_empty(t_struct *data)
{
	char	**export;
	int		i;
	int		j;

	export = malloc(sizeof(char *) * len_split(data->envp));
	protect_malloc(export);
	i = 0;
	j = 0;
	while (data->envp[i])
	{
		if (ft_strncmp("_=/usr/bin/env", data->envp[i], 14) != 0)
		{
			export[j] = ft_strdup_quotes(data->envp[i]);
			j++;
		}
		i++;
	}
	export[j] = NULL;
	sort_export(export);
	print_export(export);
	ft_free_split(export);
	exit(EXIT_SUCCESS);
}
