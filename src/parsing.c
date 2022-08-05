/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:35:47 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/05 18:35:50 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	ft_strcmp(char *s1, char *s2)
{
	int len1;
	int	len2;
	int	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 != len2)
		return (1);
	while (s1[i])
	{
		if (s1[i]!= s2[i])
			return (1);
		i++;
	}
	return (0);
	
}

char	**parsing(char *line)
{
	int		i;
	char	**line_split;
	char	**parse;
	int		fd1;
	int		fd2;
	char	*info;
	char	*tmp;

	parse = malloc(sizeof(char *) * 3 + 1);
	if (!parse)
		return (NULL);
	line_split =  ft_split(line, ' ');
	i = 0;
	if (!ft_strcmp(line_split[i], LESS))
	{
		fd1 = open(line_split[i + 1], O_RDONLY);
		if (fd1 < 0)
		{
			printf("ERROR 12\n"); ///youpi: No such file or directory
			exit(EXIT_FAILURE); //Pas de vrai exist, on veux pas sortir completement du programme!
		}
		else
		{
			info = ft_itoa(fd1);
			parse[0] = ft_strdup(info);
		}
		
		i = 2;
		//printf("\n\n first step ok avec i = %d\n\n", i);
	}
	else
	{
		//BEUG ICI
		//printf("ici");
		parse[0] = ft_strdup("0");
		//printf("\n\n first step ok avec i = %d\n\n", i);
	}
	while (line_split[i])
	{
		//check redirection d'entree simple
	
		if (ft_strcmp(line_split[i], GREAT) || ft_strcmp(line_split[i], DGREAT) || ft_strcmp(line_split[i], PIPE))
		{
			info = ft_strdup(line_split[i]);
			i++;
		}
		while (line_split[i] && (ft_strcmp(line_split[i], GREAT) || ft_strcmp(line_split[i], DGREAT) || ft_strcmp(line_split[i], PIPE)))
		{
			tmp = ft_strjoin(info, " ");
			info = ft_strjoin(tmp, line_split[i]);
			
			free(tmp);
			i++;
		}
		//ici check des dolls
		parse[1] = ft_strdup(info);
		free(info);
		parse[2] = ft_strdup("1"); // pas prise en compte
		
	}
	parse[3] = 0;
	ft_free_split(line_split);
	return (parse);
}

void	call_execute(char **parse, t_struct *data)
{
	char *tmp;
	char *cmd;
	char **full_cmd;
	
	tmp = ft_strdup(parse[1]);
	full_cmd = ft_split(tmp, ' ');
	cmd = full_cmd[0];
	free(tmp);
	if (!ft_strcmp(full_cmd[0], ECHO))
		echo(parse[1]);
	else if (!ft_strcmp(cmd, CD))
		cd_builtin(data, full_cmd[1]);
	else if (!ft_strcmp(cmd, PWD))
		pwd_builtin(data);
	else if (!ft_strcmp(cmd, ENV))
		env_builtin(data);
	else if (!ft_strcmp(cmd, EXPORT))
		export_env(data, cmd);
	else if (!ft_strcmp(cmd, UNSET))
		unset_env(data, cmd);


	

}
