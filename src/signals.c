/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:14:22 by pamartin          #+#    #+#             */
/*   Updated: 2022/11/17 15:28:13 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	process_ended(int sig)
{
	if (access(HERE_DOC, X_OK) == 0)
	{
		unlink(HERE_DOC);
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
	g_error_code = SIGNAL;
	(void)sig;
}

void	restore_prompt(int sig)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
	show_ghost();
	rl_redisplay();
	g_error_code = SIGNAL;
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
		signal(SIGINT, process_ended);
		signal(SIGQUIT, process_ended);
		signal(SIGPIPE, process_ended);
	}
}
