/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:14:22 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 17:14:24 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	restore_prompt(int sig)
{
	write (1, "\n", 1); //fd 1 ou 2 ??
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	//show_ghost();
	(void)sig;
}

void	ctrl_C(int sig)
{
	write(1, "\n", 1);
	(void)sig;
}

void	ctrl_D(int sig)
{
	printf("^\\Quit : 3\n");
	(void)sig;
}

void	run_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_C);
		signal(SIGQUIT, ctrl_D);
	}
}