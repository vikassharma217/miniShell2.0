/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_syntax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:57:35 by vsharma           #+#    #+#             */
/*   Updated: 2024/09/10 20:37:50 by vsharma          ###   ########.fr       */
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

bool	check_invalid_operator_sequence(char *str, int *i)
{
	char	first_op;

	if (str[*i] == '|' || str[*i] == '<' || str[*i] == '>')
	{
		first_op = str[*i];
		(*i)++;
		while (str[*i] && ft_isspace(str[*i]))
			(*i)++;
		if ((first_op == '|' && str[*i] == '|') || (first_op == '<'
				&& str[*i] == '>') || (first_op == '>' && str[*i] == '<'))
		{
			return (true);
		}
	}
	return (false);
}

/* handel 2 consecutive operator with and withous space in betn them*/
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
		if (!quotes)
		{
			if (check_invalid_operator_sequence(str, &i))
				return (true);
		}
		else if ((str[i] == '(' || str[i] == ')' || str[i] == '{'
				|| str[i] == '}' || str[i] == '[' || str[i] == ']'
				|| str[i] == ';' || str[i] == '&' || str[i] == '*') && !quotes)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

/* handle command start or end with operator*/
bool	invalid_syntax(char *str)
{
	if (str[0] == '|' || str[ft_strlen(str) - 1] == '|' || str[ft_strlen(str)
			- 1] == '>' || str[ft_strlen(str) - 1] == '<')
	{
		return (true);
	}
	return (false);
}
