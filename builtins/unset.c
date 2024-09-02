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
		return (1);
	prev = NULL;
	current = *head;
	if (ft_strchr(name, '='))
	{
		write(2, "minishell: unset: `", 19);
		write(2, name, ft_strlen(name));
		write(2, "': not a valid identifier\n", 27);
		return (1);
	}
	while (current)
	{
		if (str_equals(name, current->name))
		{
			remove_current_node(head, current, prev);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

int	unset(t_cmd *cmd, t_elst **head)
{
	int	i;
	int	status;

	status = 0;
	if (cmd->argc == 1)
		return (status);
	if (!cmd || !cmd->argv || !head)
		return (1);
	i = 0;
	while (++i < cmd->argc)
	{
		if (unset_variable(cmd->argv[i], head) == 1)
			status = 1;
	}
	return (status);
}
