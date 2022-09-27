/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:32:28 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/27 14:02:52 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	show_ghost(void)
{
	printf(G " /▔▔▔▔▔▔▔▔\\  ╭━━━━╮\n" R);
	printf(G "| ╭--╮╭--╮ | |BOO…|\n" R);
	printf(G "| |╭-╯╰-╮| | ╰━┳━━╯\n" R);
	printf(G "| ╰╯ ╭╮ ╰╯ |━━━╯ \n" R);
	printf(G "|    ╰╯    | \n" R);
	printf(G "|/\\_/\\/\\_/\\| \n" R);
}

static char	*prompt(void)
{
	char	*str;

	run_signals(1);
	// show_ghost();
	str = readline("MINISHELL~> ");
	if (!str)
		ft_error_exit("exit", 1);
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
		line = preparsing(line);
		line = remove_multi_space(line);
		if (is_metachar(line[ft_strlen(line) - 1]))
			line = get_full_pipe(line);
		run_program(data, tok, line);
	}
	return (0);
}
