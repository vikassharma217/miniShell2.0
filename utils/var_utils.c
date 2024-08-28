/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:55:19 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/28 13:22:53 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Check if a given environment variable is exported.
bool	is_var_exported(char *name, t_elst **head)
{
	t_elst	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (str_equals(name, temp->name))
			return (temp->exported);
		temp = temp->next;
	}
	return (false);
}

// Add or update an environment variable in the list.
int	store_env_var(char *cmd, t_elst **head, bool export)
{
	char	**line;

	line = split_env_var(cmd);
	if (is_var_exported(line[0], head) && !export)
		export = true;
	unset_variable(line[0], head);
	lstadd_back_env(head, newnode_env(line[0], line[1], export));
	free(line);
	return (EXIT_SUCCESS);
}
