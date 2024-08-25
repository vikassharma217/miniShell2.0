/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscherl <rscherl@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:54:47 by rscherl           #+#    #+#             */
/*   Updated: 2024/08/24 17:54:49 by rscherl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_util(t_cmd *node, t_data *data)
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

static void	handle_child_process(t_cmd *cmd_list, t_data *data,
		void (*execute_or_binaries)(t_cmd *, t_data *))
{
	data->mode = CHILD_PROCESS;
	handel_signals(data);
	execute_or_binaries(cmd_list, data);
	exit(data->exit_code);
}

static void	handle_parent_process(pid_t pid, t_data *data)
{
	int	temp;

	waitpid(pid, &temp, 0);
	if (WIFSIGNALED(temp))
	{
		if (WTERMSIG(temp) == SIGINT)
			data->exit_code = 130;
		else
			data->exit_code = WTERMSIG(temp) + 128;
	}
	else if (WIFEXITED(temp))
		data->exit_code =  WEXITSTATUS(temp);
}

void	init_execution(t_cmd *cmd_list, t_data *data)
{
	pid_t	pid;

	if (size_of_list(cmd_list) == 1 && builtin(cmd_list, data))
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("Error in fork()");
		exit (EXIT_FAILURE);
	}
	else if (pid == 0 && size_of_list(cmd_list) == 1)
		handle_child_process(cmd_list, data, binaries);
	else if (pid == 0 && size_of_list(cmd_list) != 1)
		handle_child_process(cmd_list, data, execute_command);
	else
		handle_parent_process(pid, data);
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
