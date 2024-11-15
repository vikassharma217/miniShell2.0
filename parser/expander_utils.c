/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:07:21 by vsharma           #+#    #+#             */
/*   Updated: 2024/09/10 19:59:56 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Calculate the size of the exit status as a string.
int	exit_status_size(t_data *data)
{
	char	*str;
	int		size;

	str = ft_lltoa(data->exit_code);
	size = ft_strlen(str);
	free(str);
	return (size);
}

// Get the exit status and store it in the provided string.
int	get_exit_status(t_data *data, char *str, int *i)
{
	char	*status;
	int		j;

	*i += 2;
	if (g_signal != 0)
		data->exit_code = 130;
	status = ft_lltoa(data->exit_code);
	j = 0;
	while (status[j])
	{
		str[j] = status[j];
		j++;
	}
	free(status);
	g_signal = 0;
	return (j);
}

// Calculate the size of the variable to be expanded in the token.
int	token_size(char *str, int *i, t_data *data)
{
	int		size;
	char	*name;
	char	*value;

	*i += 1;
	if ((*str + 1) == ' ' || (*str + 1) == '\"')
		return (1);
	size = 0;
	while (str[size + 1] && str[size + 1] != ' ' && !char_in_str(QUOTES,
			str[size + 1]) && str[size + 1] != '$')
		size++;
	if (size == 0)
		return (0);
	name = ft_substr(str, 1, size);
	value = get_fromvlst(name, &data->env_lst);
	free(name);
	*i += size;
	if (!value)
		return (0);
	return (ft_strlen(value));
}

// Calculate the size of the input string after expansion.
int	input_size(char *str, t_data *data)
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
		if ((str[var.i] == '$' && str[var.i + 1] == '?') && !var.quotes)
		{
			var.size += exit_status_size(data) - 1;
			var.i++;
		}
		else if (str[var.i] == '$' && !var.quotes)
			var.size += token_size(&(str[var.i]), &var.i, data) - 1;
		else
			var.i++;
		var.size++;
	}
	return (var.size);
}
