/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:14:22 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 17:14:24 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	part_1(void)
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
}

static void	part_2(void)
{
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
}

void	welcome(void)
{
	part_1();
	part_2();
}
