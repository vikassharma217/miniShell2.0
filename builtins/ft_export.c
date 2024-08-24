/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:06:26 by caslan            #+#    #+#             */
/*   Updated: 2024/05/03 10:49:45 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_exported(char *name, t_data *data)
{
	t_elst	*temp;

	temp = data->env_lst;
	while (temp != NULL)
	{
		if (ft_is_str_equal(name, temp->name))
		{
			temp->exported = true;
			break ;
		}
		temp = temp->next;
	}
}

static int	export_error_message(char *n)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(n, STDERR_FILENO);
	ft_putendl_fd("': not a valid", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static int	for_one(t_data *data)
{
	t_elst	*temp;

	temp = data->env_lst;
	while (temp != NULL)
	{
		if (temp->exported)
			printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_export(t_cmd *cmd, t_data *data)
{
	int		err;
	size_t	i;

	if (cmd->argc == 1)
		return (for_one(data));
	err = EXIT_SUCCESS;
	i = 0;
	while (cmd->argv[++i])
	{
		if (!is_valid(cmd->argv[i]))
			err = export_error_message(cmd->argv[i]);
		else if (ft_onstr(cmd->argv[i], '='))
		{
			store_usr_var(cmd->argv[i], &data->env_lst, true);
			continue ;
		}
		else
			ft_exported(cmd->argv[i], data);
	}
	return (err);
}
