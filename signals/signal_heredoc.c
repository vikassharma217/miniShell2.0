/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 08:21:43 by vsharma           #+#    #+#             */
/*   Updated: 2024/09/03 08:32:55 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_signal = CNTL_C;
		close(STDIN_FILENO);
	}
}

void	heredoc_sigquit_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 19);
		close(STDIN_FILENO);
		exit(131);
	}
}

void	handle_eof_in_heredoc(t_cmd *current_cmd)
{
	if (g_signal != CNTL_C)
	{
		ft_putstr_fd("bash: warning: here-document at line 0 delimited by", 2);
		ft_putstr_fd(" end-of-file (wanted `", 2);
		ft_putstr_fd(current_cmd->next->argv[0], 2);
		ft_putstr_fd("')\n", 2);
	}
}
