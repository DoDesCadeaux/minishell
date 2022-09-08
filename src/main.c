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
#include <errno.h>

void	show_ghost()
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
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	*data;
	char		*line;
	char		**tok;
	int			type;

	if (argc != 1)
		return (1);
	printf("ARGV[0] = %s\n", argv[0]);
	data = malloc(sizeof(t_struct));
	if (!data)
		return (0);
	welcome();
	data = clone_env(envp, data);
	while (19)
	{
		tok = malloc(sizeof(char *) * 4 + 1);
		if (!tok)
			return (0);
		line = prompt();
//		printf("j'ai refait\n");
		if (!line)
			exit(EXIT_FAILURE);
		if (syntax_errors(line))
		{
			printf("Syntax ERROR\n");
			continue;
		}
		add_history(line);

		//a mettre dans la tokenisation/exec ??
//		line = remove_single_quotes(line);
//		line = remove_double_quotes(line);

		if (!is_pipe(line))
		{
//			line = parsing(line, data);
			tok = tokenisation(line, tok, data);
			type = check_type(tok);
			call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]), type);
			ft_free_split(tok);
		}
		else
			printf("TEST\n");
//			pipe_exec(data, tok, line);

	}
	return (0);
}
