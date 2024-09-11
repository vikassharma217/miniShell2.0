/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:33:17 by vsharma           #+#    #+#             */
/*   Updated: 2024/09/11 13:42:27 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bzero(void *string, size_t n)
{
	char	*temp;
	size_t	i;

	i = 0;
	temp = string;
	while (i < n)
	{
		temp[i] = 0;
		i++;
	}
}

/*int	main(void)
{
	char	s[99] = "Hello there";
	ft_bzero (s, 4);
	printf("%s\n", s);
}*/