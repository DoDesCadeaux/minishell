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

char	*create_heredoc(char *delimiter)
{
	char	*line;
	char	*info;
	int		here_doc;

	here_doc = open("here_doc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (here_doc < 0)
		printf("ERROR HERE DOC");
	line = get_next_line(0);
	while (line && (ft_strncmp(line, delimiter, ft_strlen(delimiter))
			|| ft_strlen(delimiter) + 1 != ft_strlen(line)))
	{
		write(here_doc, line, ft_strlen(line));
		line = get_next_line(0);
	}
	free(line);
	info = ft_itoa(here_doc);
	return (info);
}

int	parse_0(char **parse, char **line_split, int i)
{
	char	*info;

	if (!ft_strcmp(line_split[i], LESS))
	{
		info = get_fd(line_split[i + 1], REDIR_STDIN, NULL);
		if (!info)
		{
			printf("ERROR FD1\n"); ///youpi: No such file or directory
			exit(EXIT_FAILURE); //Pas de vrai exist!
		}
		i = 2;
	}
	else if (!ft_strcmp(line_split[i], DLESS))
	{
		info = create_heredoc(line_split[i + 1]);
		i = 2;
	}
	else
		info = get_fd(NULL, REDIR_STDIN, NULL);
	parse[0] = ft_strdup(info);
	free(info);
	return (i);
}

int	parse_1(char **parse, char **line_split, int i)
{
	char	*info;
	char	*tmp;

	if (ft_strcmp(line_split[i], GREAT) && ft_strcmp(line_split[i], DGREAT)
		&& ft_strcmp(line_split[i], PIPE))
	{
		info = ft_strdup(line_split[i]);
		i++;
	}
	while (line_split[i])
	{
		if (ft_strcmp(line_split[i], GREAT) && ft_strcmp(line_split[i], DGREAT)
			&& ft_strcmp(line_split[i], PIPE))
		{
			tmp = ft_strjoin(info, " ");
			info = ft_strjoin(tmp, line_split[i]);
			free(tmp);
		}
		else
			break ;
		i++;
	}
	parse[1] = ft_strdup(info);
	free(info);
	return (i);
}

char	**parsing(char *line)
{
	char	**line_split;
	char	**parse;
	char	*tmp;
	int		i;

	parse = malloc(sizeof(char *) * 3 + 1);
	if (!parse)
		return (NULL);
	line_split = ft_split(line, ' ');
	i = 0;
	i = parse_0(parse, line_split, i);
	i = parse_1(parse, line_split, i);
	if (line_split[i] && !ft_strcmp(line_split[i], GREAT))
		tmp = get_fd(line_split[i + 1], REDIR_STDOUT, GREAT);
	else if (line_split[i] && !ft_strcmp(line_split[i], DGREAT))
		tmp = get_fd(line_split[i + 1], REDIR_STDOUT, DGREAT);
	else
		tmp = get_fd(NULL, REDIR_STDOUT, NULL);
	parse[2] = ft_strdup(tmp);
	parse[3] = 0;
	free(tmp);
	ft_free_split(line_split);
	return (parse);
}

void	call_execute(char **parse, t_struct *data)
{
	char	**full_cmd;

	full_cmd = ft_split(parse[1], ' ');
	if (!ft_strcmp(full_cmd[0], ECHO))
		echo(parse);
	else if (!ft_strcmp(full_cmd[0], CD))
		cd_builtin(data, full_cmd[1]);
	else if (!ft_strcmp(full_cmd[0], PWD))
		pwd_builtin(data, parse);
	else if (!ft_strcmp(full_cmd[0], ENV))
		env_builtin(data, parse);
	else if (!ft_strcmp(full_cmd[0], EXPORT))
		data = export_env(data, full_cmd);
	else if (!ft_strcmp(full_cmd[0], UNSET))
		data = unset_env(data, full_cmd);
	//else : on lance l'execution classique.
	if (!ft_strcmp(full_cmd[0], DLESS))
		unlink("here_doc"); //pas au point
	ft_free_split(full_cmd);
}
