/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_syntax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:57:35 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/28 13:22:08 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (char_in_str(QUOTES, str[i]))
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
