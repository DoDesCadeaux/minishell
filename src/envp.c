/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:42:23 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/05 18:42:25 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <errno.h>

t_struct	*export_env(t_struct *data, char **full_cmd)
{
	int	i;

	i = 1;
	while (full_cmd[i])
	{
		data = export_global(data, full_cmd[i]);
		i++;
	}
	return (data);
}

t_struct	*unset_env(t_struct *data, char **full_cmd)
{
	int	i;

	i = 1;
	while (full_cmd[i])
	{
		data = unset_global(data, full_cmd[i]);
		i++;
	}
	return (data);
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
				data->envp[i] = malloc(sizeof(char) * ft_strlen(export) + 1);
				if (!data->envp[i])
					return (NULL);
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

t_struct	*unset_global(t_struct *data, char *unset)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], unset, ft_strlen(unset)))
		{
			while (i < len_split(data->envp) - 1)
			{
				free(data->envp[i]);
				data->envp[i] = 0x0;
				data->envp[i] = malloc(sizeof(char)
						* ft_strlen(data->envp[i + 1]));
				ft_strcpy(data->envp[i], data->envp[i + 1]);
				i++;
			}
			free(data->envp[i]);
			data->envp[i] = 0x0;
			return (data);
		}
		i++;
	}
	return (data);
}

void	env_builtin(t_struct *data, char **parse)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		ft_putstr_fd(data->envp[i], ft_atoi(parse[2]));
		ft_putchar_fd('\n', ft_atoi(parse[2]));
		i++;
	}
	//attention message d'erreur
}
