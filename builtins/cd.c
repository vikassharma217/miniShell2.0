/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:53:18 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/11 13:41:12 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//Updates the current working directory (PWD) in the environment variables 
//and saves the new path in the data structure.

static void	update_pwd(t_data *data)
{
	char	cwd[PATH_MAX];
	char	updated_old_pwd[PATH_MAX + 5];
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (getcwd(cwd, PATH_MAX))
	{
		updated_old_pwd[i++] = 'P';
		updated_old_pwd[i++] = 'W';
		updated_old_pwd[i++] = 'D';
		updated_old_pwd[i++] = '=';
		while (cwd[j] != '\0')
			updated_old_pwd[i++] = cwd[j++];
		updated_old_pwd[i] = '\0';
		store_env_var(updated_old_pwd, &data->env_lst, true);
		ft_strncpy(data->saved_path, cwd, PATH_MAX);
	}
}
//Updates the old working directory (OLDPWD) in the environment variables 
//and saves the old path in the data structure.

static void	save_old_pwd(char *current_dir, t_data *data)
{
	char	old_pwd[PATH_MAX + 7];
	int		i;
	int		j;

	i = 0;
	j = 0;
	old_pwd[i++] = 'O';
	old_pwd[i++] = 'L';
	old_pwd[i++] = 'D';
	old_pwd[i++] = 'P';
	old_pwd[i++] = 'W';
	old_pwd[i++] = 'D';
	old_pwd[i++] = '=';
	while (current_dir[j] != '\0')
		old_pwd[i++] = current_dir[j++];
	old_pwd[i] = '\0';
	store_env_var(old_pwd, &data->env_lst, true);
}
//Handles the "cd" command for navigating to the home or OLDPWD directory,
//updating environment variables and handling errors if not set.

static int	handle_cd_to_home_or_oldpwd(char *env_var, char *current_dir,
		t_data *data)
{
	char	*dir;

	dir = get_fromvlst(env_var, &data->env_lst);
	if (!dir)
	{
		write(2, "minishell: cd: ", 15);
		write(2, env_var, ft_strlen(env_var));
		write(2, " not set\n", 9);
		return (EXIT_FAILURE);
	}
	if (chdir(dir) != 0)
		return (print_cd_error(dir));
	if (str_equals(env_var, "OLDPWD"))
		ft_putendl_fd(dir, STDOUT_FILENO);
	save_old_pwd(current_dir, data);
	update_pwd(data);
	return (EXIT_SUCCESS);
}
//updates the saved path when changing directories
//updates the saved path if directiory is deleted until last /

void	update_saved_path(char *target_dir, t_data *data)
{
	char	tmp_saved_path[PATH_MAX];
	char	*last_slash;

	if (str_equals(target_dir, ".."))
	{
		last_slash = ft_strrchr(data->saved_path, '/');
		if (last_slash)
			*last_slash = '\0';
	}
	else
	{
		ft_strlcpy(tmp_saved_path, data->saved_path, PATH_MAX);
		ft_strlcat(tmp_saved_path, "/", PATH_MAX);
		ft_strlcat(tmp_saved_path, target_dir, PATH_MAX);
		ft_strlcpy(data->saved_path, tmp_saved_path, PATH_MAX);
	}
}
//Changes the current directory, handling special cases like '~' and
//updates the environment variables PWD and OLDPWD.

int	cd(t_cmd *cmd, t_data *data, char *target_dir)
{
	char	current_dir[PATH_MAX];

	ft_bzero(current_dir, PATH_MAX);

	if (cmd->argc > 2)
		return (write(2, "cd: too many arguments\n", 23), EXIT_FAILURE);
	if (!target_dir || str_equals(target_dir, "~"))
		return (handle_cd_to_home_or_oldpwd("HOME", current_dir, data));
	if (!getcwd(current_dir, PATH_MAX))
	{
		perror("minishell: cd: getcwd: cannot access parent directories");
		if (data->saved_path[0] == '\0')
			ft_strncpy(current_dir, data->saved_path, PATH_MAX);
		else
			ft_strncpy(current_dir, "/", PATH_MAX);
	}
	if (str_equals(target_dir, "-"))
		return (handle_cd_to_home_or_oldpwd("OLDPWD", current_dir, data));
	if (chdir(target_dir) != 0)
		return (print_cd_error(target_dir));
	if (!getcwd(data->saved_path, PATH_MAX))
		update_saved_path(target_dir, data);
	save_old_pwd(current_dir, data);
	update_pwd(data);
	return (EXIT_SUCCESS);
}
