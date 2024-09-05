/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:54:47 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/05 10:16:16 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_command(t_cmd *cmd, t_data *data)
{
	if (cmd->operator != NONE)
	{
		if (cmd->operator != PIPE)
			handle_redirections(cmd, data);
		else
			pipe_execution(cmd, data);
	}
	else
	{
		if (!builtin(cmd, data))
			system_commands(cmd, data);
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
	int	i;
	t_cmd *temp;

	temp = cmd_list;
	i = 0;
	/*while (temp != NULL) //Debugging Tool for checking operator
	{
    	//printf("Operator: %u\n", temp->operator);
    	for (int i = 0; temp->argv[i] != NULL; i++)
		{
        	//printf("Command: %s\n", temp->argv[i]);
    	}
    	temp = temp->next;
	}*/
	if (!cmd_list->next && builtin(cmd_list, data))
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("Error in fork()");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		run_child_process_execute(cmd_list, data);
	else
		run_parent_process(pid, data);
}
