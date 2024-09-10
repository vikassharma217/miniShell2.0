/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handeling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:31:01 by vsharma           #+#    #+#             */
/*   Updated: 2024/09/10 13:37:34 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_minishell(int status_code, t_data *data)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	data->exit_code = status_code;
	if (data)
		ft_clear_all(data);
	exit(data->exit_code);
}


bool	input_validation(char *input, t_data *data)
{
	if (input == NULL)
	{
		exit_minishell(EXIT_SUCCESS, data);
	}
	if (input[0] == '\0')
		return (false);
	else if (mismatched_quotes(input))
	{
		ft_putendl_fd("minishell: syntax error", 2);
		data->exit_code = 2;
		return (false);
	}
	else if (invalid_sequence(input) || invalid_syntax(input))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		data->exit_code = 2;
		return (false);
	}
	return (true);
}
