/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:54:04 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/05 14:54:06 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	welcome(void)
{
	printf(YELLOW "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n" RESET);
	printf(YELLOW "= " GREEN " _  .-')                .-') _              .-')    ('-. .-.   ('-.                           "YELLOW "=\n" RESET);
	printf(YELLOW "= "GREEN "('.( OO )_             ( OO ) )            ( OO ). ( OO )  / _(  OO)                          "YELLOW "=\n" RESET);
	printf(YELLOW "=  ,--.   ,--." GREEN ")" YELLOW " ,-.-" GREEN "')" YELLOW " ,--." GREEN "/" YELLOW " ,--," GREEN "'" YELLOW " ,-.-" GREEN "')       (_)" YELLOW "---" GREEN "\\_)" YELLOW ",--. ,--." GREEN "(" YELLOW ",------.,--.      ,--.       =\n" RESET);
	printf(YELLOW "=  |   `.'   |  |  |" GREEN "OO)" YELLOW "|   \\ |  |" GREEN "\\ " YELLOW "|  |" GREEN "OO)" YELLOW "      /    _ | |  | |  | |  .---'|  |" GREEN ".-')" YELLOW "  |  |" GREEN ".-')" YELLOW"   =\n" RESET);
	printf(YELLOW "=  |         |  |  |  " GREEN "\\" YELLOW"|    \\|  | " GREEN ")" YELLOW"|  |  " GREEN "\\" YELLOW "      \\  :` `. |   .|  | |  |    |  | " GREEN "OO )" YELLOW " |  | " GREEN "OO )" YELLOW"  =\n" RESET);
	printf(YELLOW "=  |  |'.'|  |  |  |" GREEN"(_/" YELLOW "|  .     |" GREEN "/" YELLOW " |  |" GREEN "(_/" YELLOW "       '..`''." GREEN ")" YELLOW "|       |" GREEN "(" YELLOW "|  '--. |  |" GREEN "`-' |" YELLOW " |  |" GREEN "`-' |"YELLOW"  =\n" RESET);
	printf(YELLOW "=  |  |   |  | " GREEN "," YELLOW "|  |" GREEN "_.'" YELLOW "|  |\\    | " GREEN "," YELLOW "|  |" GREEN "_.'" YELLOW "      .-._)   \\|  .-.  | |  .--'" GREEN"(" YELLOW "|  '---." GREEN "'(" YELLOW "|  '---." GREEN"'" YELLOW"  =\n" RESET);
	printf(YELLOW "=  |  |   |  |" GREEN"(_" YELLOW "|  |   |  | \\   |" GREEN"(_" YELLOW "|  |         \\       /|  | |  | |  `---.|      |  |      |   =\n" RESET);
	printf(YELLOW "=  `--'   `--'  `--'   `--'  `--'  `--'          `-----' `--' `--' `------'`------'  `------'   =\n" RESET);
	printf(YELLOW "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n" RESET);
}

char	*prompt(void)
{
	char	*str;

	printf(GREEN " /▔▔▔▔▔▔▔▔\\  ╭━━━━╮\n"RESET);
	printf(GREEN "| ╭--╮╭--╮ | |BOO…|\n" RESET);
	printf(GREEN "| |╭-╯╰-╮| | ╰━┳━━╯\n" RESET);
	printf(GREEN "| ╰╯ ╭╮ ╰╯ |━━━╯ \n" RESET);
	printf(GREEN "|    ╰╯    | \n" RESET);
	str = readline(GREEN "|/\\_/\\/\\_/\\|	" RESET);
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
	tok = malloc(sizeof(char *) * 4 + 1);
	if (!tok)
		return (0);
	welcome();
	data = clone_env(envp, data);
	int i = 0;
	while (i <= 4)
	{
		tok = malloc(sizeof(char *) * 4 + 1);
		if (!tok)
			return (0);
		line = prompt();
		tok = tokenisation(line, tok);
		call_execute(tok, data);
		ft_free_split(tok);
		i++;
	}
	system("leaks minishell");
	exit(EXIT_SUCCESS);
	return (0);
}
