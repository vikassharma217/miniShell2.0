/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:13:02 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/28 13:13:30 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// creat new node for parsed token linked list
t_cmd	*newnode_par(int argc)
{
	t_cmd *new_node;

	new_node = malloc(sizeof(t_cmd));
	if (new_node == NULL)
		return (NULL);
	new_node->argc = argc;
	new_node->argv = malloc((argc + 1) * sizeof(char *));
	if (!new_node->argv)
		return (NULL);
	new_node->operator= NONE;
	new_node->next = NULL;
	return (new_node);
}