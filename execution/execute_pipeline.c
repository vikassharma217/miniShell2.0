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

static void	pipe_child_process(t_cmd *cmd, int pipe_fd[2], t_data *data)
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		handle_pipe_error("dup2 failed in child process", data);
	close(pipe_fd[1]);
	(void)cmd;
	run_command_child(&cmd, data);
	ft_clear_all(data);
	exit(EXIT_SUCCESS);
}

static void	pipe_parent_process(t_cmd *cmd, int pipe_fd[2], t_data *data,
		pid_t child_pid)
{
	int	status;

(void)cmd; //delete
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		handle_pipe_error("dup2 failed in parent process", data);
	close(pipe_fd[0]);
	waitpid(child_pid, &status, 0);
	//if (cmd->next != NULL)
	//	pipe_execution(cmd->next, data);
	data->exit_code = WEXITSTATUS(status);
}

void	pipe_execution(t_cmd *cmd, t_data *data)
{
	int		pipe_fd[2];
	int		status;
	pid_t	child_pid;

	cmd->operator = NONE;
	/*if (!cmd->next)
	{
		run_command_child(&cmd, data);
		return ;
	}*/
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
