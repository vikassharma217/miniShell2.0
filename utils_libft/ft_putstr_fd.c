/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:01:36 by vsharma           #+#    #+#             */
/*   Updated: 2023/09/13 16:49:46 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//#include <fcntl.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
	{
		return ;
	}
	write(fd, s, ft_strlen(s));
}

/*int	main()
{
	int		fd = open("test2.txt", O_RDWR);
	char 	teststring1[] = "Hello ! I am writing from main";
	ft_putstr_fd(teststring1, fd);
	close(fd);
}*/
