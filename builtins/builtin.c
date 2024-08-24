/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:07:39 by caslan            #+#    #+#             */
/*   Updated: 2024/05/10 14:06:33 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin(t_cmd *cmd, t_data *data)
{
	if (cmd->argv == NULL || cmd->argv[0] == NULL || cmd->argv[0][0] == '\0')
	{
		ft_putstr_fd(" : command not found\n", 2);
		return (true);
	}
	if (ft_is_str_equal(cmd->argv[0], "exit"))
		ft_exit(cmd, data, 0);
	else if (ft_is_str_equal(cmd->argv[0], "unset"))
		data->exit_code = check_unset(cmd, data);
	else if (ft_is_str_equal(cmd->argv[0], "export"))
		data->exit_code = ft_export(cmd, data);
	else if (ft_is_str_equal(cmd->argv[0], "cd"))
		data->exit_code = check_cd(cmd, data);
	else if (ft_strchr(cmd->argv[0], '=') && is_valid(cmd->argv[0]))
		data->exit_code = store_usr_var(cmd->argv[0], &data->env_lst, false);
	else if (ft_is_str_equal(cmd->argv[0], "echo"))
		data->exit_code = echo(cmd);
	else if (ft_is_str_equal(cmd->argv[0], "pwd"))
		data->exit_code = pwd();
	else if (ft_is_str_equal(cmd->argv[0], "env"))
		data->exit_code = env(data);
	else
		return (false);
	return (true);
}
