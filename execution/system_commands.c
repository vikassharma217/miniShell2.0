/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:54:20 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/08 18:48:47 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//exit with cleaning each array from path

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
//get env variable list

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

//searches each array like /bin/cat or /bin/ls
//if access is 0 it returns that absolute path
//F_OK if file exists, x_OK if file is executable

static char	*find_valid_path(char *cmd, char **paths)
{
	char	*path;
	char	*copy;
	size_t	i;

	i = 0;
	while (paths[i])
	{
		copy = ft_strjoin(paths[i], "/");
		path = ft_strjoin(copy, cmd);
		free(copy);
		if (path && access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
//splits PATH in seperate arrays to search in each of for the system command
//exec_path is the path
//execve return 0 if it found it
//126 for found but not executable
//127 command not found

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
//checks if command starts with /PATH as direct path or
//it should search for it

void	system_commands(t_cmd *cmd, t_data *data)
{
	if (ft_strchr(cmd->argv[0], '/'))
	{
		if (execve(cmd->argv[0], cmd->argv, data->env) == -1)
		{
			perror(cmd->argv[0]);
			exit_with_cleanup(NULL, data, NULL, 127);
		}
	}
	else
		search_and_exec(cmd->argv[0], data->env_lst, cmd, data);
}
