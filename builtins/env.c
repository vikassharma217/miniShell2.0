/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:55:40 by caslan            #+#    #+#             */
/*   Updated: 2024/04/04 14:04:38 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int env(t_data *data)
{
    t_elst *current;

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
