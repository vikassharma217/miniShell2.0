/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:38:25 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/29 17:38:13 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* calculate size of input string after proccessing(excluding) quotes*/
int	quotes_size(char *str)
{
	int		i;
	int		size;
	char	quotes;

	i = 0;
	size = 0;
	while (str[i])
	{
		while (str[i] && !char_in_str(QUOTES, str[i]))
		{
			i++;
			size++;
		}
		if (!str[i])
			break ;
		quotes = str[i++];
		while (str[i] && str[i] != quotes)
		{
			i++;
			size++;
		}
		quotes = 0;
	}
	return (size);
}

char	*allocate_memory(char *str)
{
	char	*out;

	out = malloc(sizeof(char) * (quotes_size(str) + 1));
	if (!out)
	{
		free(str);
		return (NULL);
	}
	return (out);
}

char	*process_string(char *str, char *out)
{
	int		i;
	int		j;
	char	quotes;

	i = 0;
	j = 0;
	quotes = '\0';
	while (str[i])
	{
		while (str[i] && !char_in_str(QUOTES, str[i]))
			out[j++] = str[i++];
		if (!str[i])
			break ;
		quotes = str[i];
		i++;
		while (str[i] && str[i] != quotes)
			out[j++] = str[i++];
		quotes = '\0';
	}
	out[j] = '\0';
	free(str);
	return (out);
}

/* proccessing a string that contain quotes*/
char	*handel_quotes(char *str)
{
	char	*out;

	out = allocate_memory(str);
	if (!out)
		return (NULL);
	return (process_string(str, out));
}
