/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:53:28 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/10 10:56:31 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handling_export_error(char *name)
{
	write(2, "minishell: export: `", 20);
	write(2, name, ft_strlen(name));
	write(2, "': is not a valid identifier\n", 29);
	return (1);
}
//Exports an environment variable without a value, creating a new entry

void	export_variable_without_value(char *var_name, t_elst **env_list)
{
	t_elst	*new_var;

	new_var = newnode_env(var_name, NULL, true);
	if (!new_var)
	{
		perror("Failed to create new environment variable");
		return ;
	}
	lstadd_back_env(env_list, new_var);
}
//Prints all exported environment variables
//If a variable has no value, it prints 'declare -x name

static int	print_exported_vars(t_data *data)
{
	t_elst	*current;

	if (!data->env_lst)
		return (0);
	sort_env_list(&data->env_lst);
	current = data->env_lst;
	while (current)
	{
		if (current->exported)
		{
			if (current->value)
				printf("declare -x %s=\"%s\"\n", current->name, current->value);
			else
				printf("declare -x %s\n", current->name);
		}
		current = current->next;
	}
	return (0);
}
//Handles the export command, adding or updating environment variables
//Validates variable names, stores variables with values, marks them as exported

int	export(t_cmd *cmd, t_data *data)
{
	int		any_error;
	int		equal_flag;
	size_t	i;

	if (cmd->argv[1] == NULL)
		return (print_exported_vars(data));
	any_error = 0;
	equal_flag = 0;
	i = 0;
	while (cmd->argv[++i])
	{
		if (!is_valid_variable(cmd->argv[i]))
			any_error = handling_export_error(cmd->argv[i]);
		else
		{
			equal_flag = char_in_str(cmd->argv[i], '=');
			if (equal_flag)
				store_env_var(cmd->argv[i], &data->env_lst, true);
			else if (!is_var_exported(cmd->argv[i], &data->env_lst))
				export_variable_without_value(ft_strdup(cmd->argv[i]),
					&data->env_lst);
		}
	}
	return (any_error);
}
