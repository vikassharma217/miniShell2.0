/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:49:43 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/27 17:27:08 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_status_size(t_data *data)
{
	char	*str;
	int		size;

	str = ft_lltoa(data->exit_code);
	size = ft_strlen(str);
	free(str);
	return (size);
}

void	init_varaible(int *i, int *j, bool *quotes, bool *d_quotes)
{
	*i = 0;
	*j = 0;
	*quotes = false;
	*d_quotes = false;
}

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
	return (j);
}

char	*expand_token(char *str, t_data *data, char *token)
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
}


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
			+ size] != '\"' && !ft_onstr(QUOTES, input[*i + size]) && input[*i
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

int	token_size(char *str, int *i, t_data *data)
{
	int		size;
	char	*name;
	char	*value;

	*i += 1;
	if ((*str + 1) == ' ' || (*str + 1) == '\"')
		return (1);
	size = 0;
	while (str[size + 1] && str[size + 1] != ' ' && !ft_onstr(QUOTES, str[size
				+ 1]) && str[size + 1] != '$')
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

int	input_size(char *str, t_data *data)
{
	int		i;
	int		size;
	bool	quotes;
	bool	d_quotes;

	init_varaible(&i, &size, &quotes, &d_quotes);
	while (str[i])
	{
		if (str[i] == '\"' && !quotes)
			d_quotes = !d_quotes;
		if (str[i] == '\'' && !d_quotes)
			quotes = !quotes;
		if ((str[i] == '$' && str[i + 1] == '?') && !quotes)
		{
			size += exit_status_size(data) - 1;
			i++;
		}
		else if (str[i] == '$' && !quotes)
			size += token_size(&(str[i]), &i, data) - 1;
		else
			i++;
		size++;
	}
	return (size);
}


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
	return (expanded_token);
}