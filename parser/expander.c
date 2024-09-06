/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:49:43 by vsharma           #+#    #+#             */
/*   Updated: 2024/09/06 09:56:34 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_token(char *str, t_data *data, char *token)
{
	t_var var;

	var.i = 0;
	var.size = 0;
	var.quotes = false;
	var.d_quotes = false;
	while (str[var.i])
	{
		if (str[var.i] == '\"' && !var.quotes)
			var.d_quotes = !var.d_quotes;
		if (str[var.i] == '\'' && !var.quotes)
			var.quotes = !var.quotes;
		if (str[var.i] == '$' && str[var.i + 1] == '?' && !var.quotes)
			var.size += get_exit_status(data, &(token[var.size]), &var.i);
		else if (str[var.i] == '$' && !var.quotes)
			var.size += get_variable(&(token[var.size]), str, &var.i, data);
		else
			token[var.size++] = str[var.i++];
	}
	token[var.size] = '\0';
	return (token);
}

// Expands a token by handling quotes and environment variable substitution.
/*char	*expand_token(char *str, t_data *data, char *token)
{
	int		i;
	int		j;
	bool	quotes;
	bool	d_quotes;

	init_varaible(&i, &j, &quotes, &d_quotes);
	while (str[i])
	{
		if (str[i] == '\"' && !quotes)
			d_quotes = !d_quotes;
		if (str[i] == '\'' && !quotes)
			quotes = !quotes;
		if (str[i] == '$' && str[i + 1] == '?' && !quotes)
			j += get_exit_status(data, &(token[j]), &i);
		else if (str[i] == '$' && !quotes)
			j += get_variable(&(token[j]), str, &i, data);
		else
			token[j++] = str[i++];
	}
	token[j] = '\0';
	return (token);
}*/

/* Retrieves the value of a variable from the environment
	and inserts it into the token*/
int	get_variable(char *str, char *input, int *i, t_data *data)
{
	char	*value;
	int		size;
	int		j;
	int		k;

	size = 0;
	j = 0;
	k = 0;
	*i += 1;
	if (!input[*i] || input[*i] == ' ' || input[*i] == '\"')
	{
		str[0] = '$';
		return (1);
	}
	while (input[*i + size] && input[*i + size] != ' ' && input[*i
			+ size] != '\"' && !char_in_str(QUOTES, input[*i + size]) && input[*i
			+ size] != '$')
		size++;
	value = get_varvalue_fromvlst(ft_substr(input, *i, size), data);
	*i += size;
	if (!value)
		return (0);
	while (value[k])
		str[j++] = value[k++];
	return (j);
}

// Initializes the expander by calculating and expanding tokens in the input.
char	*init_expander(char *str, t_data *data)
{
	char	*token;
	char	*expanded_token;

	if (!str || !data)
		return (NULL);
	token = malloc(sizeof(char) * (input_size(str, data) + 2));
	if (!token)
		return (NULL);
	expanded_token = expand_token(str, data, token);
	if (!expanded_token)
	{
		return (NULL);
	}
	//free(token);
	return (expanded_token);
}