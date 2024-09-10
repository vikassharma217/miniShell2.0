/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:51:38 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/08 18:50:54 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_valid_variable(char *str)
{
	size_t	i;

	i = 0;
	if (str_equals(str, "="))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (i > 0 && !ft_isdigit(str[0]));
}

int	builtin(t_cmd *cmd, t_data *data)
{
	if (str_equals(cmd->argv[0], "cd"))
		data->exit_code = cd(cmd, data, cmd->argv[1]);
	else if (str_equals(cmd->argv[0], "echo"))
		data->exit_code = echo(cmd);
	else if (str_equals(cmd->argv[0], "env"))
		data->exit_code = env(data);
	else if (str_equals(cmd->argv[0], "exit"))
		exit_shell(cmd, data);
	else if (str_equals(cmd->argv[0], "export"))
		data->exit_code = export(cmd, data);
	else if (str_equals(cmd->argv[0], "pwd"))
		data->exit_code = pwd(cmd, data);
	else if (str_equals(cmd->argv[0], "unset"))
		data->exit_code = unset(cmd, &data->env_lst);
	else if (ft_strchr(cmd->argv[0], '=') && is_valid_variable(cmd->argv[0]))
		data->exit_code = store_env_var(cmd->argv[0], &data->env_lst, 0);
	else
		return (0);
	return (1);
}
