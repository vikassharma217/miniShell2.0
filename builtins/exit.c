/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:53:02 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/11 16:43:00 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	non_numeric_args(t_data *data)
{
	data->exit_code = 2;
	ft_putendl_fd("minishell: exit: numeric argument required", STDERR_FILENO);
	ft_clear_all(data);
	exit(data->exit_code);
}
//Validates if the given string represents a valid long integer.
//Returns true if the value is valid, otherwise false

static bool	check_long(char *str)
{
	long long	result;
	int			digit;

	if (str_equals("-9223372036854775808", str))
		return (true);
	result = 0;
	if (*str == '-' || *str == '+')
		str += 1;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		digit = *str - '0';
		if (result > (LLONG_MAX - digit) / 10)
			return (false);
		result = result * 10 + digit;
		str++;
	}
	return (true);
}
//Checks if a string consists only of digits
//returns true if string is valid(true(1)), else false(0)

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
//checks if the exit status is a valid numeric value, and sets the exit code.

static bool	process_exit_args(t_cmd *cmd, t_data *data)
{
	if (cmd->argc > 2)
	{
		if (!check_digits(cmd->argv[1]))
			non_numeric_args(data);
		data->exit_code = EXIT_FAILURE;
		write(2, "minishell: exit: too many arguments\n", 36);
		return (false);
	}
	if (cmd->argc == 2)
	{
		if (cmd->argv[1][0] == '\0')
			non_numeric_args(data);
		if (check_digits(cmd->argv[1]) && check_long(cmd->argv[1]))
			data->exit_code = ft_atol(cmd->argv[1]);
		else
			non_numeric_args(data);
	}
	return (true);
}
//Handles the shell's exit command, processing exit arguments
//If pipe getting argc of current node to check if valid with 1 argv

void	exit_shell(t_cmd *cmd, t_data *data)
{
	int		i;
	int		exit_status;

	i = 0;
	exit_status = data->exit_code;
	if (data->is_pipe)
	{
		while (cmd->argv[i])
			i++;
		cmd->argc = i;
		process_exit_args(cmd, data);
	}
	else if (!process_exit_args(cmd, data))
		return ;
	if (!data->is_pipe)
		write(1, "exit\n", 5);
	exit_status = data->exit_code;
	if (data)
		ft_clear_all(data);
	exit(exit_status);
}
