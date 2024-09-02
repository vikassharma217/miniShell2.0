/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:55:03 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/02 17:04:39 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_pipe_error(const char *error_message, t_data *data)
{
	perror(error_message);
	ft_clear_all(data);
	exit(EXIT_FAILURE);
}

static void	pipe_child_process(t_cmd *node, int fd[2], t_data *data)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		handle_pipe_error("dup2 failed in child process", data);
	close(fd[1]);
	run_command(node, data);
	exit(EXIT_SUCCESS);
}

static void	pipe_parent_process(t_cmd *node, int fd[2], t_data *data,
		pid_t child_pid)
{
	int	status;

	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		handle_pipe_error("dup2 failed in parent process", data);
	close(fd[0]);
	run_command(node->next, data);
	waitpid(child_pid, &status, 0);
	data->exit_code = WEXITSTATUS(status);
}

void	pipe_execution(t_cmd *node, t_data *data)
{
	int		fd[2];
	int		status;
	pid_t	child_pid;

	node->operator = NONE;
	if (!node->next)
	{
		run_command(node, data);
		return ;
	}
	if (pipe(fd) == -1)
		handle_pipe_error("Pipe creation failed", data);
	status = 0;
	child_pid = fork();
	if (child_pid == -1)
		handle_pipe_error("fork() failed", data);
	else if (child_pid == 0)
		pipe_child_process(node, fd, data);
	else
		pipe_parent_process(node, fd, data, child_pid);
}
