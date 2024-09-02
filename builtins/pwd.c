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
	char	current_dir[PATH_MAX];

	(void)cmd;
	//Shell does print Error, Bash not
	/*if (cmd->argc > 1)
	{
		write(2, "minishell: pwd: too many arguments\n", 35);
		return (0);
	}*/
	if (getcwd(current_dir, PATH_MAX) != NULL)
		printf("%s\n", current_dir);
	else
	{
		perror("minishell: ");
		return (1);
	}
	return (0);
}
