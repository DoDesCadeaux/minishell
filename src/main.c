/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:32:28 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/21 18:00:53 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error_exit(char *message, int code)
{
	error_code = code;
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(error_code);
}

void	error_perror(void)
{
	perror("minishell");
	error_code = ERRNO;
	exit(EXIT_FAILURE);
}

void	ft_error(char *message, int code)
{
	error_code = code;
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
}

void	show_ghost(void)
{
	printf(G " /▔▔▔▔▔▔▔▔\\  ╭━━━━╮\n"R);
	printf(G "| ╭--╮╭--╮ | |BOO…|\n" R);
	printf(G "| |╭-╯╰-╮| | ╰━┳━━╯\n" R);
	printf(G "| ╰╯ ╭╮ ╰╯ |━━━╯ \n" R);
	printf(G "|    ╰╯    | \n" R);
}

static char	*prompt(void)
{
	char	*str;

	run_signals(1);
	show_ghost();
	str = readline(G "|/\\_/\\/\\_/\\|	->" R);
	if (!str)
		ft_error_exit("", 1);
	add_history(str);
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	*data;
	char		*line;
	char		**tok;

	data = initializer(envp, argc, argv);
	while (19)
	{
		tok = malloc(sizeof(char *) * 4 + 1);
		protect_malloc(tok);
		run_signals(1);
		line = prompt();
		if (syntax_errors(line))
			continue ;
		line = preparsing(line);
		line = remove_multi_space(line);
		if (is_metachar(line[ft_strlen(line) - 1]))
			line = get_full_pipe(line);
		if (!is_pipe(line))
		{
			data->pipe = 0;
			tok = tokenisation(line, tok, data);
			if (tok)
			{
				call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]));
				ft_clear_split(tok);
			}
			free(tok);
		}
		else
		{
			data->pipe = 1;
			pipe_exec(data, tok, line);
		}
	}
	return (0);
}
