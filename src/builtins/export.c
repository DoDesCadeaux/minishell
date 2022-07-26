/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:11:34 by pamartin          #+#    #+#             */
/*   Updated: 2022/11/30 16:02:16 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	bad_id(char *export)
{
	int	end;
	int	i;

	i = 1;
	end = ft_strfchr(export, '=');
	while (export[i] && i < end)
	{
		if (!ft_isalnum((int)export[i]) && export[i] != 95)
			return (1);
		i++;
	}
	return (0);
}

int	is_real_export(char *export)
{
	int	i;

	i = 0;
	while (export[i])
	{
		if (export[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	export_env(t_struct *data, char *cmd)
{
	int		i;
	char	**full_cmd;

	i = 1;
	full_cmd = ft_split_pipe(cmd, ' ');
	while (full_cmd[i])
	{
		full_cmd[i] = parsing(full_cmd[i], data);
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
	new_matrix = malloc(sizeof(char *) * (len_matrix + 1));
	protect_malloc(new_matrix);
	i = 0;
	while (matrix[i] && i <= len_matrix)
	{
		new_matrix[i] = malloc(sizeof(char) * ft_strlen(matrix[i]) + 1);
		protect_malloc(new_matrix[i]);
		ft_strcpy(new_matrix[i], matrix[i]);
		i++;
	}
	new_matrix[i] = malloc(sizeof(char) * len_nline + 1);
	protect_malloc(new_matrix[i]);
	ft_strcpy(new_matrix[i], n_line);
	new_matrix[i + 1] = 0;
	ft_free_split(matrix);
	return (new_matrix);
}

t_struct	*export_global(t_struct *d, char *ex)
{
	int	i;

	i = 0;
	while (d->envp[i] && d->pipe != 1)
	{
		if (is_env_var(d, ex, i))
		{
			if (ft_strncmp(d->envp[i], ex, ft_strlen(d->envp[i]) + 1))
			{
				free(d->envp[i]);
				d->envp[i] = malloc(sizeof(char) * ft_strlen(ex) + 1);
				protect_malloc(d->envp[i]);
				ft_strcpy(d->envp[i], ex);
				return (d);
			}
			return (d);
		}
		i++;
	}
	if (ft_strfchr(ex, '=') == 0 || (!ft_isalpha((int)ex[0])
			&& ex[0] != 95) || bad_id(ex))
		ft_error(msg("ex", ex, "not a valid identifier", 0), 1);
	else if (ft_strfchr(ex, '=') >= 1 && d->pipe == 0)
		d->envp = add_var(d->envp, len_split(d->envp), ft_strlen(ex), ex);
	return (d);
}
