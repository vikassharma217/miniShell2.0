/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                          :+:      :+:    :+:*/
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:16:15 by vsharma           #+#    #+#             */
/*   Updated: 2023/09/05 15:16:18 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i] != '\0')
		i++;
	return (i);
}

/*int	main(void)
{
	char string1[] = "destination string";
	char string2[] = "source string";
	ft_strlcpy(string1, string2, 4);
	printf("%s\n", string1);
	printf("%zu", ft_strlcpy(string1, string2, 3));
}*/
