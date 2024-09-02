/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:53:40 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/02 17:04:16 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(t_cmd *cmd)
{
	char	cwd[PATH_MAX];

	if (cmd->argc > 1)
	{
		write(2, "minishell: pwd: too many arguments\n", 35);
			// pwd: too many arguments?
		return (EXIT_FAILURE);
	}
	else if (getcwd(cwd, PATH_MAX) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("minishell: ");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
