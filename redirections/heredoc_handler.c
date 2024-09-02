/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:55:27 by rscherl           #+#    #+#             */
/*   Updated: 2024/08/30 17:10:01 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// with cmd "tail -f /tmp/.minishell_heredoc" in a seperate terminal...
//...you can see what you are writing inside in live

static void generate_filename(char *buffer, int index)
{
	int length;

	/*ft_strncpy(buffer, "/home/rscherl/Rene/42_Github_Rene_privat/Projects/minishell/temp/minishell", PATH_MAX);*/
    ft_strncpy(buffer, "/tmp/.minishell_heredoc_", PATH_MAX);
    length = ft_strlen(buffer);
    buffer[length++] = '0' + index;
    buffer[length] = '\0';
}

static void	handle_error(const char *message, const char *heredoc_file)
{
	perror(message);
	if (heredoc_file != NULL)
		unlink(heredoc_file);
	exit(EXIT_FAILURE);
}

static void	process_heredoc_input(int heredoc_fd, t_cmd *current_cmd)
{
	char	*line;
	char	*delimiter;

	delimiter = current_cmd->next->argv[0];
	while (1)
	{
		line = readline("> ");
		if (line == NULL) // This indicates EOF
		{
			handle_eof_in_heredoc(current_cmd);
			break ;
		}
		if (str_equals(line, delimiter) == 1)
		{
			free(line);
			break ;
		}
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
		free(line);
	}
}

