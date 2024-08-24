/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscherl <rscherl@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:55:03 by rscherl           #+#    #+#             */
/*   Updated: 2024/08/24 17:55:06 by rscherl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	p_first(t_cmd *node, t_data *data, int fd[2])
{
	close(fd[0]);
	if (close(STDOUT_FILENO) == -1)
	{
		perror("Error closing standard output in first command");
		return ;
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("Error duplicating write");
		return ;
	}
	close(fd[1]);
	execute_command(node, data);
}

static void	p_second(t_cmd *node, t_data *data, int fd[2])
{
	close(fd[1]);
	if (close(STDIN_FILENO) == -1)
	{
		perror("Error closing standard input in second command");
		return ;
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("Error duplicating read");
		return ;
	}
	close(fd[0]);
	execute_command(node, data);
}

void	pipe_fails(t_data *data)
{
	ft_clear_all(data);
	ft_putendl_fd(PIPE_ERR, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	child_pid_fails(t_data *data)
{
	ft_clear_all(data);
	exit(EXIT_FAILURE);
}

void	pipe_execution(t_cmd *node, t_data *data)
{
	int		fd[2];
	int		temp;
	pid_t	child_pid;

	node->operator = NONE;
	if (node->next != NULL)
	{
		if (pipe(fd) == -1)
			pipe_fails(data);
		child_pid = fork();
		if (child_pid == -1)
			child_pid_fails(data);
		else if (child_pid == 0)
		{
			p_first(node, data, fd);
			exit(EXIT_SUCCESS);
		}
		p_second(node->next, data, fd);
		waitpid(child_pid, &temp, 0);
	}
	else
		execute_command(node, data);
	data->exit_code = 130;
}
