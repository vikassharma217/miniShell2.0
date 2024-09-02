/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:53:18 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/02 17:03:28 by vsharma          ###   ########.fr       */
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
		store_env_var(updated_old_pwd, &data->env_lst, true);
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
	while (current_dir[j] != '\0')
		old_pwd[i++] = current_dir[j++];
	old_pwd[i] = '\0';
	store_env_var(old_pwd, &data->env_lst, true);
}

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

int	cd(t_cmd *cmd, t_data *data, char *target_dir)
{
	char	current_dir[PATH_MAX];

	if (cmd->argc > 2)
		return (write(2, "cd: too many arguments\n", 23), EXIT_FAILURE);
	if (!getcwd(current_dir, PATH_MAX))
		return (write(2, "minishell: cd: getcwd error\n", 29), EXIT_FAILURE);
	if (!target_dir || str_equals(target_dir, "~"))
		return (handle_cd_to_home_or_oldpwd("HOME", current_dir, data));
	if (str_equals(target_dir, "-"))
		return (handle_cd_to_home_or_oldpwd("OLDPWD", current_dir, data));
	if (chdir(target_dir) != 0)
		return (print_cd_error(target_dir));
	save_old_pwd(current_dir, data);
	update_pwd(data);
	return (EXIT_SUCCESS);
}
