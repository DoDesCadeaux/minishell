/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:38:59 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/05 18:39:00 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**add_var(char **matrix, int len_matrix, int len_nline, char *n_line)
{
	char	**new_matrix;
	int		i;

	if (len_matrix == 0)
		len_matrix++;
	new_matrix = malloc(sizeof(char *) * (len_matrix + 1));
	if (!new_matrix)
		return (NULL);
	i = 0;
	while (matrix[i] && i <= len_matrix)
	{
		new_matrix[i] = malloc(sizeof(char) * ft_strlen(matrix[i]) + 1);
		if (!new_matrix[i])
			return (NULL);
		ft_strcpy(new_matrix[i], matrix[i]);
		i++;
	}
	new_matrix[i] = malloc(sizeof(char) * len_nline + 1);
	if (!new_matrix[i])
		return (NULL);
	ft_strcpy(new_matrix[i], n_line);
	new_matrix[i + 1] = 0;
	ft_free_split(matrix);
	return (new_matrix);
}

void	*init_pwd(t_struct *data)
{
	char	*pwd_tmp;

	pwd_tmp = NULL;
	pwd_tmp = getcwd(pwd_tmp, 200);
	if (!pwd_tmp)
		return (NULL);
	data->pwd = malloc(sizeof(char *) * 2 + 1);
	if (!data->pwd)
		return (NULL);
	data->pwd[0] = ft_strdup(pwd_tmp);
	if (!data->pwd[0])
		return (NULL);
	data->pwd[1] = ft_strdup(pwd_tmp);
	if (!data->pwd[1])
		return (NULL);
	data->pwd[2] = 0;
	free(pwd_tmp);
	return (NULL);
}

t_struct	*update_lvl(t_struct *data, char *lvl)
{
	char	*tmp;
	int		new_lvl;

	lvl = ft_strchr(lvl, 61);
	if (is_numeric(lvl + 1))
	{
		new_lvl = ft_atoi(lvl + 1) + 1;
		//warning: shell level (1501) too high, resetting to 1
		if (new_lvl > 1000)
			new_lvl = 1;
		tmp = ft_itoa(new_lvl);
		lvl = ft_strjoin("SHLVL=", tmp);
		if (new_lvl == 1000)
			data = export_global(data, "SHLVL=");
		else
			data = export_global(data, lvl);
		free(lvl);
		free(tmp);
	}
	return (data);
}

t_struct	*clone_env(char **env, t_struct *data)
{
	int		i;
	char	*lvl;

	data->envp = malloc(sizeof(char *) * len_split(env) + 1);
	if (!data->envp)
		return (NULL);
	i = 0;
	while (env[i])
	{
		data->envp[i] = ft_strdup(env[i]);
		i++;
	}
	data->envp[i] = 0;
	lvl = var_exist(data, "SHLVL");
	if (lvl)
		data = update_lvl(data, lvl);
	else
		data = export_global(data, "SHLVL=1");
	init_pwd(data);
	//Si old power existe il faut le free et adress a null
	return (data);
}
