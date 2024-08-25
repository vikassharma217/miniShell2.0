/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscherl <rscherl@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:51:38 by rscherl           #+#    #+#             */
/*   Updated: 2024/08/24 17:51:43 by rscherl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_cd(t_cmd *cmd, t_data *data)
{
	if (cmd->argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	else
		return (cd(cmd->argv[1], data));
}

static int	check_unset(t_cmd *cmd, t_data *data)
{
	if (cmd->argc == 1)
		return (EXIT_SUCCESS);
	return (unset(cmd, &data->env_lst));
}

bool	is_valid(char *str)
{
	size_t	i;

	i = 0;
	if (ft_is_str_equal(str, "="))
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (i > 0 && !isdigit(str[0]));
}

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
		data->exit_code = export(cmd, data);
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
