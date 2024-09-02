/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:53:56 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/02 17:04:22 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	error_message_unset(char *name)
{
	write(2, "minishell: unset: `", 19);
	write(2, name, ft_strlen(name));
	write(2, "': not a valid identifier\n", 27);
}

static void	remove_current_node(t_elst **head, t_elst *current, t_elst *prev)
{
	if (prev == NULL)
		*head = current->next;
	else
	{
		prev->next = current->next;
	}
	free(current->name);
	free(current->value);
	free(current);
}

int	unset_variable(char *name, t_elst **head)
{
	t_elst	*current;
	t_elst	*prev;

	if (!head || !*head)
		return (EXIT_FAILURE);
	prev = NULL;
	current = *head;
	if (ft_strchr(name, '='))
	{
		error_message_unset(name);
		return (EXIT_FAILURE);
	}
	while (current)
	{
		if (str_equals(name, current->name))
		{
			remove_current_node(head, current, prev);
			return (EXIT_SUCCESS);
		}
		prev = current;
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	unset(t_cmd *cmd, t_elst **head)
{
	int	i;
	int	status;

	if (cmd->argc == 1)
		(EXIT_SUCCESS);
	status = EXIT_SUCCESS;
	if (!cmd || !cmd->argv || !head)
		return (EXIT_FAILURE);
	i = 0;
	while (++i < cmd->argc)
	{
		if (unset_variable(cmd->argv[i], head) == EXIT_FAILURE)
			status = EXIT_FAILURE;
	}
	return (status);
}
