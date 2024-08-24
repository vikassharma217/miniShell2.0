/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:53:23 by caslan            #+#    #+#             */
/*   Updated: 2024/05/10 12:08:59 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_cd(t_cmd *cmd, t_data *data)
{
	if (cmd->argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	else
		return (ft_cd(cmd->argv[1], data));
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
		i += 1;
	}
	return (i > 0 && !isdigit(str[0]));
}

int	check_unset(t_cmd *cmd, t_data *data)
{
	if (cmd->argc == 1)
		return (EXIT_SUCCESS);
	return (unset(cmd, &data->env_lst));
}
