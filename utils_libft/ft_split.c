/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:17:48 by vsharma           #+#    #+#             */
/*   Updated: 2024/04/26 10:05:26 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_scount(char const *s, char c)
{
	size_t	j;

	if (!s || !*s)
		return (0);
	j = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			j++;
		while (*s && *s != c)
			s++;
	}
	return (j);
}

static size_t	ft_slen(const char *s, char c)
{
	size_t	wlen;

	if (!ft_strchr(s, c))
		wlen = ft_strlen(s);
	else
		wlen = ft_strchr(s, c) - s;
	return (wlen);
}

static void	*ft_mclean(char **strs, int i)
{
	while (i >= 0)
	{
		free(strs[i]);
		i--;
	}
	free(strs);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t		count;
	int			i;
	char		**arr;

	if (!s)
		return (0);
	count = ft_scount(s, c);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		count = ft_slen(s, c);
		arr[i] = ft_substr(s, 0, count);
		if (!arr[i++])
			return (ft_mclean(arr, --i));
		s += count;
	}
	arr[i] = 0;
	return (arr);
}
