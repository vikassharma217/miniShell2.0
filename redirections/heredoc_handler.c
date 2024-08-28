/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:55:27 by rscherl           #+#    #+#             */
/*   Updated: 2024/08/28 13:22:53 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_heredoc	*create_and_append_node(t_heredoc **head, char *buffer)
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

void	heredoc_handler(t_data *data, t_cmd *node)
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
