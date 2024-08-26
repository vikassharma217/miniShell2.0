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

static int	print_cd_error(char *target_dir)
{
	write(2, "minishell: cd: ", 15);
	write(2, "No such file or directory: ", 28);
	write(2, target_dir, ft_strlen(target_dir));
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}

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
		store_usr_var(updated_old_pwd, &data->env_lst, true);
	}
}

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
	while (current_dir[j] != '\0' && i < (PATH_MAX + 7 - 1))
		old_pwd[i++] = current_dir[j++];
	old_pwd[i] = '\0';
	store_usr_var(old_pwd, &data->env_lst, true);
}

static int	change_to_old_pwd(char *current_dir, t_data *data)
{
	char	*old_pwd;

	old_pwd = get_fromvlst("OLDPWD", &data->env_lst);
	if (!old_pwd)
		return(write(2, "minishell: cd: OLDPWD not set\n", 31), EXIT_FAILURE);
	if (chdir(old_pwd) != 0)
		return (print_cd_error(old_pwd));
	ft_putendl_fd(old_pwd, STDOUT_FILENO);
	save_old_pwd(current_dir, data);
	update_pwd(data);
	return (EXIT_SUCCESS);
}

int	cd(t_cmd *cmd, t_data *data, char *target_dir)
{
	char	current_dir[PATH_MAX];

	if (cmd->argc > 2)
		return (write(2, "cd: too many arguments\n", 23), EXIT_FAILURE);
	if (!getcwd(current_dir, PATH_MAX))
		return (write(2, "minishell: cd: getcwd()\n", 31), EXIT_FAILURE);
	if (!target_dir || ft_is_str_equal(target_dir, "~"))
	{
		save_old_pwd(current_dir, data);
		if (chdir(getenv("HOME")) != 0)
		{
			perror("minishell: cd: could not change to home directory");
			return (EXIT_FAILURE);
		}
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	if (ft_is_str_equal(target_dir, "-"))
		return (change_to_old_pwd(current_dir, data));
	if (chdir(target_dir) != 0)
		return (print_cd_error(target_dir));
	save_old_pwd(current_dir, data);
	update_pwd(data);
	return (EXIT_SUCCESS);
}

/*int	cd(t_cmd *cmd, char *target_dir, t_data *data)
{
	char	current_dir[PATH_MAX];

	if (cmd->argc > 2)
		return (write(2, "cd: too many arguments\n", 23), EXIT_FAILURE);
	getcwd(current_dir, PATH_MAX);
	if (target_dir == NULL || ft_is_str_equal(target_dir, "~"))
	{
		save_oldpwd(current_dir, data);
		chdir(getenv("HOME"));
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	if (ft_is_str_equal(target_dir, "-"))
		return (cd_oldpwd(current_dir, data));
	if (chdir(target_dir) == SUCCESS)
	{
		save_oldpwd(current_dir, data);
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	return (print_cd_error(target_dir));
}*/

/*
static int	print_cd_error(char *target_dir)
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
	char	*updated_old_pwd;

	getcwd(cwd, PATH_MAX);
	updated_old_pwd = ft_strjoin("PWD=", cwd);
	store_usr_var(updated_old_pwd, data->env_lst, true);
	free(updated_old_pwd);
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
	return (print_cd_error(oldpwd));
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
	return (print_cd_error(target_dir));
} */
