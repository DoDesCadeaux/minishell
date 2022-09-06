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

int	is_only_spaces(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'
		   || line[i] == '\v' || line[i] == '\f' || line[i] == '\r')
		i++;
	if (i == ft_strlen(line))
		return (1);
	return (0);
}

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
		if (*line == '\0')        //verifie si la ligne est vide
			continue;
		if (is_only_spaces(line)) //verifie s'il y a que des espaces
			continue;
		if (!single_quote(line)) //verifie s'il y a des quotes ouverts
			continue;
		add_history(line);
		line = parsing_dollar(data, line);  //remplace les $ s'il faut (pas les single quotes)
		tok = tokenisation(line, tok);
		call_execute(tok, data);
		ft_free_split(tok);
	}
	//rl_clear_history();
	return (0);
}
