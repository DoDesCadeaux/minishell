/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 23:12:38 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/19 06:37:18 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*add_space(char *side, char *line, int i)
{
	char	*tmp1;
	char	*tmp2;
	char	*str;

	if (!ft_strcmp(side, "before"))
	{
		tmp1 = str_dup_parts(line, i - 1, 0);
		tmp2 = str_dup_parts(line, ft_strlen(line), i);
		tmp1 = ft_strjoin(tmp1, " ");
		str = ft_strjoin(tmp1, tmp2);
	}
	if (!ft_strcmp(side, "after"))
	{
		tmp1 = str_dup_parts(line, i, 0);
		tmp2 = str_dup_parts(line, ft_strlen(line), i + 1);
		tmp1 = ft_strjoin(tmp1, " ");
		str = ft_strjoin(tmp1, tmp2);
	}
	free(tmp1);
	free(tmp2);
	return (str);
}

static char	*left_redirection(char *line, int i)
{
	if (line[i - 1] != ' ' && line[i - 1] != '<')
	{
		line = add_space("before", line, i);
		i++;
	}
	if (line[i + 1] == '<')
		i++;
	if (line[i + 1] != ' ' && line[i + 1] != '<')
		line = add_space("after", line, i);
	return (line);
}

static char	*right_redirection(char *line, int i)
{
	if (line[i - 1] != ' ' && line[i - 1] != '>')
	{
		line = add_space("before", line, i);
		i++;
	}
	if (line[i + 1] == '>')
		i++;
	if (line[i + 1] != ' ' && line[i + 1] != '>')
		line = add_space("after", line, i);
	return (line);
}

static char	*check_spaces_redirections(char *line_to_pars)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line_to_pars);
	while (line_to_pars[i])
	{
		if (line_to_pars[i] == 39 || line_to_pars[i] == 34)
			i = skip_all_quotes(line_to_pars, i);
		if ((i + 1 <= len) && line_to_pars[i] == '>')
			line_to_pars = right_redirection(line_to_pars, i);
		else if ((i + 1 <= len) && line_to_pars[i] == '<')
			line_to_pars = left_redirection(line_to_pars, i);
		i++;
	}
	return (line_to_pars);
}

int		quote(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

// char	*parsing(char *line, t_struct *data)
// {
// 	int	i;

// 	i = 0;
// 	line = remove_multi_space(line);
// 	if (!quote(line))
// 	{
// 		line = parsing_dollar(data, line, ft_strlen(line));
// 		return (line);
// 	}
// 	while (line[i])
// 	{
// 		if (line[i] == 34)
// 		{
// 			i++;
// 			while (line[i] && line[i] != 34)
// 				i++;
// 			if (line[i])
// 				i++;
// 			line = remove_double_quotes(line);
// 			line = parsing_dollar(data, line, i);
// 		}
// 		else if (line[i] && line[i] == 39)
// 		{
// 			i++;
// 			while (line[i] && line[i] != 39)
// 				i++;
// 			if (line[i])
// 				i++;
// 			line = remove_single_quotes(line);
// 		}
// 		i++;
// 	}
// 	line = check_spaces_redirections(line);
// 	return (line);
// }


char	*parsing(char *line, t_struct *data)
{
	int	i;

	i = 0;
	line = remove_multi_space(line);
	while (line[i])
	{
		if (line[i] == 39)
		{
			i++;
			while (line[i] != 39)
				i++;
			i++;
		}
		if (line[i] == '$')
		{
			line = parsing_dollar(data, line, i);
			i = 0;
		}
		i++;
	}
	line = remove_double_quotes(line);
	line = remove_single_quotes(line);
	line = check_spaces_redirections(line);
	return (line);
}
