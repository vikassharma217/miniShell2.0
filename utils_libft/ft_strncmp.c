/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:11:09 by vsharma           #+#    #+#             */
/*   Updated: 2024/05/08 14:02:14 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cmp_char(char c1, char c2)
{
	if (c1 != c2)
		return (c1 - c2);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (cmp_char(s1[i], s2[i]))
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	if (i < n)
	{
		if (cmp_char(s1[i], s2[i]))
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
	}
	return (0);
}

/*int	main(void)
{
	printf("%d\n", ft_strncmp("ABCDEFG", "ABCHJKD", 5));
}*/
