/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:53:40 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/03 08:29:50 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//printing the current working directory
//If getcwd fails, it prints the saved path or an error message
int	pwd(t_cmd *cmd, t_data *data)
{
	char	current_dir[PATH_MAX];

	(void)cmd;
	if (getcwd(current_dir, PATH_MAX) != NULL)
		printf("%s\n", current_dir);
	else
	{
		if (data->saved_path[0] != '\0')
		{
			printf("%s\n", data->saved_path);
			return (0);
		}
		else
		{
			perror("minishell: ");
			return (1);
		}
	}
	return (0);
}
