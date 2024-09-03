/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:52:38 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/03 08:25:03 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Backslash things fixed but we need that?
static void	check_and_print(const char *str)
{
	int	backslash_flag;

	backslash_flag = 0;
	if (str == NULL)
		return ;
	while (*str)
	{
		if (*str == '\\' && backslash_flag)
		{
			write(1, "\\", 1);
			backslash_flag = 0;
		}
		else if (*str == '\\')
			backslash_flag = 1;
		if (*str != '\\')
			write(1, str, 1);
		str++;
	}
}

static int	check_new_line_flag(const char *argv)
{
	int	i;

	i = 1;
	if (argv[0] != '-')
		return (0);
	while (argv[i] == 'n')
		i++;
	return (argv[i] == '\0');
}

int	echo(t_cmd *cmd)
{
	int	print_new_line_flag;
	int	i;

	print_new_line_flag = 0;
	i = 0;
	while (++i < cmd->argc && check_new_line_flag(cmd->argv[i]))
		print_new_line_flag = 1;
	while (i < cmd->argc)
	{
		check_and_print(cmd->argv[i]);
		if (i++ < cmd->argc - 1)
			write(1, " ", 1);
	}
	if (!print_new_line_flag)
		write(1, "\n", 1);
	return (0);
}
