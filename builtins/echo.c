/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:52:38 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/08 22:27:53 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Prints the given string to stdout, handling escaped backslashes
//Consecutive backslashes are printed as a single backslash.

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
//Returns 1 if the flag is valid, otherwise 0.

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
//Implements the echo command, handling the '-n' flag, and printing the arg

int	echo(t_cmd *cmd)
{
	int	print_new_line_flag;
	int	i;
	int	j;

	print_new_line_flag = 0;
	i = 0;
	j = 1;
	while (cmd->argv[j])
		j++;
	while (++i < cmd->argc && check_new_line_flag(cmd->argv[i]))
		print_new_line_flag = 1;
	while (i < j)
	{
		check_and_print(cmd->argv[i]);
		if (i < j - 1)
			write(1, " ", 1);
		i++;
	}
	if (!print_new_line_flag)
		write(1, "\n", 1);
	return (0);
}
