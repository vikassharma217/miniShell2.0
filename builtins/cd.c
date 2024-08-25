/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscherl <rscherl@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:53:18 by rscherl           #+#    #+#             */
/*   Updated: 2024/08/24 17:53:20 by rscherl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_error_message(char *target_dir)
{
	char	*error;

	error = ft_strjoin("minishell: cd: ", target_dir);
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

static void	update_oldpwd(char *current_dir, t_data *data)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", current_dir);
	store_usr_var(oldpwd, &data->env_lst, true);
	free(oldpwd);
}

static int	cd_oldpwd(char *current_dir, t_data *data)
{
	char	*oldpwd;

	oldpwd = get_fromvlst("OLDPWD", &data->env_lst);
	if (!oldpwd)
	{
		write(STDERR_FILENO, "minishell: cd: OLDPWD not set\n", 31);
		return (EXIT_FAILURE);
	}
	if (chdir(oldpwd) == SUCCESS)
	{
		ft_putendl_fd(oldpwd, STDOUT_FILENO);
		update_oldpwd(current_dir, data);
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	return (cd_error_message(oldpwd));
}

int	cd(char *target_dir, t_data *data)
{
	char	current_dir[PATH_MAX];

	getcwd(current_dir, PATH_MAX);
	if (target_dir == NULL || ft_is_str_equal(target_dir, "~"))
	{
		update_oldpwd(current_dir, data);
		chdir(getenv("HOME"));
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	if (ft_is_str_equal(target_dir, "-"))
		return (cd_oldpwd(current_dir, data));
	if (chdir(target_dir) == SUCCESS)
	{
		update_oldpwd(current_dir, data);
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	return (cd_error_message(target_dir));
}

/*
static int	cd_error_message(char *target_dir)
{
	char	*error;

	error = ft_strjoin("minishell: cd: ", target_dir);
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
	store_usr_var(updated, data->env_lst, true);
	free(updated);
}

static void	update_oldpwd(char *current_dir, t_data *data)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", current_dir);
	store_usr_var(oldpwd, data->env_lst, true);
	free(oldpwd);
}

static int	cd_oldpwd(char *current_dir, t_data *data)
{
	char	*oldpwd;

	oldpwd = get_fromvlst("OLDPWD", data->env_lst);
	if (!oldpwd)
	{
		ft_putendl_fd(OLD_PWD_NOT_SET, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (chdir(oldpwd) == SUCCESS)
	{
		ft_putendl_fd(oldpwd, STDOUT_FILENO);
		update_oldpwd(current_dir, data);
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	return (cd_error_message(oldpwd));
}

int	ft_cd(char *target_dir, t_data *data)
{
	char	current_dir[PATH_MAX];

	getcwd(current_dir, PATH_MAX);
	if (target_dir == NULL || ft_is_str_equal(target_dir, "~"))
	{
		update_oldpwd(current_dir, data);
		chdir(getenv("HOME"));
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	if (ft_is_str_equal(target_dir, "-"))
		return (cd_oldpwd(current_dir, data));
	if (chdir(target_dir) == SUCCESS)
	{
		update_oldpwd(current_dir, data);
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	return (cd_error_message(target_dir));
} */
