/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:52:53 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/30 17:01:32 by vsharma          ###   ########.fr       */
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
		//rl_redisplay();
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

void	heredoc_sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = CNTL_C;
		write(1, "\n", 1);
		//ft_clear_all(data);
		//exit(130); // Exit with code 130 for Ctrl+C interruption
	}
}

void	heredoc_sigquit_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 19);
		close(STDIN_FILENO); // Close stdin to ensure readline exits cleanly
		exit(131);           // Exit with code 131 for Ctrl+\ interruption
	}
}

void	handle_eof_in_heredoc(t_cmd *current_cmd)
{
	ft_putstr_fd("bash: warning: here-document at line 0 delimited by end-of-file (wanted `",
		2);
	ft_putstr_fd(current_cmd->next->argv[0], 2);
	ft_putstr_fd("')\n", 2);
}

void	init_signal(t_data *data)
{
	if (data->mode == INTERACTIVE)
	{
		signal(SIGINT, &sigint_handler);
		signal(SIGQUIT, &sigquit_handler);
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
