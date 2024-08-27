/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:31:01 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/27 18:49:59 by vsharma          ###   ########.fr       */
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

bool	mismatched_quotes(const char *str)
{
	bool	single_quote_open;
	bool	double_quote_open;

	single_quote_open = false;
	double_quote_open = false;
	while (*str)
	{
		if (*str == '\'' && !double_quote_open)
			single_quote_open = !single_quote_open;
		else if (*str == '"' && !single_quote_open)
			double_quote_open = !double_quote_open;
		str++;
	}
	return (single_quote_open || double_quote_open);
}

bool	invalid_sequence(char *str)
{
	int		i;
	bool	quotes;

	i = 0;
	quotes = false;
	while (str[i])
	{
		if (ft_onstr(QUOTES, str[i]))
			quotes = !quotes;
		if (((str[i] == '>' && str[i + 1] == '<') || (str[i] == '<' && str[i
						+ 1] == '>') || (str[i] == '|' && str[i + 1] == '|'))
			&& !quotes)
			return (true);
		else if ((str[i] == '(' || str[i] == ')' || str[i] == '{'
				|| str[i] == '}' || str[i] == '[' || str[i] == ']'
				|| str[i] == ';' || str[i] == '&' || str[i] == '*') && !quotes)
			return (true);
		i++;
	}
	return (false);
}

bool	invalid_syntax(char *str)
{
	if (str[0] == '|' || str[ft_strlen(str) - 1] == '|' || str[ft_strlen(str)
			- 1] == '>' || str[ft_strlen(str) - 1] == '<')
	{
		return (true);
	}
	return (false);
}

bool	check_operator(char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (ft_onstr(OPERATORS, input[i]))
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
	if (ft_onstr(QUOTES, input[i]))
		quotes = !quotes;
	if (ft_onstr(OPERATORS, input[i]) && !quotes)
	{
		if (input[i] == input[i + 1])
			i = i + 2;
		else
			i++;
		if (input[i] == ' ')
		{
			while (input[i] && input[i] == ' ')
				i++;
			if (ft_onstr(OPERATORS, input[i]))
				return (true);
		}
		if (ft_onstr(OPERATORS, input[i]))
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
		//free(input);
		data->exit_code = 2;
		return (false);
	}
	else if (invalid_sequence(input) || invalid_syntax(input)
		|| invalid_operator(input))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		//free(input);
		data->exit_code = 2;
		return (false);
	}
	return (true);
}
