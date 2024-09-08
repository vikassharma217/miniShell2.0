/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:52:53 by vsharma           #+#    #+#             */
/*   Updated: 2024/09/08 18:52:06 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = CNTL_C;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	init_signal_interactive(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_signal_non_interactive(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	init_signal_heredocs(void)
{
	signal(SIGINT, &heredoc_sigint_handler);
	signal(SIGQUIT, &heredoc_sigquit_handler);
}
