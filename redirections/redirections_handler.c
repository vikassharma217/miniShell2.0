/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:55:41 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/09 09:18:30 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//if RD_IN sorting our cmd list in right way order
//free is for deleting argv[0] -> filename 
//so after filename command is getting set to [0] for right execution

void	shift_argv_left(char **argv)
{
	int	i;

	i = 0;
	if (argv[i])
		free(argv[i]);
	while (argv[i + 1])
	{
		argv[i] = argv[i + 1];
		i++;
	}
	argv[i] = NULL;
}

static void	run_command_rd(t_cmd *cmd, t_data *data)
{
	if (!builtin(cmd, data))
		system_commands(cmd, data);
}

//handles all redirection commands
//executes start command to write inside redirection fd

static void	action_redirections(t_cmd **cmd, t_data *data)
{
	while ((*cmd) && ((*cmd)->operator == RD_IN || (*cmd)->operator == RD_OUT
			|| (*cmd)->operator == RD_APND))
	{
		if ((*cmd)->operator == RD_IN)
			perform_input_redirection(*cmd, data);
		else if ((*cmd)->operator == RD_OUT || (*cmd)->operator == RD_APND)
			perform_output_redirection(*cmd);
		if ((*cmd)->next)
			*cmd = (*cmd)->next;
		else
			break ;
	}
}

static void	execute_redirection(t_cmd **cmd, t_data *data, int saved_stdout)
{
	t_cmd	*start_cmd;
	int		flag;

	start_cmd = NULL;
	flag = 0;
	if ((*cmd)->argv[0])
	{
		start_cmd = *cmd;
		flag = 1;
	}
	action_redirections(cmd, data);
	if ((*cmd) && (*cmd)->argv[0] && !flag)
	{
		shift_argv_left((*cmd)->argv);
		start_cmd = (*cmd);
	}
	if (flag)
		run_command_rd(start_cmd, data);
	else if (!flag)
	{
		if (saved_stdout != -1)
			close(saved_stdout);
		run_child_process_execute(cmd, data);
	}
}
//saves old stdout to redirect it after function is finsihed

void	handle_redirections(t_cmd **cmd, t_data *data)
{
	int	saved_stdout;

	saved_stdout = -1;
	if ((*cmd)->operator == RD_OUT || (*cmd)->operator == RD_APND)
	{
		saved_stdout = dup(STDOUT_FILENO);
		if (saved_stdout == -1)
		{
			perror("dup failed");
			exit(EXIT_FAILURE);
		}
		execute_redirection(cmd, data, saved_stdout);
		if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		{
			perror("dup2 restore failed");
			close(saved_stdout);
			exit(EXIT_FAILURE);
		}
		if (saved_stdout != -1)
			close(saved_stdout);
	}
	else
		execute_redirection(cmd, data, saved_stdout);
}
