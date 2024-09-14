/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_input_output.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscherl <rscherl@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:56:02 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/14 13:56:06 by rscherl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	perform_input_redirection(t_cmd *cmd, t_data *data)
{
	t_cmd	*copy_cmd;
	int		input_fd;

	copy_cmd = cmd->next;
	while (copy_cmd && copy_cmd->operator == RD_IN)
		copy_cmd = copy_cmd->next;
	if (copy_cmd && copy_cmd->argv[0])
	{
		input_fd = open(copy_cmd->argv[0], O_RDONLY, 0644);
		if (input_fd < 0)
		{
			write(2, "minishell: ", 11);
			perror(copy_cmd->argv[0]);
			data->exit_code = 1;
			ft_clear_all(data);
			exit(EXIT_FAILURE);
		}
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 in perform input redirection failed");
			close(input_fd);
			exit (EXIT_FAILURE);
		}
		close(input_fd);
	}
}

//creates file to write inside file
//redirects stdout to the file fd

void	perform_output_redirection(t_cmd *cmd)
{
	t_cmd	*copy_cmd;
	int		output_fd;
	char	*filename;

	copy_cmd = cmd;
	output_fd = 0;
	if (copy_cmd)
	{
		filename = copy_cmd->next->argv[0];
		if (copy_cmd->operator == RD_OUT)
			output_fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (copy_cmd->operator == RD_APND)
			output_fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (output_fd < 0 || dup2(output_fd, STDOUT_FILENO) == -1)
		{
			if (output_fd == -1)
				close(output_fd);
			perror("system function failed in perform output rd");
			exit(EXIT_FAILURE);
		}
		close(output_fd);
	}
}
