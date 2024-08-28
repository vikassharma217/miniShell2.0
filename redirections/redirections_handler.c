/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscherl <rscherl@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:55:41 by rscherl           #+#    #+#             */
/*   Updated: 2024/08/24 17:55:42 by rscherl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	perform_input_redirection(t_cmd *cmd, t_data *data)
{
	t_cmd	*current_cmd;
	int		input_fd;

	current_cmd = cmd->next;
	while (current_cmd && current_cmd->operator == RD_IN)
		current_cmd = current_cmd->next;
	if (current_cmd && current_cmd->argv[0])
	{
		input_fd = open(current_cmd->argv[0], O_RDONLY);
		if (input_fd < 0)
		{
			write(2, "minishell: ", 11);
			perror(current_cmd->argv[0]);
			data->exit_code = 1;
			exit(EXIT_FAILURE);
		}
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
}

static void	perform_output_append(t_cmd *cmd)
{
	t_cmd	*current_cmd;
	int		output_fd;
	char	*filename;

	current_cmd = cmd;
	if (current_cmd && current_cmd->next && current_cmd->next->argv[0])
	{
		while (current_cmd && current_cmd->next && current_cmd->next->argv[0])
		{
			filename = current_cmd->next->argv[0];
			output_fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (output_fd < 0)
			{
				write(2, "minishell: ", 11);
				perror(filename);
				exit(EXIT_FAILURE);
			}
			if (current_cmd->next->next != NULL)
				close(output_fd);
			current_cmd = current_cmd->next;
		}
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
}

static void	perform_output_redirection(t_cmd *cmd)
{
	t_cmd	*current_cmd;
	int		output_fd;
	char	*filename;

	current_cmd = cmd;
	if (current_cmd && current_cmd->next && current_cmd->next->argv[0])
	{
		while (current_cmd && current_cmd->next && current_cmd->next->argv[0])
		{
			filename = current_cmd->next->argv[0];
			output_fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (output_fd < 0)
			{
				write(2, "minishell: ", 11);
				perror(filename);
				exit(EXIT_FAILURE);
			}
			if (current_cmd->next->next != NULL)
				close(output_fd);
			current_cmd = current_cmd->next;
		}
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
}

static void	execute_redirection(t_cmd *cmd, t_data *data)
{
	if (cmd->operator == RD_IN)
		perform_input_redirection(cmd, data);
	else if (cmd->operator == RD_HD)
	{
		heredoc_handler(cmd);
		ft_clear_all(data);
		exit(0);
	}
	else if (cmd->operator == RD_OUT)
		perform_output_redirection(cmd);
	else if (cmd->operator == RD_APND)
		perform_output_append(cmd);
	else
		write(2, "Error: unsupported redirection operator\n", 40);
}

void	handle_redirections(t_cmd *cmd, t_data *data)
{
	t_cmd	*start_cmd;

	start_cmd = cmd;
	execute_redirection(cmd, data);
	start_cmd->operator = NONE;
	while (cmd && cmd->operator != NONE && cmd->operator != PIPE)
		cmd = cmd->next;
	if (!cmd || cmd->operator == NONE)
		run_command(start_cmd, data);
	else
		pipe_execution(cmd, data);
}

/*static void	r_in(t_data *data, t_cmd *node)
{
	int		in;
	char	*error_message;

	if (node->next->argv[0])
	{
		while (node->next->operator == RD_IN)
		{
			node = node->next;
		}
		if (access(node->next->argv[0], F_OK) == 0)
		{
			in = open(node->next->argv[0], O_RDONLY, 0666);
			dup2(in, STDIN_FILENO);
		}
		else
		{
			error_message = ft_strjoin("minishell: ", node->next->argv[0]);
			perror(error_message);
			free(error_message);
			data->exit_code = 2;
			exit(EXIT_FAILURE);
		}
	}
}

static void	r_out(t_cmd *node)
{
	close(STDOUT_FILENO);
	while (node->next->operator == RD_OUT || node->next->operator == RD_APND)
	{
		if (node->operator == RD_OUT)
			open(node->next->argv[0], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (node->operator == RD_APND)
			open(node->next->argv[0], O_WRONLY | O_APPEND | O_CREAT, 0666);
		node = node->next;
		close(1);
	}
	if (node->operator == RD_OUT)
		open(node->next->argv[0], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (node->operator == RD_APND)
		open(node->next->argv[0], O_WRONLY | O_APPEND | O_CREAT, 0666);
}

void	redirections(t_cmd *cmd, t_data *data)
{
	t_cmd	*temp;

	temp = cmd;
	if (cmd->operator == RD_IN)
		r_in(data, cmd);
	else if (cmd->operator == RD_HD)
	{
		r_hd(data, cmd);
		ft_clear_all(data);
		exit (0);
	}
	else
		r_out(cmd);
	temp->operator = NONE;
	while (cmd->operator != NONE && cmd->operator != PIPE)
		cmd = cmd->next;
	if (cmd->operator == NONE)
		run_command(temp, data);
	else
		pipe_execution(cmd, data);
}*/
