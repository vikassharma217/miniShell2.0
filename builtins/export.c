/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:53:28 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/02 17:04:10 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	export_error_message(char *n)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(n, STDERR_FILENO);
	ft_putendl_fd("': not a valid", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static void	set_exported_flag(char *name, t_data *data)
{
	t_elst	*current;

	current = data->env_lst;
	while (current != NULL)
	{
		if (str_equals(name, current->name))
		{
			current->exported = true;
			break ;
		}
		current = current->next;
	}
}

static int	print_exported_vars(t_data *data)
{
	t_elst	*current;

	current = data->env_lst;
	while (current)
	{
		if (current->exported)
			printf("declare -x %s=\"%s\"\n", current->name, current->value);
		else
			printf("declare -x %s\n", current->name);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	export(t_cmd *cmd, t_data *data)
{
	int		any_error;
	int		equal_flag;
	size_t	i;

	if (cmd->argc == 1)
		return (print_exported_vars(data));
	any_error = EXIT_SUCCESS;
	equal_flag = 0;
	i = 0;
	while (cmd->argv[++i])
	{
		if (!is_valid_variable(cmd->argv[i]))
			any_error = export_error_message(cmd->argv[i]);
		else
		{
			equal_flag = char_in_str(cmd->argv[i], '=');
			if (equal_flag)
				store_env_var(cmd->argv[i], &data->env_lst, true);
			else
				set_exported_flag(cmd->argv[i], data);
		}
	}
	return (any_error);
}

/*static void	ft_exported(char *name, t_data *data)
{
	t_elst	*current;

	current = data->env_lst;
	while (current != NULL)
	{
		if (str_equals(name, current->name))
		{
			current->exported = true;
			break ;
		}
		current = current->next;
	}
}

static int	export_error_message(char *n)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(n, STDERR_FILENO);
	ft_putendl_fd("': not a valid", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static int	print_exported_vars(t_data *data)
{
	t_elst	*current;

	current = data->env_lst;
	while (current != NULL)
	{
		if (current->exported)
			printf("declare -x %s=\"%s\"\n", current->name, current->value);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_export(t_cmd *cmd, t_data *data)
{
	int		err;
	size_t	i;

	if (cmd->argc == 1)
		return (print_exported_vars(data));
	err = EXIT_SUCCESS;
	i = 0;
	while (cmd->argv[++i])
	{
		if (!is_valid(cmd->argv[i]))
			err = export_error_message(cmd->argv[i]);
		else if (char_in_str(cmd->argv[i], '='))
		{
			store_usr_var(cmd->argv[i], &data->env_lst, true);
			continue ;
		}
		else
			ft_exported(cmd->argv[i], data);
	}
	return (err);
}*/
