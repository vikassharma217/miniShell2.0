/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:52:53 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/29 17:42:40 by vsharma          ###   ########.fr       */
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

//Think we dont need it anymore, dont find the testcase for it
/*void	handle_eof_in_heredoc(t_cmd *current_cmd)
{
	ft_putstr_fd("bash: warning: here-document at line 0 delimited by end-of-file (wanted `",
		2);
	ft_putstr_fd(current_cmd->next->argv[0], 2);
	ft_putstr_fd("')\n", 2);
}*/

//Same here, dont think we need it 
/*void	herdocs_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = CNTL_C;
		exit(130);
	}
}*/

void	init_signal(t_data *data)
{
	if (data->mode == INTERACTIVE)
	{
		signal(SIGINT, &sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (data->mode == NON_INTERACTIVE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	// deleted data->mode CHILD_PROCESS implemented in other function

	//Dont think we need this anymore, but not sure
	/*else if (data->mode == HEREDOCS)
	{
		signal(SIGINT, &herdocs_handler);
		signal(SIGQUIT, SIG_IGN);
	}*/
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

/*
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

void	herdocs_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = CNTL_C;
		exit(130);
	}
}
void	init_signal(t_data *data)
{
	if (data->mode == INTERACTIVE)
	{
		signal(SIGINT, &sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (data->mode == NON_INTERACTIVE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (data->mode == CHILD_PROCESS)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (data->mode == HEREDOCS)
	{
		signal(SIGINT, &herdocs_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	handel_signals(t_data *data)
{
	init_signal(data);
}*/