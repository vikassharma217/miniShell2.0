/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:47:03 by vsharma           #+#    #+#             */
/*   Updated: 2024/09/09 10:53:32 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Creates a new node for an environment variable linked list.

t_elst	*newnode_env(char *var_name, char *var_value, bool is_exported)
{
	t_elst	*new_node;

	new_node = malloc(sizeof(t_elst));
	if (!new_node)
		return (NULL);
	new_node->name = var_name;
	new_node->value = var_value;
	new_node->exported = is_exported;
	new_node->next = NULL;
	return (new_node);
}

t_elst	*lstlast_env(t_elst *node)
{
	while (node)
	{
		if (!node->next)
			break ;
		node = node->next;
	}
	return (node);
}

void	lstadd_back_env(t_elst **head, t_elst *new)
{
	t_elst	*temp;

	if (head)
	{
		if (!*head)
			*head = new;
		else
		{
			temp = lstlast_env(*(head));
			temp->next = new;
		}
	}
}

char	*get_fromvlst(char *var_name, t_elst **head)
{
	t_elst	*temp;

	temp = *head;
	if (!var_name || !head)
		return (NULL);
	while (temp != NULL)
	{
		if (str_equals(var_name, temp->name))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

char	*retrieve_env_value(char *env_name, t_data *data)
{
	char	*env_value;

	if (!env_name || !data)
		return (NULL);
	env_value = get_fromvlst(env_name, &data->env_lst);
	if (!env_value)
	{
		free(env_name);
		return (NULL);
	}
	free(env_name);
	return (env_value);
}
