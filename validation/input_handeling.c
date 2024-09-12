/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handeling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:31:01 by vsharma           #+#    #+#             */
/*   Updated: 2024/09/12 11:17:32 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	check_operator(char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (char_in_str(OPERATORS, input[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	invalid_operator_helper(char *input)
{
	size_t	i;
	bool	quotes;

	i = 0;
	quotes = false;
	if (char_in_str(QUOTES, input[i]))
		quotes = !quotes;
	if (char_in_str(OPERATORS, input[i]) && !quotes)
	{
		if (input[i] == input[i + 1])
			i = i + 2;
		else
			i++;
		if (input[i] == ' ')
		{
			while (input[i] && input[i] == ' ')
				i++;
			if (char_in_str(OPERATORS, input[i]))
				return (true);
		}
		if (char_in_str(OPERATORS, input[i]))
			return (true);
	}
	return (false);
}

bool	invalid_operator(char *input)
{
	size_t	i;

	i = 0;
	while (check_operator(&input[i]))
	{
		invalid_operator_helper(input);
		i++;
	}
	return (false);
}

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
	if (*input == '\0')
		return (false);
	else if (mismatched_quotes(input))
	{
		ft_putendl_fd("minishell: syntax error", 2);
		data->exit_code = 2;
		return (false);
	}
	else if (invalid_sequence(input) || invalid_syntax(input)
		|| invalid_operator(input))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		data->exit_code = 2;
		return (false);
	}
	return (true);
}
