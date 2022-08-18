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
/*
void	welcome(void)
{
	printf(Y "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =");
	printf(Y " = = = = = = = = = = = = = = = = = \n" R);
	printf(Y "= " G " _  .-')                .-') _              .-')    ('-.");
	printf(G " .-.   ('-.                           "Y "=\n" R);
	printf(Y "= "G "('.( OO )_             ( OO ) )            ( OO ). ( OO )");
	printf(G ")  / _(  OO)                         "Y "=\n" R);
	printf(Y "=  ,--.   ,--." G ")" Y " ,-.-" G "')" Y " ,--." G "/" Y " ,--,");
	printf(G "'" Y " ,-.-" G "')       (_)" Y "---" G "\\_)" Y ",--. ,--." );
	printf(G "(" Y ",------.,--.      ,--.       =\n" R);
	printf(Y "=  |   `.'   |  |  |" G "OO)" Y "|   \\ |  |" G "\\ " Y "|  |" );
	printf(G "OO)" Y "      /    _ | |  | |  | |  .---'|  |" G ".-')" );
	printf(Y "  |  |" G ".-')" Y"   =\n" R);
	printf(Y "=  |         |  |  |  " G "\\" Y"|    \\|  | " G ")" );
	printf(Y"|  |  " G "\\" Y "      \\  :` `. |   .|  | |  |    |  | " );
	printf(G "OO )" Y " |  | " G "OO )" Y"  =\n" R);
	printf(Y "=  |  |'.'|  |  |  |" G"(_/" Y "|  .     |" G "/" Y " |  |" );
	printf(G "(_/" Y "       '..`''." G ")" Y "|       |" G "(" );
	printf(Y "|  '--. |  |" G "`-' |" Y " |  |" G "`-' |"Y"  =\n" R);
	printf(Y "=  |  |   |  | " G "," Y "|  |" G "_.'" Y "|  |\\    | " );
	printf(G "," Y "|  |" G "_.'" Y "      .-._)   \\|  .-.  | |  .--'" );
	printf(G"(" Y "|  '---." G "'(" Y "|  '---." G"'" Y"  =\n" R);
	printf(Y "=  |  |   |  |" G"(_" Y "|  |   |  | \\   |" G"(_" );
	printf(Y "|  |         \\       /|  | |  | |  `---.|      |  |      ");
	printf(Y"|   =\n" R);
	printf(Y "=  `--'   `--'  `--'   `--'  `--'  `--'          `-----' ");
	printf(Y"`--' `--' `------'`------'  `------'   =\n" R);
	printf(Y "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ");
	printf(Y "= = = = = = = = = = = = = = = = = = \n" R);
}*/

char	*prompt(void)
{
	char	*str;

	printf(G " /▔▔▔▔▔▔▔▔\\  ╭━━━━╮\n"R);
	printf(G "| ╭--╮╭--╮ | |BOO…|\n" R);
	printf(G "| |╭-╯╰-╮| | ╰━┳━━╯\n" R);
	printf(G "| ╰╯ ╭╮ ╰╯ |━━━╯ \n" R);
	printf(G "|    ╰╯    | \n" R);
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
	argv = NULL;
	data = malloc(sizeof(t_struct));
	if (!data)
		return (0);
	welcome();
	data = clone_env(envp, data);
	while (1)
	{
		tok = malloc(sizeof(char *) * 4 + 1);
		if (!tok)
			return (0);
		line = prompt();
		tok = tokenisation(line, tok);
		call_execute(tok, data);
		ft_free_split(tok);
	}
	return (0);
}
