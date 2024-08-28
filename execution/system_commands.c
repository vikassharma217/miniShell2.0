/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:54:20 by rscherl           #+#    #+#             */
/*   Updated: 2024/08/28 13:22:53 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exit_with_cleanup(char *cmd, t_data *data, char **paths,
		int exit_code)
{
	size_t	i;

	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (paths)
	{
		i = 0;
		while (paths[i])
			free(paths[i++]);
		free(paths);
	}
	ft_clear_all(data);
	exit(exit_code);
}

static char	*combine_and_release(char *str1, char *str2)
{
	char	*result;

	result = ft_strjoin(str1, str2);
	free(str1);
	return (result);
}

static char	*get_env_variable(t_elst *env_lst, char *name)
{
	while (env_lst)
	{
		if (str_equals(name, env_lst->name))
			return (ft_strdup(env_lst->value));
		env_lst = env_lst->next;
	}
	return (NULL);
}

static void	search_and_exec(char *cmd, t_elst *env_lst, t_cmd *cmd_struct,
		t_data *data)
{
	char	**paths;
	char	*env_paths;
	char	*path;
	size_t	i;

	i = 0;
	env_paths = get_env_variable(env_lst, "PATH");
	if (!env_paths)
		exit_with_cleanup(cmd, data, NULL, 127);
	paths = ft_split(env_paths, ':');
	free(env_paths);
	while (paths[i])
	{
		path = combine_and_release(ft_strjoin(paths[i], "/"), cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			if (execve(path, cmd_struct->argv, data->env) == -1)
			{
				perror(path);
				free(path);
				exit_with_cleanup(NULL, data, paths, 126);
			}
			free(path);
			exit_with_cleanup(NULL, data, paths, 0);
		}
		free(path);
		i++;
	}
	exit_with_cleanup(cmd, data, paths, 127);
}

void	system_commands(t_cmd *cmd, t_data *data)
{
	if (ft_strchr(cmd->argv[0], '/'))
	{
		if (execve(cmd->argv[0], cmd->argv, data->env) == -1)
		{
			perror(cmd->argv[0]);
			exit(127);
		}
	}
	else
		search_and_exec(cmd->argv[0], data->env_lst, cmd, data);
}

/*static char	*get_the_path(char *cmd, char **paths)
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
	while (!str_equals("PATH", temp->name))
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
}*/
