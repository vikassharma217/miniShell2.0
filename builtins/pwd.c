/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:54:48 by caslan            #+#    #+#             */
/*   Updated: 2024/04/04 14:04:55 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//no malloc version!

int pwd(void)
{
    char cwd[4096]; //PATH_MAX

    if (getcwd(cwd, 4096) != NULL)
    {
        printf("%s\n", cwd); // ft_putendl_fd(cwd, STDOUT_FILENO); //? 
        return (EXIT_SUCCESS);
    }
    else
    {
        perror("minishell: "); //?
        return (EXIT_FAILURE);
    }
}


/*
int	ft_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
	{
		perror("minishell: ");
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (EXIT_SUCCESS);
}*/
