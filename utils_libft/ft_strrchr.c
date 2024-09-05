/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:24:41 by vsharma           #+#    #+#             */
/*   Updated: 2023/09/07 15:24:43 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strrchr(const char *string, int c)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		i++;
	}
	while (i >= 0)
	{
		if (string[i] == (char)c)
			return ((char *)(string + i));
		i--;
	}
	return (0);
}

/*int	main(void)
{
	printf("%s\n", ft_strchr("This is string", 'T'));
	printf("%s\n", strchr("This is string", 's'));
}*/		
