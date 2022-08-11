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

char	*get_fd(char *file, int type, char *token)
{
	int		fd;
	char	*fd_parse;

	if (type == REDIR_STDIN)
	{
		if (file)
			fd = open(file, O_RDONLY);
		else
			fd = 0;
	}
	else
	{
		if (file && !ft_strcmp(token, GREAT))
			fd = open(file, O_CREAT | O_APPEND | O_RDWR, 0644);
		else if (file && !ft_strcmp(token, DGREAT))
			fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else
			fd = 1;
	}
	if (fd < 0)
		return (NULL);
	fd_parse = ft_itoa(fd);
	return (fd_parse);
}

char	**parsing(char *line)
{
	int		i;
	char	**line_split;
	char	**parse;
	char	*info;
	char	*tmp;

	parse = malloc(sizeof(char *) * 3 + 1);
	if (!parse)
		return (NULL);
	line_split =  ft_split(line, ' ');
	i = 0;
	//Found entry redirection
	if (!ft_strcmp(line_split[i], LESS))
	{
		info = get_fd(line_split[i + 1], REDIR_STDIN, NULL);
		if (!info)
		{
			printf("ERROR FD1\n"); ///youpi: No such file or directory
			exit(EXIT_FAILURE); //Pas de vrai exist, on veux pas sortir completement du programme!
		}
		i = 2;
	}
	else
		info = get_fd(NULL, REDIR_STDIN, NULL);
	parse[0] = ft_strdup(info);
	free(info);


	if (ft_strcmp(line_split[i], GREAT) && ft_strcmp(line_split[i], DGREAT) && ft_strcmp(line_split[i], PIPE))
	{
		info = ft_strdup(line_split[i]);
		i++;
	}
	while (line_split[i])
	{
		if (ft_strcmp(line_split[i], GREAT) && ft_strcmp(line_split[i], DGREAT) && ft_strcmp(line_split[i], PIPE))
		{
			tmp = ft_strjoin(info, " ");
			info = ft_strjoin(tmp, line_split[i]);
			free(tmp);
		}
		else
			break;
		i++;
	}
	parse[1] = ft_strdup(info);
	free(info);


	if (line_split[i] && !ft_strcmp(line_split[i], GREAT))
		tmp = get_fd(line_split[i + 1], REDIR_STDOUT, GREAT);
	else if (line_split[i] && !ft_strcmp(line_split[i], DGREAT))
		tmp = get_fd(line_split[i + 1], REDIR_STDOUT, DGREAT);
	else
		tmp = get_fd(NULL, REDIR_STDOUT, NULL);
	parse[2] = ft_strdup(tmp);
	parse[3] = 0;
	ft_free_split(line_split);

	int y = 0;
	while (parse[y])
	{
		printf("parse[%d] = %s\n", y, parse[y]);
		y++;
	}
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
		echo(parse);
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
	//else : on lance l'execution classique.
}
