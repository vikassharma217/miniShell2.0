/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:39:53 by vsharma           #+#    #+#             */
/*   Updated: 2024/09/05 19:05:53 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d;
	size_t	s;
	size_t	dstl;
	size_t	srcl;

	dstl = ft_strlen(dst);
	srcl = ft_strlen((char *)src);
	d = dstl;
	s = 0;
	if (dstl < size - 1 && size > 0)
	{
		while (src[s] != '\0' && dstl + s < size - 1)
		{
			dst[d] = src[s];
			d++;
			s++;
		}
		dst[d] = 0;
	}
	if (dstl >= size)
		dstl = size;
	return (dstl + srcl);
}

/*int	main(void)
{
	char string1[] = "destination string";
	char string2[] = "source string";
	ft_strlcat(string1, string2, 6);
	printf("%s\n", string1);
}*/
