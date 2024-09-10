/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 08:21:43 by vsharma           #+#    #+#             */
/*   Updated: 2024/09/10 20:36:34 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = CNTL_C;
		close(STDIN_FILENO);
	}
}

void	heredoc_sigquit_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		close(STDIN_FILENO);
	}
}

void	handle_eof_in_heredoc(t_cmd *current_cmd)
{
	if (g_signal != CNTL_C)
	{
		ft_putstr_fd("bash: warning: here-document delimited by", 2);
		ft_putstr_fd(" end-of-file (wanted `", 2);
		ft_putstr_fd(current_cmd->next->argv[0], 2);
		ft_putstr_fd("')\n", 2);
	}
}
