/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:34:26 by caslan            #+#    #+#             */
/*   Updated: 2024/05/06 08:52:36 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_error_message(char *path)
{
	char	*error;

	error = ft_strjoin("minishell: cd: ", path);
	perror(error);
	free(error);
	return (EXIT_FAILURE);
}

static void	update_pwd(t_data *data)
{
	char	cwd[PATH_MAX];
	char	*updated;

	getcwd(cwd, PATH_MAX);
	updated = ft_strjoin("PWD=", cwd);
	store_usr_var(updated, &data->env_lst, true);
	free(updated);
}

static void	update_oldpwd(char *temp, t_data *data)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", temp);
	store_usr_var(oldpwd, &data->env_lst, true);
	free(oldpwd);
}

static int	cd_oldpwd(char *temp, t_data *data)
{
	char	*oldpwd;

	oldpwd = get_fromvlst("OLDPWD", &data->env_lst);
	if (!oldpwd)
	{
		ft_putendl_fd(OLD_PWD_NOT_SET, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (chdir(oldpwd) == SUCCESS)
	{
		ft_putendl_fd(oldpwd, STDOUT_FILENO);
		update_oldpwd(&temp[0], data);
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	return (cd_error_message(oldpwd));
}

int	ft_cd(char *path, t_data *data)
{
	char	temp[PATH_MAX];

	getcwd(temp, PATH_MAX);
	if (path == NULL || ft_is_str_equal(path, "~"))
	{
		update_oldpwd(&temp[0], data);
		chdir(getenv("HOME"));
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	if (ft_is_str_equal(path, "-"))
		return (cd_oldpwd(&temp[0], data));
	if (chdir(path) == SUCCESS)
	{
		update_oldpwd(&temp[0], data);
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	return (cd_error_message(path));
}

/*
static int	cd_error_message(char *path)
{
	char	*error;

	error = ft_strjoin("minishell: cd: ", path);
	perror(error);
	free(error);
	return (EXIT_FAILURE);
}

static void	update_pwd(t_data *data)
{
	char	cwd[PATH_MAX];
	char	*updated;

	getcwd(cwd, PATH_MAX);
	updated = ft_strjoin("PWD=", cwd);
	store_usr_var(updated, &data->env_lst, true);
	free(updated);
}

static void	update_oldpwd(char *temp, t_data *data)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", temp);
	store_usr_var(oldpwd, &data->env_lst, true);
	free(oldpwd);
}

static int	cd_oldpwd(char *temp, t_data *data)
{
	char	*oldpwd;

	oldpwd = get_fromvlst("OLDPWD", &data->env_lst);
	if (!oldpwd)
	{
		ft_putendl_fd(OLD_PWD_NOT_SET, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (chdir(oldpwd) == SUCCESS)
	{
		ft_putendl_fd(oldpwd, STDOUT_FILENO);
		update_oldpwd(&temp[0], data);
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	return (cd_error_message(oldpwd));
}

int	ft_cd(char *path, t_data *data)
{
	char	temp[PATH_MAX];

	getcwd(temp, PATH_MAX);
	if (path == NULL || ft_is_str_equal(path, "~"))
	{
		update_oldpwd(&temp[0], data);
		chdir(getenv("HOME"));
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	if (ft_is_str_equal(path, "-"))
		return (cd_oldpwd(&temp[0], data));
	if (chdir(path) == SUCCESS)
	{
		update_oldpwd(&temp[0], data);
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	return (cd_error_message(path));
} */
