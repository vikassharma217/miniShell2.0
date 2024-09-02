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
	return (1);
}

void	export_variable_without_value(char *var_name, t_elst **env_list)
{
	t_elst *new_var;

	new_var = newnode_env(var_name, NULL, true);
    if (!new_var)
	{
		perror ("Failed to create new environment variable");
		return ;
    }
	lstadd_back_env(env_list, new_var);
}

static int	print_exported_vars(t_data *data)
{
	t_elst	*current;

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

int	export(t_cmd *cmd, t_data *data)
{
	int		any_error;
	int		equal_flag;
	size_t	i;

	if (cmd->argc == 1)
		return (print_exported_vars(data));
	any_error = 0;
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
			else if (!is_var_exported(cmd->argv[i], &data->env_lst))
				export_variable_without_value(ft_strdup(cmd->argv[i]), &data->env_lst);
		}
	}
	return (any_error);
}
