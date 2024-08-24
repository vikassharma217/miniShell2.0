/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscherl <rscherl@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:53:56 by rscherl           #+#    #+#             */
/*   Updated: 2024/08/24 17:53:58 by rscherl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	error_message_unset(char *name)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd("not a valid", STDERR_FILENO);
}

int	f_unset(char *name, t_elst **head)
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
	while (current) //updated that *head will be changed if unset to the next
	{
		if (ft_is_str_equal(name, current->name))
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->name);
			free(current->value);
			free(current);
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

	if (!cmd || !cmd->argv || !head)
		return (EXIT_FAILURE);
	i = 0;
	while (++i < cmd->argc)
		f_unset(cmd->argv[i], head);
	return (EXIT_SUCCESS);
}






/*static void	error_message_unset(char *name)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd("not a valid", STDERR_FILENO);
}

int	f_unset(char *name, t_elst **head)
{
	t_elst	*temp;
	t_elst	*next_node;

	temp = *head;
	if (ft_strchr(name, '='))
	{
		error_message_unset(name);
		return (EXIT_FAILURE);
	}
	while (temp && temp->next != NULL)
	{
		if (ft_is_str_equal(name, temp->next->name))
		{
			next_node = temp->next->next;
			free(temp->next->name);
			free(temp->next->value);
			free(temp->next);
			temp->next = next_node;
			break ;
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

int	unset(t_cmd *cmd, t_elst **head)
{
	int	i;

	i = 1;
	while (i < cmd->argc)
	{
		f_unset(cmd->argv[i], head);
		i++;
	}
	return (EXIT_SUCCESS);
}*/
