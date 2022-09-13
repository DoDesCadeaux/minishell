/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:11:34 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 13:11:36 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_env(t_struct *data, char *cmd)
{
	int		i;
	char	**full_cmd;

	i = 1;
	full_cmd = ft_split(cmd, ' ');
	while (full_cmd[i])
	{
		data = export_global(data, full_cmd[i]);
		i++;
	}
	ft_free_split(full_cmd);
}

char	**add_var(char **matrix, int len_matrix, int len_nline, char *n_line)
{
	char	**new_matrix;
	int		i;

	if (len_matrix == 0)
		len_matrix++;
	new_matrix = NULL;
	new_matrix[0] = ft_malloc(len_matrix);
	i = 0;
	while (matrix[i] && i <= len_matrix)
	{
		new_matrix[i] = ft_malloc(ft_strlen(matrix[i]));
		ft_strcpy(new_matrix[i], matrix[i]);
		i++;
	}
	new_matrix[i] = malloc(len_nline);
	ft_strcpy(new_matrix[i], n_line);
	new_matrix[i + 1] = 0;
	ft_free_split(matrix);
	return (new_matrix);
}

t_struct	*export_global(t_struct *data, char *export)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (is_env_var(data, export, i))
		{
			if (ft_strncmp(data->envp[i], export, ft_strlen(data->envp[i])))
			{
				free(data->envp[i]);
				data->envp[i] = ft_malloc(ft_strlen(export));
				ft_strcpy(data->envp[i], export);
				return (data);
			}
		}
		i++;
	}
	if (ft_strfchr(export, '=') > 1)
		data->envp = add_var(data->envp, len_split(data->envp),
				ft_strlen(export), export);
	return (data);
}
