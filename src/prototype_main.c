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

void	prompt(void)
{
	char	*str;

	printf(GREEN " /▔▔▔▔▔▔▔▔\\  ╭━━━━╮\n"RESET);
	printf(GREEN "| ╭--╮╭--╮ | |BOO…|\n" RESET);
	printf(GREEN "| |╭-╯╰-╮| | ╰━┳━━╯\n" RESET);
	printf(GREEN "| ╰╯ ╭╮ ╰╯ |━━━╯ \n" RESET);
	printf(GREEN "|    ╰╯    | \n" RESET);
	str = readline(GREEN "|/\\_/\\/\\_/\\|	" RESET);
}

int main(int argc, char **argv, char **envp)
{
	welcome();

	printf ("\n\n coucou");
    while (1)
	    prompt();
	return (0);
}
