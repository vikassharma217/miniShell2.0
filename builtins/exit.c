/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:12:56 by caslan            #+#    #+#             */
/*   Updated: 2024/05/10 16:37:26 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	non_numeric_args(t_data *data)
{
	data->exit_code = 2;
	ft_putendl_fd("minishell: exit: numeric argument required", STDERR_FILENO);
}

static bool	check_long(char *str)
{
	long long	result;
	int			digit;

	if (ft_is_str_equal("-9223372036854775808", str))
		return (true);
	result = 0;
	if (*str == '-' || *str == '+')
		str += 1;
	while (*str)
    {
        if (!isdigit(*str))
            return false;
        digit = *str - '0';
        if (result > (LLONG_MAX - digit) / 10)
            return false;
        result = result * 10 + digit;
        str++;
    }
	return (true);
}

static bool	check_digits(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (false);
		i++;
	}
	return (true);
}

static bool	process_exit_args(t_cmd *cmd, t_data *data)
{
	if (cmd->argc > 2)
	{
		data->exit_code = EXIT_FAILURE;
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
        return false;
    }
	if (cmd->argc == 2)
	{
		if (check_digits(cmd->argv[1]) && check_long(cmd->argv[1]))
			data->exit_code = ft_atol(cmd->argv[1]);
		else
			non_numeric_args(data); //true or false return? should exit?
	}
	return (true);
}

void	ft_exit(t_cmd *cmd, t_data *data, int status_code)
{
	status_code = 0; //?delete .. status code already set in data->exit_code?
	write(1, "exit\n", 5);
	if (!process_exit_args(cmd, data))
		return ;
	status_code = data->exit_code;
	if (data)
		ft_clear_all(data);
	exit(status_code);
}
/*
static void	non_numeric_args(t_data *data)
{
	data->exit_code = 2;
	ft_putendl_fd("minishell: exit: numeric argument required", STDERR_FILENO);
	return ;
}

static void	too_many_args(t_data *data)
{
	data->exit_code = EXIT_FAILURE;
	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	return ;
}

bool	process_exit_args(t_cmd *cmd, t_data *data)
{
	if (cmd->argc == 2)
	{
		if (check_digits(cmd->argv[1]))
		{
			if (!check_long(cmd->argv[1]))
				non_numeric_args(data);
			else
				data->exit_code = ft_atol(cmd->argv[1]);
		}
		else
			non_numeric_args(data);
	}
	else if (cmd->argc > 2)
	{
		if (!check_digits(cmd->argv[1]))
		{
			non_numeric_args(data);
			return (true);
		}
		too_many_args(data);
		return (false);
	}
	return (true);
}

bool	check_long(char *str)
{
	long long	out;
	int			c;

	if (ft_strlen(str) > 20)
		return (false);
	if (ft_is_str_equal("-9223372036854775808", str))
		return (true);
	out = 0;
	if (*str == '-' || *str == '+')
		str += 1;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		c = *str - '0';
		if (out > (LLONG_MAX - c) / 10)
			return (false);
		out = out * 10 + c;
		str += 1;
	}
	return (true);
}

bool	check_digits(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit(t_cmd *cmd, t_data *data, int status_code)
{
	status_code = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (!process_exit_args(cmd, data))
		return ;
	status_code = data->exit_code;
	if (data)
	{
		ft_clear_all(data);
	}
	exit(status_code);
}*/
