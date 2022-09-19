/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:32:28 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/19 14:49:23 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error_exit(char *message, int code)
{
	error_code = code;
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	ft_error(char *message, int code)
{
	error_code = code;
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

void	show_ghost(void)
{
	printf(G " /▔▔▔▔▔▔▔▔\\  ╭━━━━╮\n"R);
	printf(G "| ╭--╮╭--╮ | |BOO…|\n" R);
	printf(G "| |╭-╯╰-╮| | ╰━┳━━╯\n" R);
	printf(G "| ╰╯ ╭╮ ╰╯ |━━━╯ \n" R);
	printf(G "|    ╰╯    | \n" R);
}

// char	*prompt(void)
// {
// 	char	*str;

// 	run_signals(1);
// 	show_ghost();
// 	str = readline(G "|/\\_/\\/\\_/\\|	->" R);
// 	if (!str)
// 		ft_error_exit("", 1);
// 	add_history(str);
// 	return (str);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_struct	*data;
// 	char		*line;
// 	char		**tok;

// 	data = initializer(envp, argc, argv);
// 	while (19)
// 	{
// 		tok = malloc(sizeof(char *) * 4 + 1);
// 		protect_malloc(tok);
// 		line = prompt();
// 		if (syntax_errors(line))
// 			continue ;
// 		if (!is_pipe(line))
// 		{
// 			data->pipe = 0;
// 			tok = tokenisation(line, tok, data);
// 			if (tok)
// 			{
// 				call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]));
// 				ft_clear_split(tok);
// 			}
// 			free(tok);
// 		}
// 		else
// 		{
// 			data->pipe = 1;
// 			pipe_exec(data, tok, line);
// 		}
// 	}
// 	return (0);
// }

typedef struct s_tok
{
	int	fdin;
	int	fdout;
	char	*tok;
}	t_tok;

char	*ft_strjoin_space(char const *s1, char const *s2)
{
	size_t	i;
	size_t	y;
	char	*str;

	if (!s1 || !s2)
		return (0);
	i = 0;
	y = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!str)
		return (0);
	while (s1[i])
		str[y++] = s1[i++];
	str[y++] = ' ';
	i = 0;
	while (s2[i])
		str[y++] = s2[i++];
	str[y] = 0;
	return (str);
}

// char	*skip_spaces(char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i] == ' ' || line[i] == '\t')
// 		i++;
// 	return (line + i);
// }

// int	is_sep(char c)
// {
// 	char sep[] = "><| ";
// 	int	i = 0;

// 	while (sep[i])
// 	{
// 		if (c == sep[i])
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int	count_args(char *line)
// {
// 	int	arg;
// 	int	i;

// 	arg = 0;
// 	i = 0;
// 	line = skip_spaces(line);
// 	if (line[0] == '\0')
// 		return (arg);
// 	while (line[i])
// 	{
		
// 	}
// 	return (arg);
// }

// char	**split_args(char *line)
// {
// 	char	**split;
// 	int		num_args;

// 	if (!line)
// 		return (NULL);
// 	num_args = count_args(line);
// 	if (!num_args)
// 		return (NULL);
// 	split = malloc(sizeof(char *) * num_args + 1);

// 	return (split);
// }

// char	*remove_spaces(char *line)
// {
// 	char	*new_line;
// 	char	**sep_args;
// 	int		i;

// 	new_line = malloc(sizeof(char) * 1);
// 	if (!new_line)
// 		return (NULL);
// 	new_line[0] = '\0';
// 	sep_args = split_args(line);
// 	if (!split_args(line))
// 		return (NULL);
// 	i = 0;
// 	while (sep_args[i])
// 	{
// 		new_line = ft_strjoin_space(new_line, sep_args[i]);
// 		i++;
// 	}
// 	free(line);
// 	ft_free_split(sep_args);
// 	return (new_line);
// }


char	*remove_spaces(char *line)
{
	char	*new_line;
	int		i;

	
	i = 0;
	line = skip_spaces(line);
	
}


int	main(void)
{
	char	*line;

	while (8)
	{
		line = readline("~>");
		line = remove_spaces(line);
		printf("line = %s -- count_args = %d\n", line, count_args(line));
	}
	return (0);
}
