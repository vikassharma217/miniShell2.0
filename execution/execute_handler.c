/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:54:47 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/03 08:33:23 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	if (!cmd_list->next && builtin(cmd_list, data))
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("Error in fork()");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0 && !cmd_list->next)
		run_child_process_system_commands(cmd_list, data);
	else if (pid == 0 && cmd_list->next)
		run_child_process_execute(cmd_list, data);
	else
		run_parent_process(pid, data);
}
