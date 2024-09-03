/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:54:20 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/03 09:04:33 by vsharma          ###   ########.fr       */
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

/*helper function for search_and_exec*/
static char	*find_valid_path(char *cmd, char **paths)
{
	char	*path;
	size_t	i;

	i = 0;
	while (paths[i])
	{
		path = combine_and_release(ft_strjoin(paths[i], "/"), cmd);
		if (path && access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

static void	search_and_exec(char *cmd, t_elst *env_lst, t_cmd *cmd_struct,
		t_data *data)
{
	char	**paths;
	char	*env_paths;
	char	*exec_path;

	env_paths = get_env_variable(env_lst, "PATH");
	if (!env_paths)
		exit_with_cleanup(cmd, data, NULL, 127);
	paths = ft_split(env_paths, ':');
	free(env_paths);
	if (!paths)
		exit_with_cleanup(cmd, data, NULL, 127);
	exec_path = find_valid_path(cmd, paths);
	if (exec_path)
	{
		if (execve(exec_path, cmd_struct->argv, data->env) == -1)
		{
			perror(exec_path);
			free(exec_path);
			exit_with_cleanup(NULL, data, paths, 126);
		}
		free(exec_path);
		exit_with_cleanup(NULL, data, paths, 0);
	}
	exit_with_cleanup(cmd, data, paths, 127);
}

/*change to fix leaks */
/*static void	search_and_exec(char *cmd, t_elst *env_lst, t_cmd *cmd_struct,
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
	if (!paths)
		exit_with_cleanup(cmd, data, NULL, 127);
	while (paths[i])
	{
		path = combine_and_release(ft_strjoin(paths[i], "/"), cmd);
		if (path && access(path, F_OK | X_OK) == 0)
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
}*/

/*code written by RENE*/
/*static void	search_and_exec(char *cmd, t_elst *env_lst, t_cmd *cmd_struct,
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
}*/

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
