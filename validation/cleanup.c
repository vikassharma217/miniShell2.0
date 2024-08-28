/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:32:44 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/28 11:54:38 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lstclear_env(t_elst **head)
{
	t_elst	*temp;
	t_elst	*next_node;

	if (!head)
		return ;
	temp = *head;
	while (temp != NULL)
	{
		next_node = temp->next;
		free(temp->name);
		free(temp->value);
		free(temp);
		temp = next_node;
	}
	*head = NULL;
}

void	free_all_data(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	lstclear_par(t_cmd **head)
{
	t_cmd	*temp;
	t_cmd	*next_node;

	if (!head)
		return ;
	temp = *head;
	while (temp != NULL)
	{
		next_node = temp->next;
		free_all_data(temp->argv);
		free(temp);
		temp = next_node;
	}
	*head = NULL;
}

void	free_parsed_tokens(t_cmd **cmd_list, t_data *data)
{
	lstclear_par(cmd_list);
	*cmd_list = NULL;
	data->head = NULL;
}

void	ft_clear_all(t_data *data)
{
	rl_clear_history();
	if (data->env_lst)
		lstclear_env(&data->env_lst);
	if (data->head)
		lstclear_par(&data->head);
}
