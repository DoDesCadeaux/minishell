/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:10:37 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 13:10:40 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_pwd(t_struct *data, int status)
{
	char	*update_pwd;

	update_pwd = NULL;
	update_pwd = getcwd(update_pwd, 200);
	protect_malloc(update_pwd);
	free(data->pwd[status]);
	data->pwd[status] = ft_strdup(update_pwd);
	free(update_pwd);
}

t_struct	*update_var(t_struct *data, char *export, int i)
{
	if (ft_strncmp(data->envp[i], export, ft_strlen(export))
		|| ft_strlen(export) < ft_strlen(data->envp[i]))
	{
		free(data->envp[i]);
		data->envp[i] = malloc(sizeof(char) * ft_strlen(export) + 1);
		protect_malloc(data->envp[i]);
		ft_strcpy(data->envp[i], export);
		printf("update = %s\n", data->envp[i]);
	}
	return (data);
}

t_struct	*update_envp(t_struct *data, char *type)
{
	int		i;
	char	*export;
	char	*update_pwd;

	update_pwd = NULL;
	update_pwd = getcwd(update_pwd, 200);
	if (!update_pwd)
		return (NULL);
	export = ft_strjoin(type, update_pwd);
	i = 0;
	while (data->envp[i])
	{
		if (is_env_var(data, export, i))
		{
			data = update_var(data, export, i);
			printf("lolilo\n");
		}
			
		i++;
	}
	free(update_pwd);
	free(export);
	return (data);
}

t_struct	*change_directory(t_struct *data, char *directory)
{
	int	check;

	update_pwd(data, 1);
	data = update_envp(data, "OLDPWD=");
	printf("1\n");
	check = chdir(directory);
	if (check < 0)
		printf("merde\n");
	update_pwd(data, 0);
	data = update_envp(data, "PWD=");
	printf("2\n\n\n");
	return (data);
}

void	cd_builtin(t_struct *data, char **tok)
{
	int		check;
	char	*tmp;
	char	**full_cmd;

	full_cmd = ft_split(tok[1], ' ');
	check = access(full_cmd[1], F_OK);
	if (check == 0)
		data = change_directory(data, full_cmd[1]);
	else if (!ft_strcmp(full_cmd[1], "-"))
	{
		tmp = ft_strdup(data->pwd[1]);
		data = change_directory(data, tmp);
		free(tmp);
		printf("tok[2]= %s\n", tok[2]);
		ft_putstr_fd(data->pwd[0],ft_atoi(tok[2]));
		ft_putchar_fd('\n', ft_atoi(tok[2]));
	}
	else if (!ft_strcmp(full_cmd[1], "~"))
	{
		tmp = ft_strjoin("/Users/", data->user);
		data = change_directory(data, tmp);
		free(tmp);
	}
	else
		printf(" ERROR CD\n");
}
