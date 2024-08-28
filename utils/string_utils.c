/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:44:58 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/28 13:23:36 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	char_in_str(const char *str, int ch)
{
	size_t	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
			return (true);
		i++;
	}
	return (false);
}

bool	str_equals(char *str1, char *str2)
{
	size_t	i;

	if ((str1 && !str2) || (!str1 && str2))
		return (false);
	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (false);
		i++;
	}
	return (true);
}

char	*strip_whitespace(char *str)
{
	const char *start;
	const char *end;
	size_t len;
	char *trimmed_str;

	start = str;
	end = str + ft_strlen(str) - 1;
	while (ft_isspace((unsigned char)*start))
		start++;
	while (end > start && ft_isspace((unsigned char)*end))
		end--;
	len = (end - start) + 1;
	trimmed_str = (char *)malloc(len + 1);
	if (!trimmed_str)
	{
		free(str);
		exit(EXIT_FAILURE);
	}
	ft_strncpy(trimmed_str, start, len);
	trimmed_str[len] = '\0';
	free(str);
	return (trimmed_str);
}