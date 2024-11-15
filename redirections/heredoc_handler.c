/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:55:27 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/10 15:07:51 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// with cmd "tail -f /tmp/.minishell_heredoc" in a seperate terminal...
//...you can see what you are writing inside in live

static void	handle_error(const char *message, const char *heredoc_file)
{
	perror(message);
	if (heredoc_file != NULL)
		unlink(heredoc_file);
	exit(EXIT_FAILURE);
}
//redirecting heredoc fd to stdin for commands like cat

void	redirect_and_execute_command(const char *heredoc_file, t_cmd *cmd,
		t_data *data)
{
	int	fd;

	fd = open(heredoc_file, O_RDONLY);
	if (fd < 0)
		handle_error("Failed to create or open temporary file", heredoc_file);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Failed to redirect stdin");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
	system_commands(cmd, data);
}
//writing inside heredoc
//ending by delimiter

static void	process_heredoc_input(int heredoc_fd, t_cmd *current_cmd,
		t_data *data)
{
	char	*line;
	char	*delimiter;
	char	*expanded_line;

	delimiter = current_cmd->next->argv[0];
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			handle_eof_in_heredoc(current_cmd);
			break ;
		}
		if (str_equals(line, delimiter))
		{
			free(line);
			break ;
		}
		expanded_line = init_expander(line, data);
		ft_putstr_fd(expanded_line, heredoc_fd);
		ft_putstr_fd("\n", heredoc_fd);
		free(line);
		free(expanded_line);
	}
}
//generating filename for multiple heredoc
//READ/WRITE, CREATE, TRUNC to empty if it exists to 0 bytes
//rules for file who can write and read it

static void	process_current_heredoc(t_cmd *current_cmd, char *heredoc_file,
		int *file_index, t_data *data)
{
	int	heredoc_fd;
	int	stdin_copy;

	while (current_cmd && current_cmd->operator == RD_HD)
	{
		generate_filename(heredoc_file, (*file_index)++);
		heredoc_fd = open(heredoc_file, O_RDWR | O_CREAT | O_TRUNC, 0600);
		if (heredoc_fd < 0)
			handle_error("Failed to create or open temporary file",
				heredoc_file);
		if (data->is_pipe)
			stdin_copy = redirect_stdin_to_terminal(data);
		process_heredoc_input(heredoc_fd, current_cmd, data);
		if (current_cmd->next && current_cmd->next->operator == RD_HD)
		{
			close(heredoc_fd);
			unlink(heredoc_file);
		}
		else
			close(heredoc_fd);
		current_cmd = current_cmd->next;
	}
	if (data->is_pipe)
		restore_stdin(stdin_copy, data);
}

//manages heredoc input: sets up signals, processes the heredoc

void	heredoc_handler(t_cmd *cmd, t_data *data)
{
	char	heredoc_file[PATH_MAX];
	int		file_index;

	data->mode = HEREDOCS;
	init_signal_heredocs();
	file_index = 1;
	process_current_heredoc(cmd, heredoc_file, &file_index, data);
	if (g_signal != CNTL_C)
		redirect_and_execute_command(heredoc_file, cmd, data);
	unlink(heredoc_file);
	data->mode = INTERACTIVE;
	init_signal_interactive();
	if (g_signal == CNTL_C)
	{
		ft_clear_all(data);
		exit(130);
	}
}