void redirect_and_execute_command(const char *heredoc_file, t_cmd *cmd, t_data *data)
{
    int		fd;
	int		status;
	pid_t	pid;

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
    if ((pid = fork()) == 0)
    {
        system_commands(cmd, data);
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
        waitpid(pid, &status, 0);
    else
		handle_error("Failed to fork", heredoc_file);
}

void heredoc_handler(t_cmd *cmd, t_data *data)
{
    char    heredoc_file[256];
    int     heredoc_fd;
    int     file_index;
    t_cmd   *current_cmd = cmd;

	
    data->mode = HEREDOCS;
    handle_signals(data);
    while (current_cmd && current_cmd->operator == RD_HD)
    {
        generate_filename(heredoc_file, file_index++);
        heredoc_fd = open(heredoc_file, O_RDWR | O_CREAT | O_TRUNC, 0600);
        if (heredoc_fd < 0)
        {
            handle_error("Failed to create or open temporary file", heredoc_file);
        }
        process_heredoc_input(heredoc_fd, current_cmd);
		if (current_cmd->next && current_cmd->next->operator == RD_HD)
        {
            close(heredoc_fd);
            unlink(heredoc_file);
        }
        else
            close(heredoc_fd);
        current_cmd = current_cmd->next;
    }
	if (g_signal != CNTL_C)
        redirect_and_execute_command(heredoc_file, cmd, data);
	unlink(heredoc_file);
    data->mode = INTERACTIVE; 
    handle_signals(data);   
    if (g_signal == CNTL_C)
    {
        ft_clear_all(data);
        exit(130);
    }
}




























/*static void	print_heredoc_contents(int heredoc_fd)
{
	char	buffer[1024];
	ssize_t	bytes_read;

	lseek(heredoc_fd, 0, SEEK_SET); // Move file descriptor to start
	bytes_read = read(heredoc_fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		write(STDOUT_FILENO, buffer, bytes_read);
		bytes_read = read(heredoc_fd, buffer, sizeof(buffer));
	}
}*/

/*void	heredoc_handler(t_cmd *cmd, t_data *data)
{
	char	*heredoc_file;
	int		heredoc_fd;

	data->mode = HEREDOCS;
	handle_signals(data);
	heredoc_file = "/tmp/.minishell_heredoc";
	heredoc_fd = open(heredoc_file, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (heredoc_fd < 0)
	{
		handle_error("Failed to create or open temporary file", heredoc_file);
	}
	process_heredoc_input(heredoc_fd, cmd);
	if (g_signal != CNTL_C)
	{ // Only print contents if not interrupted
		print_heredoc_contents(heredoc_fd);
	}
	close(heredoc_fd);
	unlink(heredoc_file);
	data->mode = INTERACTIVE; // Restore mode after handling
	handle_signals(data);     // Restore original signals
	if (g_signal == CNTL_C)
    {unlink(last_file);
        ft_clear_all(data);  // Clean up resources
        exit(130);  // Exit with code 130 indicating interruption
    }
}*/




/*void	heredoc_handler(t_cmd *cmd)
{
	char	*heredoc_file;
	int		heredoc_fd;

	heredoc_file = "/tmp/.minishell_heredoc";
	heredoc_fd = open(heredoc_file, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (heredoc_fd < 0)
		handle_error("Failed to create or open temporary file", heredoc_file);
	process_heredoc_input(heredoc_fd, cmd);
	close(heredoc_fd);
	unlink(heredoc_file);
}
*/

// Think we dont need it do it to print it with cat just <<1 <<2 <<3 thats it
// even with cat it just prints whats in the last <<?
/*
static void	handle_error(char *message, char *heredoc_file)
{
	perror(message);
	if (heredoc_file != NULL)
		unlink(heredoc_file);
	exit(EXIT_FAILURE);
}

static void	output_file_content(int fd, char *heredoc_file)
{
	char	buffer[1024];
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		write(STDOUT_FILENO, buffer, bytes_read);
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
	if (bytes_read < 0)
		handle_error("Error reading file", heredoc_file);
}

static int	check_for_cat_command(t_data *data, t_cmd *cmd_list)
{
	(void) data;
	while (cmd_list)
	{
		if (cmd_list->argv[0] && str_equals(cmd_list->argv[0], "cat") == 1)
			return (1);
		cmd_list = cmd_list->next;
	}
	return (0);
}

static void	process_heredoc_input(int heredoc_fd, t_cmd *current_cmd)
{
	char	*line;
	char	*delimiter;

	while (current_cmd && current_cmd->operator == RD_HD)
	{
		delimiter = current_cmd->next->argv[0];
		while (1)
		{
			line = readline("> ");
			//Think we dont need it anymore
			if (!line)
				handle_eof_in_heredoc(current_cmd);
			if (str_equals(line, delimiter) == 1)
			{
				free(line);
				break ;
			}
			if (*line)
			{
				write(heredoc_fd, line, ft_strlen(line));
				write(heredoc_fd, "\n", 1);
			}
			free(line);
		}
		current_cmd = current_cmd->next;
	}
}
void	heredoc_handler(t_data *data, t_cmd *cmd)
{
	int			heredoc_fd;
	char		*heredoc_file;
	int			print_flag;
	t_heredoc	*new_node;
	t_heredoc	*current;

	print_flag = check_for_cat_command(data, cmd);
	heredoc_file = "/tmp/.minishell_heredoc";
	heredoc_fd = open(heredoc_file, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (heredoc_fd < 0)
	{
		handle_error("Failed to create or open temporary file", heredoc_file);
	}
	process_heredoc_input(heredoc_fd, cmd);
	close(heredoc_fd);
	if (print_flag)
	{
		heredoc_fd = open(heredoc_file, O_RDONLY);
		if (heredoc_fd < 0)
			handle_error("Failed to open temp file for reading", heredoc_file);
		output_file_content(heredoc_fd, heredoc_file);
		close(heredoc_fd);
	}
	unlink(heredoc_file);
}*/
// org
/*static t_heredoc	*create_and_append_node(t_heredoc **head, char *buffer)
{
	new_node = malloc(sizeof(t_heredoc));
	if (!new_node)
	{
		free(buffer);
		exit(EXIT_FAILURE);
	}
	new_node->input = ft_strdup(buffer);
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
	return (new_node);
}

static int	*read_heredoc_lines(t_cmd *node, t_heredoc **head)
{
	char	*buffer;
	int		*fd;

	fd = malloc(2 * sizeof(int));
	if (!fd)
		exit(EXIT_FAILURE);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		buffer = readline("> ");
		if (str_equals(buffer, node->next->argv[0]))
		{
			free(buffer);
			break ;
		}
		ft_putendl_fd(buffer, fd[1]);
		create_and_append_node(head, buffer);
		free(buffer);
	}
	return (fd);
}

static void	free_heredoc_lines(t_heredoc *head, int print_flag)
{
	t_heredoc	*current;
	t_heredoc	*next;

	current = head;
	while (current != NULL)
	{
		if (print_flag)
			ft_putendl_fd(current->input, STDOUT_FILENO);
		next = current->next;
		free(current->input);
		free(current);
		current = next;
	}
}

void	r_hd(t_data *data, t_cmd *node)
{
	t_heredoc	*head;
	int			is_cat_command;
	int			*fd;

	head = NULL;
	is_cat_command = str_equals(node->argv[0], "cat");
	data->mode = HEREDOCS;
	handle_signals(data);
	fd = read_heredoc_lines(node, &head);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	free_heredoc_lines(head, is_cat_command);
	free(fd);
}*/
