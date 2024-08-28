/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:54:47 by rscherl           #+#    #+#             */
/*   Updated: 2024/08/28 15:46:44 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	size_of_list(t_cmd *list)
{
	t_cmd	*temp;
	size_t	len;

	temp = list;
	len = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		len++;
	}
	return (len);
}

void	run_command(t_cmd *node, t_data *data)
{
	if (node->operator != NONE)
	{
		if (node->operator == PIPE)
			pipe_execution(node, data);
		else
			handle_redirections(node, data);
	}
	else
	{
		if (!builtin(node, data))
			system_commands(node, data);
	}
	if (data)
		ft_clear_all(data);
	exit(data->exit_code);
}

static void	run_parent_process(pid_t child_pid, t_data *data)
{
	int	status;
	int	exit_status;

	exit_status = 0;
	if (waitpid(child_pid, &status, 0) == -1)
	{
		perror("waitpid()");
		data->exit_code = 1;
		return ;
	}
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			exit_status = 128 + SIGINT;
		else
			exit_status = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	data->exit_code = exit_status;
}

static void	run_child_process_system_commands(t_cmd *cmd_list, t_data *data)
{
	int	status;

	status = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	system_commands(cmd_list, data);
	status = data->exit_code;
	exit(status);
}

static void	run_child_process_execute(t_cmd *cmd_list, t_data *data)
{
	int	status;

	status = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	run_command(cmd_list, data);
	status = data->exit_code;
	exit(status);
}

void	start_execution(t_cmd *cmd_list, t_data *data)
{
	pid_t	pid;

	if (size_of_list(cmd_list) == 1 && builtin(cmd_list, data))
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("Error in fork()");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0 && size_of_list(cmd_list) == 1)
		run_child_process_system_commands(cmd_list, data);
	else if (pid == 0 && size_of_list(cmd_list) != 1)
		run_child_process_execute(cmd_list, data);
	else
		run_parent_process(pid, data);
}

/*void	execute_util(t_cmd *node, t_data *data)
{
	if (builtin(node, data))
		return ;
	binaries(node, data);
}

void	execute_command(t_cmd *node, t_data *data)
{
	data->mode = CHILD_PROCESS;
	handel_signals(data);
	if (node->operator == PIPE)
		pipe_execution(node, data);
	else if (node->operator == NONE)
		execute_util(node, data);
	else
		redirections(node, data);
	if (data)
		ft_clear_all(data);
	exit(data->exit_code);
}

void	handle_child_process(t_cmd *cmd_list, t_data *data,
		void (*execute)(t_cmd *, t_data *))
{
	data->mode = CHILD_PROCESS;
	handel_signals(data);
	execute(cmd_list, data);
	exit(data->exit_code);
}

void	handle_parent_process(pid_t pid, t_data *data)
{
	int	temp;
	int	status;

	waitpid(pid, &temp, 0);
	if (WIFSIGNALED(temp))
	{
		status = WTERMSIG(temp);
		if (status == SIGINT)
			data->exit_code = 130;
		else
			data->exit_code = status + 128;
	}
	else if (WIFEXITED(temp))
	{
		status = WEXITSTATUS(temp);
		data->exit_code = status;
	}
}

void	init_execution(t_cmd *cmd_list, t_data *data)
{
	pid_t	pid;

	if (size_of_list(cmd_list) == 1)
	{
		if (!builtin(cmd_list, data))
		{
			pid = fork();
			if (pid == 0)
				handle_child_process(cmd_list, data, binaries);
			else
				handle_parent_process(pid, data);
		}
	}
	else
	{
		pid = fork();
		if (pid == 0)
			handle_child_process(cmd_list, data, execute_command);
		else
			handle_parent_process(pid, data);
	}
}*/
