/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:52:05 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/02 17:03:42 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//Prints the list of environment variables that are marked as exported.
//Each variable is printed in the format 'name=value'
int	env(t_data *data)
{
	t_elst	*current;

	current = data->env_lst;
	while (current)
	{
		if (current->exported)
		{
			if (current->name && current->value)
				printf("%s=%s\n", current->name, current->value);
		}
		current = current->next;
	}
	return (0);
}
