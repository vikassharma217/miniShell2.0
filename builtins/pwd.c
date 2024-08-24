/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscherl <rscherl@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:53:40 by rscherl           #+#    #+#             */
/*   Updated: 2024/08/24 17:53:43 by rscherl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//no malloc version!

int pwd(void)
{
    char cwd[PATH_MAX]; //PATH_MAX

    if (getcwd(cwd, PATH_MAX) != NULL)
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
