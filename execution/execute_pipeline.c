/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:55:03 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/09 14:05:10 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_pipe_error(const char *error_message, t_data *data)
{
	perror(error_message);
	ft_clear_all(data);
	exit(EXIT_FAILURE);
}

static void	pipe_child_process(t_cmd **cmd, int pipe_fd[2], t_data *data)
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		handle_pipe_error("dup2 failed in child process", data);
	close(pipe_fd[1]);
	run_command_child(cmd, data);
	ft_clear_all(data);
	exit(EXIT_SUCCESS);
}

static void	pipe_parent_process(t_cmd **cmd, int pipe_fd[2], t_data *data,
		pid_t child_pid)
{
	int	status;

	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		handle_pipe_error("dup2 failed in parent process", data);
	close(pipe_fd[0]);
	if ((*cmd)->next != NULL)
	{
		*cmd = (*cmd)->next;
		run_child_process_execute(cmd, data);

	}
	waitpid(child_pid, &status, 0);
	data->exit_code = WEXITSTATUS(status);
}

void	pipe_execution(t_cmd **cmd, t_data *data)
{
	int		pipe_fd[2];
	int		status;
	pid_t	child_pid;

	(*cmd)->operator = NONE;
	data->is_pipe = 1;
	if (!(*cmd)->next)
	{
		run_command_child(cmd, data);
		ft_clear_all(data);
		data->exit_code = 0;
		exit(data->exit_code);
	}
	if (pipe(pipe_fd) == -1)
		handle_pipe_error("Pipe creation failed", data);
	status = 0;
	child_pid = fork();
	if (child_pid == -1)
		handle_pipe_error("fork() failed", data);
	else if (child_pid == 0)
		pipe_child_process(cmd, pipe_fd, data);
	else
		pipe_parent_process(cmd, pipe_fd, data, child_pid);
}
