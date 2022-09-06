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
	str = readline(G "|/\\_/\\/\\_/\\|	" R);
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	*data;
	char		*line;
	char		**tok;

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
		if (!line)
			exit(EXIT_FAILURE);
		if (syntax_errors(line))	//ligne est vide || que des espaces || quotes ouverts
			continue;
		add_history(line);
		line = parsing(line, data);

		//a mettre dans la tokenisation/exec ??
//		line = remove_single_quotes(line);
//		line = remove_double_quotes(line);

		tok = tokenisation(line, tok);
		call_execute(tok, data);
		ft_free_split(tok);
	}
	//rl_clear_history();
	return (0);
}
