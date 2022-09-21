/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                             :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:32:28 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 13:32:31 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*join_and_replace(t_struct *data, char *tmp1, char *replace, char *tmp3)
{
	char	*dst;
	char	*tmp_dollar;
	int		i;

	tmp_dollar = var_exist(data, replace);
	if (tmp_dollar)
	{
		i = 0;
		while (tmp_dollar[i] != '=' && tmp_dollar[i])
			i++;
		i++;
		tmp_dollar = str_dup_parts(tmp_dollar, ft_strlen(tmp_dollar), i);
		dst = ft_strjoin(tmp1, tmp_dollar);
		dst = ft_strjoin(dst, tmp3);
	}
	else
		dst = ft_strjoin(tmp1, tmp3);
	free(tmp_dollar);
	return (dst);
}

static char	*replace_or_erase(char *line, t_struct *data)
{
	if (var_exist(data, data->tmp_2))
		line = join_and_replace(data, data->tmp_1, data->tmp_2, data->tmp_3);
	else
		line = ft_strjoin(data->tmp_1, data->tmp_3);
	return (line);
}

static char	*replace_error_code(t_struct *data, char *line_pars, int i)
{
	char	*dst;
	int		y;

	data->tmp_1 = str_dup_parts(line_pars, i - 1, 0);
	i++;
	data->tmp_2 = ft_itoa(error_code);
	y = i + 1;
	while (line_pars[i])
		i++;
	data->tmp_3 = str_dup_parts(line_pars, i, y);
	dst = ft_strjoin(data->tmp_1, data->tmp_2);
	dst = ft_strjoin(dst, data->tmp_3);
	return (dst);
}

static	int	is_error_code(char *line, int i)
{
	if (line[i] == '$' && line[i + 1] == '?')
	{
		i += 2;
		if (is_end_of_dollar(line[i]) || line[i] == '\0')
			return (1);
	}
	return (0);
}

char	*parsing_dollar(t_struct *data, char *line_pars, int i)
{
	int	y;

	
	while (line_pars[i])
	{
		if (is_error_code(line_pars, i))
			line_pars = replace_error_code(data, line_pars, i);
		if (line_pars[i] == '$')
		{
			data->tmp_1 = str_dup_parts(line_pars, i - 1, 0);
			i++;
			y = i;
			i = update_i(line_pars, i);
			data->tmp_2 = str_dup_parts(line_pars, i - 1, y);
			y = i;
			while (line_pars[i])
				i++;
			data->tmp_3 = str_dup_parts(line_pars, i, y);
			line_pars = replace_or_erase(line_pars, data);
			i = ft_strlen(line_pars) - 1;
		}
		i++;
	}
	return (line_pars);
}
