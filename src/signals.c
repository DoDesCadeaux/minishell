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

static void	restore_prompt(int sig)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
	show_ghost();
	rl_redisplay();
	g_error_code = 1;
	(void)sig;
}

/*static void	ctrl_c(int sig)
{
	write(1, "\n", 1);
	(void)sig;
}*/
/*
static void	ctrl_d(int sig)
{
	printf("^\\\n\nEXIT\n");
	(void)sig;
}*/

void	run_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGKILL, SIG_IGN);
	}
}
