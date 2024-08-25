/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscherl <rscherl@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:52:38 by rscherl           #+#    #+#             */
/*   Updated: 2024/08/24 17:52:42 by rscherl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_and_print(const char *str)
{
	while (*str)
	{
		if (*str != '\\')
			write(1, str, 1);
		str++;
	}
}

static bool	check_n_flag(const char *argv)
{
	int	j;

	j = 1;
	if (argv[0] != '-')
		return (false);
	while (argv[j] == 'n')
		j++;
	return (argv[j] == '\0');
}

int	echo(t_cmd *cmd)
{
	bool	flag_for_n;
	int		i;

	flag_for_n = false;
	i = 0;
	while (++i < cmd->argc && check_n_flag(cmd->argv[i]))
		flag_for_n = true;
	while (i < cmd->argc)
	{
		check_and_print(cmd->argv[i]);
		if (i < cmd->argc - 1)
			write(1, " ", 1);
		i++;
	}
	if (!flag_for_n)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

/*static void	ft_print(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			i++;
			continue ;
		}
		ft_putchar_fd(str[i], STDOUT_FILENO);
		i++;
	}
}

bool	ft_str_start(const char *str, const char *pre)
{
	while (*pre)
	{
		if (*pre++ != *str++)
			return (false);
	}
	return (true);
}

int	ft_echo(t_cmd *cmd, t_data *data)
{
	bool	flag_for_n;
	int		i;

	(void)data;
	i = 1;
	flag_for_n = false;
	while (i < cmd->argc && ft_str_start(cmd->argv[i], "-n"))
	{
		flag_for_n = true;
		i++;
	}
	while (i < cmd->argc)
	{
		ft_print(cmd->argv[i]);
		if (i < cmd->argc - 1)
		{
			ft_putchar_fd(' ', STDOUT_FILENO);
		}
		i++;
	}
	if (!flag_for_n)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (EXIT_SUCCESS);
}*/
