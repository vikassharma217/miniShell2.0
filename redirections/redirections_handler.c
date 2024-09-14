/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:55:41 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/14 12:00:58 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//if RD_IN sorting our cmd list in right way order
//free is for deleting argv[0] -> filename 
//so after filename command is getting set to [0] for right execution
void shift_argv_left(char **argv)
{
    int i = 0;

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

//redirects file fd to stdin

static void	perform_input_redirection(t_cmd *cmd, t_data *data)
{
	t_cmd	*copy_cmd;
	int		input_fd;

	copy_cmd = cmd->next; //Safety thing
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

static void	perform_output_redirection(t_cmd *cmd, t_data *data, int saved_stdout)
{
	t_cmd	*copy_cmd;
	int		output_fd;
	char	*filename;

	copy_cmd = cmd;
	output_fd = 0;
	if (copy_cmd)
	{
		filename = copy_cmd->next->argv[0]; //safety thing
		if (copy_cmd->operator == RD_OUT)
			output_fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (copy_cmd->operator == RD_APND)
			output_fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (output_fd < 0 || dup2(output_fd, STDOUT_FILENO) == -1)
		{
			if (output_fd == -1)
				close(output_fd);
			perror("system function failed in perform output rd");
			close(saved_stdout);
			ft_clear_all(data);
			exit(EXIT_FAILURE);
		}
		close(output_fd);
	}
}

//handles all redirection commands
//executes start command to write inside redirection fd

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
	if ((*cmd)->operator == RD_HD)
	{
		close(saved_stdout);
		heredoc_handler(*cmd, data);
		ft_clear_all(data);
		exit(0);
	}
	while ((*cmd) && ((*cmd)->operator == RD_IN || (*cmd)->operator == RD_OUT
			|| (*cmd)->operator == RD_APND))
	{
		if ((*cmd)->operator == RD_IN)
			perform_input_redirection(*cmd, data);
		else if ((*cmd)->operator == RD_OUT || (*cmd)->operator == RD_APND)
			perform_output_redirection(*cmd, data, saved_stdout);
		if ((*cmd)->next)
			*cmd = (*cmd)->next;
		else
			break ;
	}
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
		{
			close(saved_stdout);
		}
		run_child_process_execute(cmd, data);
	}
}
//saves old stdout to redirect it after function is finsihed

void	handle_redirections(t_cmd **cmd, t_data *data)
{
	int	saved_stdout;

	saved_stdout = -1;
	if ((*cmd)->operator == RD_OUT || (*cmd)->operator == RD_APND
		|| (*cmd)->operator == RD_HD)
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
