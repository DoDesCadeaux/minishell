/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:32:28 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 13:32:31 by pamartin         ###   ########.fr       */
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

char	*prompt(void)
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
		line = prompt();
		if (syntax_errors(line))
			continue ;
		if (!is_pipe(line))
		{
			tok = tokenisation(line, tok, data);
			if (tok)
			{
				call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]));
				ft_clear_split(tok);
			}
			free(tok);
		}
		else
			pipe_exec(data, tok, line);
	}
	return (0);
}
