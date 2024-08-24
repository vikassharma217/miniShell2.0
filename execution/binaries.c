/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:40:23 by caslan            #+#    #+#             */
/*   Updated: 2024/05/08 12:02:27 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_the_path(char *cmd, char **paths)
{
	size_t	i;
	char	*temp;
	char	*path;

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = concat_and_free(temp, cmd);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	free_all(char **path)
{
	size_t	i;

	i = 0;
	if (!path)
		return ;
	while (path[i])
	{
		free(path[i]);
		path[i] = NULL;
		i++;
	}
	free(path);
	path = NULL;
}

static void	exit_function(t_data *data, char **paths, char *cmd,
		int exit_status)
{
	if (cmd)
		perror(cmd);
	free_all(paths);
	(void)data;
	if (g_signal != CNTL_C)
		exit(exit_status);
	else
		exit(130);
}

static char	**get_paths(t_elst *env_lst)
{
	t_elst	*temp;

	temp = env_lst;
	while (!ft_is_str_equal("PATH", temp->name))
	{
		temp = temp->next;
		if (temp == NULL)
			return (NULL);
	}
	return (ft_split(temp->value, ':'));
}

void	binaries(t_cmd *cmd, t_data *data)
{
	char	*path;
	char	**paths;

	path = cmd->argv[0];
	paths = get_paths(data->env_lst);
	if (is_path(cmd))
	{
		if (execve(path, cmd->argv, data->env) == -1)
			exit_function(data, paths, cmd->argv[0], 127);
		exit_function(data, paths, NULL, EXIT_SUCCESS);
		return ;
	}
	path = get_the_path(cmd->argv[0], paths);
	if (path == NULL)
	{
		msg_error(cmd->argv[0], data);
		exit_function(data, paths, NULL, 127);
	}
	if (execve(path, cmd->argv, data->env) == -1)
	{
		free(path);
		exit_function(data, paths, cmd->argv[0], 126);
	}
	free(path);
	exit_function(data, paths, NULL, EXIT_SUCCESS);
}
