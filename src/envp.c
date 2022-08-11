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

t_struct	*export_env(t_struct *data, char *export)
{
	//Fonctionnel en l'etat mais a revoir avec le parsing et le format des donnees
	//il est possible d'export plusieurs variables en même temps
	//Plusieurs possibilités:
	//	->on rappel cette fonction dans une boucle qui pqsse tous les arg un a un
	//	->tous est pris en compte dans cette fonction
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
		data->envp = add_var(data->envp, len_split(data->envp), ft_strlen(export), export);
	return (data);
}

t_struct	*unset_env(t_struct *data, char *unset)
{
	//Fonctionnel en l'etat mais a revoir avec le parsing et le format des donnees
	//il est possible d'export plusieurs variables en même temps
	//Plusieurs possibilités:
	//	->on rappel cette fonction dans une boucle qui pqsse tous les arg un a un
	//	->tous est pris en compte dans cette fonction
	int i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], unset, ft_strlen(unset)))
		{
			while(i < len_split(data->envp)-1)
			{
				free(data->envp[i]);
				data->envp[i] = 0x0;
				data->envp[i] = malloc(sizeof(char) * ft_strlen(data->envp[i + 1]));
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
	//Fonctionnel en l'etat
	//Attention si il y a qqc apres env -> msg d'erreur
	//Messages d'erreurs a vérifier
	int	i;

	i = 0;
	while (data->envp[i])
	{
		ft_putstr_fd(data->envp[i], ft_atoi(parse[2]));
		ft_putchar_fd('\n', ft_atoi(parse[2]));
		i++;
	}
}
