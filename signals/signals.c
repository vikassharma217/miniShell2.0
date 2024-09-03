/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:52:53 by vsharma           #+#    #+#             */
/*   Updated: 2024/09/03 08:23:00 by vsharma          ###   ########.fr       */
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

void	sigquit_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
		g_signal = CNTL_BACKSLASH;
	}
}

void	init_signal(t_data *data)
{
	if (data->mode == INTERACTIVE)
	{
		signal(SIGINT, &sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (data->mode == HEREDOCS)
	{
		signal(SIGINT, &heredoc_sigint_handler);
		signal(SIGQUIT, &heredoc_sigquit_handler);
	}
	else if (data->mode == NON_INTERACTIVE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	handle_signals(t_data *data)
{
	init_signal(data);
}
