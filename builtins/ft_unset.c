/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:10:10 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/21 13:10:21 by vsharma          ###   ########.fr       */
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

int	ft_unset(t_cmd *cmd, t_elst **head)
{
	int	i;

	i = 1;
	while (i < cmd->argc)
	{
		f_unset(cmd->argv[i], head);
		i++;
	}
	return (EXIT_SUCCESS);
}