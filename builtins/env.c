/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscherl <rscherl@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:52:05 by rscherl           #+#    #+#             */
/*   Updated: 2024/08/24 17:52:48 by rscherl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	return (EXIT_SUCCESS);
}

/*int	ft_env(t_data *data)
{
	t_elst	*temp;

	temp = data->env_lst;
	while (temp != NULL)
	{
		if (temp->exported)
			printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}*/
