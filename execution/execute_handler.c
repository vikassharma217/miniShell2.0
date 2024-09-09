/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:54:47 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/09 09:24:35 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_command_child(t_cmd **cmd, t_data *data)
{
	int	status;

	status = 0;
	if ((*cmd)->operator != NONE)
	{
		if ((*cmd)->operator != PIPE)
		{
			handle_redirections(cmd, data);
			status = 1;
		}
		else
			pipe_execution(*cmd, data);
	}
	else
	{
		if (!builtin(*cmd, data))
			system_commands(*cmd, data);
	}
	return (status);
}

// parent shud not wait for invidual child process to finish
// before starting the next one
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

// If flag is set,already points to nxt cmd without the pipe and filename
static void	run_child_process_execute(t_cmd **cmd_list, t_data *data)
{
	int	flag_redirection;

	flag_redirection = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	while (*cmd_list)
	{
		flag_redirection = run_command_child(cmd_list, data);
		if ((*cmd_list)->next)
		{
			if ((*cmd_list)->next && !flag_redirection)
				*cmd_list = (*cmd_list)->next;
			flag_redirection = 0;
			continue ;
		}
		if (flag_redirection && !(*cmd_list)->next)
			run_command_child(cmd_list, data);
		break ;
	}
	if (data)
		ft_clear_all(data);
	data->exit_code = 0;
	exit(data->exit_code);
}

void	start_execution(t_cmd *cmd_list, t_data *data)
{
	pid_t	pid;
	int		i;
	t_cmd	*temp;

	temp = cmd_list;
	i = 0;
	if (!cmd_list->next && builtin(cmd_list, data))
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("Error in fork()");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		run_child_process_execute(&cmd_list, data);
	else
		run_parent_process(pid, data);
}

/*void	run_command(t_cmd *cmd, t_data *data)
{
	int	status;
	int	status;
	int	status;

	status = 0;
	if (cmd->operator != NONE)
	{
		if (cmd->operator != PIPE)
		{
			handle_redirections(&cmd, data);
			status = 1;
		}
		else
			pipe_execution(cmd, data);
	}
	else
	{
		if (!builtin(cmd, data))
			system_commands(cmd, data);
	}
	//if (data)
	//	ft_clear_all(data);
	//exit(data->exit_code);
}*/
/*static void	run_command_rd(t_cmd *cmd, t_data *data)
{
	if (!builtin(cmd, data))
		system_commands(cmd, data);
}*/