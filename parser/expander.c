/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:49:43 by vsharma           #+#    #+#             */
/*   Updated: 2024/09/10 20:19:29 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Retrieves the value of a variable from the environment
	and inserts it into the token*/
static int	execute_expansion(char *dst, char *input, int *i, t_data *data)
{
	char	*val;
	int		len;
	int		dst_idx;
	int		val_idx;

	len = 0;
	dst_idx = 0;
	val_idx = 0;
	*i += 1;
	if (!input[*i] || input[*i] == ' ' || input[*i] == '\"')
	{
		dst[0] = '$';
		return (1);
	}
	while (input[*i + len] && input[*i + len] != ' ' && input[*i + len] != '\"'
		&& !char_in_str(QUOTES, input[*i + len]) && input[*i + len] != '$')
		len++;
	val = retrieve_env_value(ft_substr(input, *i, len), data);
	*i += len;
	if (!val)
		return (0);
	while (val[val_idx])
		dst[dst_idx++] = val[val_idx++];
	return (dst_idx);
}

// Expand the env var and return the expanded var value
char	*expand_token(char *str, t_data *data, char *token)
{
	t_var	var;

	var.i = 0;
	var.size = 0;
	var.quotes = false;
	var.d_quotes = false;
	while (str[var.i])
	{
		if (str[var.i] == '\"' && !var.quotes)
			var.d_quotes = !var.d_quotes;
		if (str[var.i] == '\'' && !var.d_quotes)
			var.quotes = !var.quotes;
		if (str[var.i] == '$' && str[var.i + 1] == '?' && !var.quotes)
			var.size += get_exit_status(data, &(token[var.size]), &var.i);
		else if (str[var.i] == '$' && !var.quotes)
			var.size += execute_expansion(&(token[var.size]), str, &var.i,
					data);
		else
			token[var.size++] = str[var.i++];
	}
	token[var.size] = '\0';
	return (token);
}

// Initializes the expander by calculating and expanding tokens in the input.
char	*init_expander(char *input_str, t_data *data)
{
	char	*token;
	char	*result;

	if (!input_str || !data)
		return (NULL);
	token = malloc(sizeof(char) * (input_size(input_str, data) + 1));
	if (!token)
		return (NULL);
	result = expand_token(input_str, data, token);
	if (!result)
	{
		return (NULL);
	}
	return (result);
}
