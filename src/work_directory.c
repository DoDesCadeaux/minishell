/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:45:46 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/05 18:45:48 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pwd_builtin(t_struct *data)
{
	char	*pwd;
	char	*tmp;

	pwd = NULL;
	pwd = getcwd(pwd, 200);
	if (!pwd)
		printf("prout pwd\n");
	printf("%s\n", pwd);
	free(pwd);
	pwd = 0x0;
}

void	update_pwd(t_struct *data, int status)
{
	char	*update_pwd;

	update_pwd = NULL;
	update_pwd = getcwd(update_pwd, 200);
	//protection malloc
	free(data->pwd[status]);
	data->pwd[status] = ft_strdup(update_pwd);
	free(update_pwd);
}

t_struct	*update_envp(t_struct *data, char *type)
{
	int		i;
	char	*export;
	char	*update_pwd;

	update_pwd = NULL;
	update_pwd = getcwd(update_pwd, 200);
	//protection malloc
	export = ft_strjoin(type, update_pwd);
	//printf("export ===> %s\n", export);
	i = 0;
	while (data->envp[i])
	{
		if (is_env_var(data, export, i))
		{
			if (ft_strncmp(data->envp[i], export, ft_strlen(export)) || ft_strlen(export) < ft_strlen(data->envp[i]))
			{
				free(data->envp[i]);
				data->envp[i] = malloc(sizeof(char) * ft_strlen(export) + 1);
				//protection
				ft_strcpy(data->envp[i], export);
			}
		}
		i++;
	}
	free(update_pwd);
	free(export);
	return (data);
}

void	cd_builtin(t_struct *data, char *directory)
{
	int check;

	//Possibilité du cd
	check = access(directory, F_OK);
	if (check == 0)
	{
		update_pwd(data, 1);
		data = update_envp(data, "OLDPWD=");
		check = chdir(directory);
		//protection
		update_pwd(data, 0);
		data = update_envp(data, "PWD=");
	}
	else
		printf(" ERROR CD\n");
}