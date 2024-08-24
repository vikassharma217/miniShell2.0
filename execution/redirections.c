/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscherl <rscherl@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:55:41 by rscherl           #+#    #+#             */
/*   Updated: 2024/08/24 17:55:42 by rscherl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	r_in(t_data *data, t_cmd *node)
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
		execute_command(temp, data);
	else
		pipe_execution(cmd, data);
}
