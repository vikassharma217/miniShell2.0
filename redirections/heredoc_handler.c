/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:55:27 by rscherl           #+#    #+#             */
/*   Updated: 2024/08/28 13:22:53 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Check PATH_MAX in create_tempfile
//Check if heredoc file will be deleted after something fails
//Check all free commands

static int	create_tempfile(t_data *data, char **template)
{
	char	*temp_path;
	int		temp_fd;

	temp_path = ft_strjoin(data->execute_dir, "/temp/heredoc");
	*template = ft_strdup(temp_path);
	free(temp_path);
	temp_fd = open(*template, O_RDWR | O_CREAT | O_EXCL, 0600);
	if (temp_fd == -1)
	{
		free(*template);
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (temp_fd);
}

static void	process_heredoc_input(char *delimiter, int temp_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(temp_fd, line, strlen(line));
		write(temp_fd, "\n", 1);
		free(line);
	}
}

void	heredoc_handler(t_data *data, t_cmd *command)
{
	t_cmd	*current_cmd;
	char	*template;
	char	buffer[1024];
	int		temp_fd;
	ssize_t	bytes_read;

	current_cmd = command;
	template = NULL;
	temp_fd = create_tempfile(data, &template);
	while (current_cmd && current_cmd->operator == RD_HD)
	{
		process_heredoc_input(current_cmd->next->argv[0], temp_fd);
		current_cmd = current_cmd->next;
	}
	close(temp_fd);
	temp_fd = open(template, O_RDONLY);
	if (temp_fd == -1)
	{
		perror("Error reopening temporary file");
		exit(EXIT_FAILURE);
	}
	bytes_read = read(temp_fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		write(STDOUT_FILENO, buffer, bytes_read);
		bytes_read = read(temp_fd, buffer, sizeof(buffer));
	}
	close(temp_fd);
	unlink(template);
}

/*static t_heredoc	*create_and_append_node(t_heredoc **head, char *buffer)
{
	t_heredoc	*new_node;
	t_heredoc	*current;

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
