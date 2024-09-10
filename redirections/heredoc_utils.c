/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscherl <rscherl@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:23:37 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/10 17:24:09 by rscherl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exit_with_failure(t_data *data)
{
	ft_clear_all(data);
	exit(EXIT_FAILURE);
}
//allowing direct interaction with the terminal
//even if stdin or stdout is redirected.

int	redirect_stdin_to_terminal(t_data *data)
{
	int	stdin_copy;
	int	terminal_fd;

	stdin_copy = dup(STDIN_FILENO);
	if (stdin_copy == -1)
	{
		perror("Failed to duplicate stdin");
		exit_with_failure(data);
	}
	terminal_fd = open("/dev/tty", O_RDONLY);
	if (terminal_fd == -1)
	{
		perror("Failed to open /dev/tty");
		close(stdin_copy);
		exit_with_failure(data);
	}
	if (dup2(terminal_fd, STDIN_FILENO) == -1)
	{
		perror("Failed to redirect stdin to terminal");
		close(terminal_fd);
		close(stdin_copy);
		exit_with_failure(data);
	}
	close(terminal_fd);
	return (stdin_copy);
}

void	restore_stdin(int stdin_copy, t_data *data)
{
	if (dup2(stdin_copy, STDIN_FILENO) == -1)
	{
		perror("Failed to restore stdin");
		close(stdin_copy);
		exit_with_failure(data);
	}
	close(stdin_copy);
}
