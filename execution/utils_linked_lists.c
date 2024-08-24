/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_linked_lists.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:29:24 by caslan            #+#    #+#             */
/*   Updated: 2024/04/04 14:05:16 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	size_of_list(t_cmd *list)
{
	t_cmd	*temp;
	size_t	len;

	temp = list;
	len = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		len++;
	}
	return (len);
}
